#include "apimodel.h"
#include "../global.h"
namespace dingbot::apimodel {
    Model::Model()
    {
        this->http = 80;
        this->http_string = "80";
    }
    Model::Model(int p)
    {
        this->http = p;
        this->http_string = std::to_string(p);
    }
    string Model::getDingBotVersion() {
        return dingbot::global::getDingBotVersion();
    }
    void Model::setHttpPort(int p)
    {
        this->http = p;
        this->http_string = std::to_string(p);
    }
}