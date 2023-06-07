#include "botserver.h"
#include "../logger.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include "../bot/bot.h"

namespace dingbot::botserver {
    void do_session(boost::asio::ip::tcp::socket socket)
    {
        dingbot::logger::GetConsoleLogger()->debug("ws client json");
        try
        {
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{std::move(socket)};

            ws.accept();
            for(;;)
            {
                boost::beast::flat_buffer buffer;
                ws.read(buffer);
                ws.text(ws.got_text());
                ws.write(buffer.data());
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
            auto const address = boost::asio::ip::make_address("0.0.0.0");
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