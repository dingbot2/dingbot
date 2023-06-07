#include "botapi.h"
namespace dingbot::botapi {
    dingbot::apimodel::Model _model;

    void init(int p)
    {
        _model = dingbot::apimodel::Model(p);
    }

    dingbot::apimodel::Model get()
    {
        return _model;
    }
}