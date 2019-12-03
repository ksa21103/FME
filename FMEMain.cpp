//
// Created by Копиенко Сергей on 03.12.2019.
//

#include <exception>

#include "FMEMain.h"
#include "FMECommandsEngine.h"
#include "FMECommandsParser.h"
#include "FMEStoragePresenter.h"

int FMEMain::worker(std::istream &streamIn, std::ostream &streamOut, FMEStorage &disk)
{
    std::string strCmd;
    size_t lineNo = 0;
    try
    {
        FMECommandsEngine cmdEngine(disk);

        FMECommandsParser cmdParser;
        while (std::getline(streamIn >> std::ws, strCmd))
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
        streamOut << "ERROR: " << exc.what() << std::endl;
        streamOut << "       in string " << lineNo << " : " << strCmd << std::endl;
        return -1;
    }

    FMEStoragePresenter presenter(streamOut);
    presenter.show(disk);

    return 0;
}
