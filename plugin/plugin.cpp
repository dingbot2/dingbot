#include "plugin.h"
#include "../global.h"
#include <fstream>
#include <boost/json.hpp>
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
}