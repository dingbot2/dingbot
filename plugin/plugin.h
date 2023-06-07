#ifndef DINGBOT_PLUGIN_H
#define DINGBOT_PLUGIN_H
#include <string>
namespace dingbot::plugin {
    bool isPluginDisable(std::string name);
    void disablePlugin(std::string name);
}
#endif //DINGBOT_PLUGIN_H