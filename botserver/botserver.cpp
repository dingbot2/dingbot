#include "botserver.h"
#include "../logger.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include "../bot/bot.h"
#include <boost/json.hpp>
#include "../plugin/plugin.h"

namespace dingbot::botserver {
    void handleMessage(const std::string& msg)
    {
        boost::json::object j = boost::json::parse(msg).as_object();
        using std::string;
        string post_type = j["post_type"].as_string().c_str();
        if(post_type == "meta_event")
        {
            return;
        }
        if(post_type == "message")
        {
            string message_type = j["message_type"].as_string().c_str();
            string user_id = std::to_string(j["sender"].as_object()["user_id"].as_int64());
            string message = j["message"].as_string().c_str();
            if(message_type == "private") //私聊消息
            {
                dingbot::logger::GetConsoleLogger()->debug("收到来自{0}的私聊消息:{1}",user_id.c_str(),message.c_str());
                dingbot::plugin::sendEventPrivateMsg(message,user_id);
                return;
            }
            if(message_type == "group") //群聊消息
            {
                return;
            }
        }
        dingbot::logger::GetConsoleLogger()->debug("ws 收到 {0}",msg.c_str());
    }
    void do_session(boost::asio::ip::tcp::socket socket)
    {
        try
        {
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{std::move(socket)};

            ws.accept();
            for(;;)
            {
                boost::beast::flat_buffer buffer;
                ws.read(buffer);
                ws.text(ws.got_text());
                std::stringstream ss;
                ss<<boost::beast::make_printable(buffer.data());
                std::string msg = ss.str();
                std::thread run(handleMessage,msg);
                run.detach();
            }
        }
        catch(boost::beast::system_error const& se)
        {
            if(se.code() != boost::beast::websocket::error::closed)
            {
                dingbot::logger::GetConsoleLogger()->error("ws server:{0}",se.code().message().c_str());
            }
        }
        catch(std::exception const& e)
        {
            dingbot::logger::GetConsoleLogger()->error("ws server:{0}",e.what());
        }
    }
    void start()
    {
        dingbot::logger::GetConsoleLogger()->info("正在启动bot server(ws 服务器)...");
        try
        {
            auto const address = boost::asio::ip::make_address("127.0.0.1");
            auto const port = static_cast<unsigned short>(dingbot::bot::getCQHttpSetting().ws);

            boost::asio::io_context ioc{1};
            boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};
            for(;;)
            {
                boost::asio::ip::tcp::socket socket{ioc};
                acceptor.accept(socket);
                std::thread(
                        &do_session,
                        std::move(socket)).detach();
            }
        }
        catch (const std::exception& e)
        {
            dingbot::logger::GetConsoleLogger()->error("ws server:{0}",e.what());
        }
    }
}