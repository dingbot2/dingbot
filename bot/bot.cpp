#include "bot.h"
#include "../global.h"
#include "../logger.h"
#include <boost/json.hpp>
#include <fstream>

namespace dingbot::bot {
    BotSetting _bot;
    GoCQHttpSetting _gocqhttp;

    void Init()
    {
        dingbot::logger::GetConsoleLogger()->info("正在加载配置...");
        {
            std::ifstream in(global::getGlobalPath() / "data" / "bot.json");
            boost::json::object j = boost::json::parse(in).as_object();
            in.close();
            _bot.name = j["name"].as_string();
            _bot.qq = j["qq"].as_string();
            boost::json::array masterJson = j["master"].as_array();
            for (auto i: masterJson) {
                _bot.master.emplace_back(i.as_string().c_str());
            }
        }
        {
            std::ifstream in(global::getGlobalPath()/"data"/"gocqhttp.json");
            boost::json::object j = boost::json::parse(in).as_object();
            in.close();
            _gocqhttp.http = j["http"].as_int64();
            _gocqhttp.http_string = std::to_string(j["http"].as_int64());
            _gocqhttp.ws = j["ws"].as_int64();
            _gocqhttp.ws_string = std::to_string(j["ws"].as_int64());
            dingbot::logger::GetConsoleLogger()->debug("ws反向服务器端口:{0},http端口:{1}",_gocqhttp.ws_string.c_str(),_gocqhttp.http_string.c_str());
        }
        dingbot::logger::GetConsoleLogger()->info("已加载机器人:{0}",_bot.name.c_str());
    }

    BotSetting getBotSetting()
    {
        return _bot;
    }

    GoCQHttpSetting getCQHttpSetting()
    {
        return _gocqhttp;
    }
}