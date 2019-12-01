#include <iostream>
#include <string>
#include <csignal>
#include <fstream>

#include "FMECommandsParser.h"
#include "FMECommandsEngine.h"
#include "FMEStoragePresenter.h"

void signal_handler(int signal)
{
    std::cout << std::endl;
    std::cout << "ERROR: signal " << signal << " received - exit!" << std::endl;
    exit(signal);
}

/**
 * Worker function of FME application
 * @param is - stream for read source text with FME commands
 * @param disk - FME disk storage
 * @return result code: 0 if success, -1 if errors
 */
int worker(std::istream& is, FMEStorage& disk)
{
    std::string strCmd;
    size_t lineNo = 0;
    try
    {
        FMECommandsEngine cmdEngine(disk);

        FMECommandsParser cmdParser;
        while (std::getline(is >> std::ws, strCmd))
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
    int result = worker(cmdFile.is_open() ? cmdFile : std::cin, disk);

    if (!result)
    {
        FMEStoragePresenter presenter(std::cout);
        presenter.show(disk);
    }

    return result;
}
