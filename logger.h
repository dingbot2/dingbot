#ifndef DINGBOT_LOGGER_H
#define DINGBOT_LOGGER_H
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
namespace dingbot::logger {
        void InitLogger();
        std::shared_ptr<spdlog::logger> GetConsoleLogger();
}
#endif //DINGBOT_LOGGER_H