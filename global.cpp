#include "global.h"

namespace dingbot::global {
    bool debug = false;
    bool getDebug()
    {
        return debug;
    }
    void setDebug(bool d)
    {
        debug = d;
    }
    boost::filesystem::path getGlobalPath()
    {
        return boost::filesystem::current_path();
    }

    std::string version = "1.0 beta";
    std::string getDingBotVersion()
    {
        return version;
    }
}