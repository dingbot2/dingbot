#ifndef DINGBOT_TOOL_H
#define DINGBOT_TOOL_H
#include <boost/filesystem.hpp>
namespace dingbot::tool {
    void createPath(const boost::filesystem::path& path);
}
#endif