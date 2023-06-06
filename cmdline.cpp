#include "cmdline.h"
#include <boost/program_options.hpp>
#include "global.h"
#include <iostream>
namespace dingbot::cmdline {
    void parse(int argc,char **argv)
    {
        namespace po = boost::program_options;
        po::options_description desc("dingbot");
        desc.add_options()("debug","启动调试模式")
                ("help","帮助");
        po::variables_map vm;
        po::store(po::parse_command_line(argc,argv,desc),vm);
        po::notify(vm);
        if(vm.count("help"))
        {
            std::cout << desc << std::endl;
            exit(0);
        }
        if(vm.count("debug"))
        {
            dingbot::global::setDebug(true);
        }
    }
}