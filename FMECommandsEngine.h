//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMECOMMANDSENGINE_H
#define FME_FMECOMMANDSENGINE_H

#include "FMECmdBase.h"
#include "FMEStorage.h"

////////////////////////////////////////////////////////////////////////////////
class FMECommandsEngine
{
public:

    FMECommandsEngine(FMEStorage& diskStorage);

    void processCommand(const FMECmdBase& cmd, const FMECmdParams& params);

private:

    void processCreateDirectory(const FMECmdBase& cmd, const FMECmdParams& params);
    void processCreateFile     (const FMECmdBase& cmd, const FMECmdParams& params);
    void processRemove         (const FMECmdBase& cmd, const FMECmdParams& params);
    void processCopy           (const FMECmdBase& cmd, const FMECmdParams& params);
    void processMove           (const FMECmdBase& cmd, const FMECmdParams& params);

    std::vector<std::string> parseParam(const FMECmdParam& param);

private:

    FMEStorage& m_diskStorage;
};

#endif //FME_FMECOMMANDSENGINE_H
