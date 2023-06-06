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
}