/**
 * @file   FMECommandsEngine.h
 * @author Kopienko S.A.
 * @brief  Declaration of main FME disk storage operations
 */


#ifndef FME_FMECOMMANDSENGINE_H
#define FME_FMECOMMANDSENGINE_H

#include "FMECmdBase.h"
#include "FMEStorage.h"

////////////////////////////////////////////////////////////////////////////////
// class FMECommandsEngine - implements of main operations for FME Disk storage
class FMECommandsEngine
{
public:

    /// Constructor
    ///
    /// \param diskStorage - FME disk storage
    explicit FMECommandsEngine(FMEStorage& diskStorage);

    /// Execute FME console command
    ///
    /// \param cmd - FME console command
    /// \param params - params for FME console command
    ///
    /// \exception std::runtime_error - if error occurred or specified command is unknown
    void processCommand(const FMECmdBase& cmd, const TCmdParamsContainer& params);

private:

    /// Implementation of create directory command
    /// \param cmd - create directory command info
    /// \param params - command params
    /// \see @FMECmdCreateDirectory
    ///
    /// \exception std::runtime_error - if error occurred
    void processCreateDirectory(const FMECmdBase& cmd, const TCmdParamsContainer& params);

    /// Implementation of create directory command
    /// \param cmd - create file command info
    /// \param params - command params
    /// \see @FMECmdCreateFile
    ///
    /// \exception std::runtime_error - if error occurred
    void processCreateFile     (const FMECmdBase& cmd, const TCmdParamsContainer& params);

    /// Implementation of erse file/folder command
    /// \param cmd - erse file/folder command command info
    /// \param params - command params
    /// \see @FMECmdRemove
    ///
    /// \exception std::runtime_error - if error occurred
    void processRemove         (const FMECmdBase& cmd, const TCmdParamsContainer& params);

    /// Implementation of copy file/folder command
    /// \param cmd - copy file/folder command command info
    /// \param params - command params
    /// \see @FMECmdCopy
    ///
    /// \exception std::runtime_error - if error occurred
    void processCopy           (const FMECmdBase& cmd, const TCmdParamsContainer& params);

    /// Implementation of move file/folder command
    /// \param cmd - move file/folder command command info
    /// \param params - command params
    /// \see @FMECmdMove
    ///
    /// \exception std::runtime_error - if error occurred
    void processMove           (const FMECmdBase& cmd, const TCmdParamsContainer& params);

    /// Parse param to FME path
    /// \param param - FMC console command param
    /// \return - FME path
    static TEntryPath parseParam(const TCmdParam& param);

    /// Check that main path start from testing path
    /// \param pathMain - main path
    /// \param pathTesting - testing path
    /// \return - true - if main path start from testing path; false - otherwise
    [[nodiscard]] static bool isSameStartOfPath(const TEntryPath& pathMain, const TEntryPath& pathTesting);

private:

    FMEStorage& m_diskStorage;      //< Ref to FME disk storage
};

#endif //FME_FMECOMMANDSENGINE_H
