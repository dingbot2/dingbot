#ifndef DINGBOT_APIMODEL_H
#define DINGBOT_APIMODEL_H
#include <string>
#include <boost/shared_ptr.hpp>
using std::string;
namespace dingbot::apimodel {
    class Model {
    public:
        virtual string getDingBotVersion() = 0;
        virtual void setHttpPort(int p) = 0;
        virtual void setPluginName(string name) = 0;
        virtual void log_info(string text) = 0;
        virtual void log_debug(string text) = 0;
    };
    boost::shared_ptr<Model > makeInstance();
}
#endif