#include "botapi.h"
namespace dingbot::botapi {
    boost::shared_ptr<dingbot::apimodel::Model> _model;

    void init(int p)
    {
        _model = dingbot::apimodel::makeInstance();
    }

    boost::shared_ptr<dingbot::apimodel::Model> get()
    {
        return _model;
    }
}