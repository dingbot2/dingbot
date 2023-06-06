#include "logger.h"
#include "cmdline.h"

int main(int argc,char **argv)
{
    dingbot::cmdline::parse(argc,argv);
    dingbot::logger::InitLogger();
}