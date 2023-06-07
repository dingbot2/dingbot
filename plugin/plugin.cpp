#include "plugin.h"
#include "../global.h"
#include "pluginmodel.h"
#include <fstream>
#include <boost/json.hpp>
#include "../logger.h"
#include <map>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <utility>
#include "../botapi/botapi.h"
#include "../bot/bot.h"
namespace dingbot::plugin {
    bool isPluginDisable(std::string name)
    {
        if(!boost::filesystem::exists(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json"))
        {
            return false;
        }
        std::ifstream in(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json");
        boost::json::object j = boost::json::parse(in).as_object();
        in.close();
        if (!j.contains(name))
        {
            return false;
        }
        if(j[name].as_object()["disable"].as_bool())
        {
            return true;
        }
        return false;
    }
    void disablePlugin(std::string name)
    {
        if(!boost::filesystem::exists(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json"))
        {
            std::ofstream out(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json");
            boost::json::object j;
            boost::json::object j2;
            j2["disable"] = true;
            j[name] = j2;
            out << boost::json::serialize(j).c_str();
            out.close();
            return;
        }
        std::ifstream in(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json");
        boost::json::object j = boost::json::parse(in).as_object();
        in.close();
        boost::json::object j2;
        j2["disable"] = true;
        j[name] = j2;
        std::ofstream out(dingbot::global::getGlobalPath()/"data"/"plugin_disable.json");
        out << boost::json::serialize(j).c_str();
        out.close();
    }

    std::map<std::string,boost::shared_ptr<dingbot_plugin_model> > plugins;

    void loadPlugins()
    {
        auto nowPath = dingbot::global::getGlobalPath();
        boost::filesystem::directory_iterator end_it;
        for(boost::filesystem::directory_iterator i(nowPath/"plugin");i!=end_it;i++)
        {
            auto i_path = i->path();
            if (!boost::filesystem::is_directory(i_path))
            {
                continue;
            }
            dingbot::logger::GetConsoleLogger()->debug("正在尝试加载插件:{0}",i_path.stem().c_str());
            string name = i_path.stem().c_str();
            if(isPluginDisable(name))
            {
                continue;
            }
            i_path /= name;
            typedef boost::shared_ptr<dingbot_plugin_model> (pluginCreator)();
            boost::function<pluginCreator> c = boost::dll::import_alias<pluginCreator>(i_path,"create_plugin",boost::dll::load_mode::append_decorations);
            plugins[name] = c();
            boost::shared_ptr<dingbot::apimodel::Model> p = dingbot::apimodel::makeInstance();
            p->setPluginName(name);
            p->setHttpPort(dingbot::bot::getCQHttpSetting().http);
            plugins[name]->setApiModel(p);
            dingbot::logger::GetConsoleLogger()->info("成功加载插件:{0},作者:{1}",plugins[name]->getPluginInfo().pluginName.c_str(),plugins[name]->getPluginInfo().author.c_str());
        }
    }

    void sendEventPrivateMsg(string message,string sender_id)
    {
        if(!plugins["plugin"])
        {
            dingbot::logger::GetConsoleLogger()->error("ptr error!");
            return;
        }
        plugins["plugin"]->event_private_msg(strdup(message.c_str()), strdup(sender_id.c_str()));
    }
}