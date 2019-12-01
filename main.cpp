#include <iostream>
#include <string>

#include "FMECommandsParser.h"
#include "FMECommandsEngine.h"
#include "FMEStoragePresenter.h"

int main(int argc, char** argv)
{
    FMEStorage disk;

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

    FMEStoragePresenter presenter(std::cout);
    presenter.show(disk);

    return 0;
}
