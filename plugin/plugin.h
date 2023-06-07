#ifndef DINGBOT_PLUGIN_H
#define DINGBOT_PLUGIN_H
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "pluginmodel.h"
namespace dingbot::plugin {
    bool isPluginDisable(std::string name);
    void disablePlugin(std::string name);
    void loadPlugins();
    void sendEventPrivateMsg(string message,string sender_id);
}
#endif //DINGBOT_PLUGIN_H