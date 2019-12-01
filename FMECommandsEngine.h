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

    void processCommand(const FMECmdBase& cmd, const TCmdParamsContainer& params);

private:

    void processCreateDirectory(const FMECmdBase& cmd, const TCmdParamsContainer& params);
    void processCreateFile     (const FMECmdBase& cmd, const TCmdParamsContainer& params);
    void processRemove         (const FMECmdBase& cmd, const TCmdParamsContainer& params);
    void processCopy           (const FMECmdBase& cmd, const TCmdParamsContainer& params);
    void processMove           (const FMECmdBase& cmd, const TCmdParamsContainer& params);

    TEntryPath parseParam(const TCmdParam& param);
    bool    isSameStartOfPath(const TEntryPath pathMain, const TEntryPath& pathTesting) const;

private:

    FMEStorage& m_diskStorage;
};

#endif //FME_FMECOMMANDSENGINE_H
