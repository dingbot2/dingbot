#include "logger.h"
#include "global.h"

namespace dingbot::logger {
    void InitLogger()
    {
        spdlog::stdout_color_mt("dingbot");
        if(dingbot::global::getDebug())
        {
            GetConsoleLogger()->set_level(spdlog::level::debug);
            GetConsoleLogger()->debug("已启动调试模式！");
        }
        else
        {
            GetConsoleLogger()->set_level(spdlog::level::info);
        }
        GetConsoleLogger()->info("Logger初始化成功！");
    }
    std::shared_ptr<spdlog::logger> GetConsoleLogger()
    {
        return spdlog::get("dingbot");
    }
}