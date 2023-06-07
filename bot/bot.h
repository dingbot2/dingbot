#ifndef DINGBOT_BOT_H
#define DINGBOT_BOT_H
#include <string>
#include <vector>
namespace dingbot::bot {
    struct BotSetting
    {
        std::string name;
        std::string qq;
        std::vector<std::string> master;
    };
    struct GoCQHttpSetting
    {
        std::string ws_string;
        int ws;
        int http;
        std::string http_string;
    };
    void Init();
    BotSetting getBotSetting();
    GoCQHttpSetting getCQHttpSetting();
}
#endif //DINGBOT_BOT_H
