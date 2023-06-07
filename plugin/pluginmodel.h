#ifndef DINGBOT_PLUGINMODEL_H
#define DINGBOT_PLUGINMODEL_H
#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "apimodel.h"
using std::string;
struct dingbot_plugin_info
{
    string name; // 插件文件名，要求全英文，插件文件夹和主体文件必须为此。例如:group_monitor
    string pluginName; // 插件正式名称，例如:群聊管理插件
    string author; // 插件作者，例如:dinglz
    string description; // 插件介绍，例如:用于管理群聊的插件
};
class BOOST_SYMBOL_VISIBLE dingbot_plugin_model
{
public:
    virtual dingbot_plugin_info getPluginInfo() const = 0;
    virtual void setApiModel(boost::shared_ptr<dingbot::apimodel::Model> _api) = 0;

    virtual void event_private_msg(string message,string sender_id) = 0;
};
#endif //DINGBOT_PLUGINMODEL_H
