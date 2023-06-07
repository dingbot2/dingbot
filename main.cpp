#include "logger.h"
#include "cmdline.h"
#include "global.h"
#include "tool/tool.h"
#include <boost/json/src.hpp>
#include <iostream>
#include <fstream>
#include "bot/bot.h"
#include "botserver/botserver.h"
#include "botapi/botapi.h"
#include "plugin/plugin.h"

void InitPath()
{
    dingbot::tool::createPath(dingbot::global::getGlobalPath()/"plugin");
    dingbot::tool::createPath(dingbot::global::getGlobalPath()/"data");
}

void InitGoCqhttp()
{
    if(!boost::filesystem::exists(dingbot::global::getGlobalPath()/"data"/"gocqhttp.json"))
    {
        dingbot::logger::GetConsoleLogger()->info("gocqhttp未配置，正在启动生成程序。");
        boost::json::object j;
        using namespace std;
        cout << "请输入反向ws端口:";
        int cnt;
        cin >> cnt;
        j["ws"] = cnt;
        cout << "请输入正向http端口:";
        int cnt_int;
        cin >> cnt_int;
        j["http"] = cnt_int;
        ofstream out(dingbot::global::getGlobalPath()/"data"/"gocqhttp.json");
        out << boost::json::serialize(j) ;
        out.close();
        dingbot::logger::GetConsoleLogger()->info("gocqhttp配置生成成功！");
    }
    if(!boost::filesystem::exists(dingbot::global::getGlobalPath()/"data"/"bot.json"))
    {
        dingbot::logger::GetConsoleLogger()->info("机器人信息未配置，正在启动生成程序。");
        boost::json::object j;
        using namespace std;
        cout << "请输入机器人名称(dingbot):";
        string cnt;
        cin >> cnt;
        j["name"] = cnt;
        cout << "请输入机器人QQ号:";
        cin >> cnt;
        j["qq"] = cnt;
        cout << "请输入初始主人QQ号:";
        cin >> cnt;
        boost::json::array masters;
        masters.push_back(cnt.c_str());
        j["master"] = masters;
        ofstream out(dingbot::global::getGlobalPath()/"data"/"bot.json");
        out << boost::json::serialize(j) ;
        out.close();
        dingbot::logger::GetConsoleLogger()->info("bot配置生成成功！");
    }
}

int main(int argc,char **argv)
{
    dingbot::cmdline::parse(argc,argv);
    dingbot::logger::InitLogger();
    dingbot::logger::GetConsoleLogger()->info("dingbot version : {0}",dingbot::global::getDingBotVersion().c_str());
    dingbot::logger::GetConsoleLogger()->info("dingbot QQ交流群 : 603838409");
    InitPath();
    InitGoCqhttp();
    dingbot::bot::Init();
    dingbot::botapi::init(dingbot::bot::getCQHttpSetting().http);
    dingbot::plugin::loadPlugins();
    dingbot::botserver::start();
}