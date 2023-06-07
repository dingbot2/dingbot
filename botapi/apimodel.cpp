#include "apimodel.h"
#include "../global.h"
#include "../logger.h"
namespace dingbot::apimodel {
    class ModelActive:public Model {
    public:
        ModelActive()
        {
            this->http = 80;
            this->http_string = "80";
        }
        explicit ModelActive(int p)
        {
            this->http = p;
            this->http_string = std::to_string(p);
        }
        string getDingBotVersion() override
        {
            return dingbot::global::getDingBotVersion();
        }
        void setHttpPort(int p) override
        {
            this->http = p;
            this->http_string = std::to_string(p);
        }
        void setPluginName(string name) override
        {
            this->pluginName = name;
        }
        void log_info(string text) override
        {
            dingbot::logger::GetConsoleLogger()->info("[{0}] {1}",this->pluginName.c_str(),text.c_str());
        }
        void log_debug(std::string text) override
        {
            dingbot::logger::GetConsoleLogger()->debug("[{0}] {1}",this->pluginName.c_str(),text.c_str());
        }
    private:
        int http;
        string http_string;
        string pluginName;
    };
    boost::shared_ptr<Model > makeInstance()
    {
        return boost::shared_ptr<ModelActive>(new ModelActive);
    }
}