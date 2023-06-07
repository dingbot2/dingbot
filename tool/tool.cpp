#include "tool.h"
#include "../logger.h"

namespace dingbot::tool {
    void createPath(const boost::filesystem::path& path)
    {
        if (!boost::filesystem::exists(path))
        {
            boost::filesystem::create_directory(path);
            dingbot::logger::GetConsoleLogger()->debug("创建文件夹:{0}",path.string().c_str());
        }
    }
}