#ifndef DINGBOT_APIMODEL_H
#define DINGBOT_APIMODEL_H
#include <string>
using std::string;
namespace dingbot::apimodel {
    class Model {
    public:
        Model();
        explicit Model(int p);
        static string getDingBotVersion();
        void setHttpPort(int p);
    private:
        int http;
        string http_string;
    };
}
#endif