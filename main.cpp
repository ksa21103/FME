#include <iostream>
#include <string>
#include <csignal>

#include "FMECommandsParser.h"
#include "FMECommandsEngine.h"
#include "FMEStoragePresenter.h"

void signal_handler(int signal)
{
    std::cout << std::endl;
    std::cout << "ERROR: signal " << signal << " received - exit!" << std::endl;
    exit(signal);
}

int worker(FMEStorage& disk)
{
    std::string strCmd;
    size_t lineNo = 0;
    try
    {
        FMECommandsEngine cmdEngine(disk);

        FMECommandsParser cmdParser;
        while (std::getline(std::cin >> std::ws, strCmd))
        {
            ++lineNo;

            if (strCmd.empty())
                continue;

            TCmdParamsContainer cmdParams;
            auto cmd = cmdParser.parse(strCmd, cmdParams);
            if (!cmd)
                throw std::runtime_error("Unknown command: " + strCmd);

            cmdEngine.processCommand(*cmd, cmdParams);
        }
    }
    catch (const std::exception& exc)
    {
        std::cout << "ERROR: " << exc.what() << std::endl;
        std::cout << "       in string " << lineNo << " : " << strCmd << std::endl;
        return -1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    std::signal(SIGINT, signal_handler);

    FMEStorage disk;
    int result = worker(disk);

    if (!result)
    {
        FMEStoragePresenter presenter(std::cout);
        presenter.show(disk);
    }

    return result;
}
