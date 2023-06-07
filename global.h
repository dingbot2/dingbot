#ifndef DINGBOT_GLOBAL
#define DINGBOT_GLOBAL
#include <boost/filesystem.hpp>
namespace dingbot::global {
    bool getDebug();
    void setDebug(bool d);
    boost::filesystem::path getGlobalPath();
    std::string getDingBotVersion();
}
#endif