#include <iostream>
#include <string>
#include <csignal>
#include <fstream>

#include "FMEMain.h"

void signal_handler(int signal)
{
    std::cout << std::endl;
    std::cout << "ERROR: signal " << signal << " received - exit!" << std::endl;
    exit(signal);
}

int main(int argc, char** argv)
{
    std::signal(SIGINT, signal_handler);

    std::ifstream cmdFile;
    if (argc > 1)
    {
        cmdFile.open(argv[1]);
        if (!cmdFile.is_open())
        {
            std::cout << "ERROR: unable to open file " << argv[1] << " - exit!" << std::endl;
            exit(-1);
        }
    }

    FMEStorage disk;
    int result = FMEMain::worker(cmdFile.is_open() ? cmdFile : std::cin, std::cout, disk);

    return result;
}
