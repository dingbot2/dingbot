#ifndef DINGBOT_BOTAPI_H
#define DINGBOT_BOTAPI_H
#include "apimodel.h"
namespace dingbot::botapi {
    void init(int p);
    boost::shared_ptr<dingbot::apimodel::Model> get();
}
#endif //DINGBOT_BOTAPI_H
