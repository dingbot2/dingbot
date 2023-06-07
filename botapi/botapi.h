#ifndef DINGBOT_BOTAPI_H
#define DINGBOT_BOTAPI_H
#include "apimodel.h"
namespace dingbot::botapi {
    void init(int p);
    dingbot::apimodel::Model get();
}
#endif //DINGBOT_BOTAPI_H
