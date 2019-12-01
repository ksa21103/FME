/**
 * @file   FMECommandsEngine.cpp
 * @author Kopienko S.A.
 * @brief  Implementation of main operations for FME Disk storage
 */

#include <cstring>

#include "FMECommandsEngine.h"

void throw_wrong_params_count(const FMECmdBase& cmd, size_t paramsCount);

void throw_operation_error(FMEStorage::ErrorCode ec, const TEntryName& name)
{
    std::string str = "Operation error : ";
    switch (ec)
    {
    case FMEStorage::ErrorCode::eSuccess:
        str += " unknown";
        break;

    case FMEStorage::ErrorCode::eNotFound:
        str += " file/folder not found";
        break;

    case FMEStorage::ErrorCode::eExist:
        str += " file/folder already exist";
        break;

    case FMEStorage::ErrorCode::eExistWithDiffType:
        str += " file/folder already exist, but has other type";
        break;

    case FMEStorage::ErrorCode::eReadOnly:
        str += " operation disabled for this folder";
        break;
    }

    if (!name.empty())
        str += " (" + name + ")";

    throw std::runtime_error(str);
}

void throw_folder_not_found(const TEntryPath& folderPath)
{
    std::string str = "Folder not found : ";
    str += std::to_string(folderPath);

    throw std::runtime_error(str);
}

void throw_invalid_entry_type(const TEntryName& name, TEntryBase::EntryKind real)
{
    std::string str = "Invalid entry type of '" + name + "' entry";
    throw std::runtime_error(str);
}

void throw_bad_dest_folder(const TEntryPath& destPath)
{
    std::string str = "Bad destination path (" + std::to_string(destPath) + ")";
    throw std::runtime_error(str);
}

FMECommandsEngine::FMECommandsEngine(FMEStorage& diskStorage)
    : m_diskStorage(diskStorage)
{
}

void FMECommandsEngine::processCommand(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    switch (cmd.getKind())
    {
    case CommandKinds::eCreateDirectory:
        processCreateDirectory(cmd, params);
        return;

    case CommandKinds::eCreateFile:
        processCreateFile(cmd, params);
        return;

    case CommandKinds::eRemove:
        processRemove(cmd, params);
        return;

    case CommandKinds::eCopy:
        processCopy(cmd, params);
        return;

    case CommandKinds::eMove:
        processMove(cmd, params);
        return;
    }

    throw std::runtime_error("Command processing not implemented for " + cmd.getName());
}

void FMECommandsEngine::processCreateDirectory(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    if (params.size() != 1)
        throw_wrong_params_count(cmd, params.size());

    auto folders = parseParam(params.front());
    if (folders.empty())
        throw_wrong_params_count(cmd, params.size());

    const auto folderToCreate = folders.back();
    folders.pop_back();

    EntryFolder* pEntryFolder = m_diskStorage.findFolder(folders);
    if (!pEntryFolder)
        throw_folder_not_found(folders);

    FMEStorage::ErrorCode ec;
    if (!m_diskStorage.createFolder(*pEntryFolder, folderToCreate, ec))
        throw_operation_error(ec, folderToCreate);
}

void FMECommandsEngine::processCreateFile(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    if (params.size() != 1)
        throw_wrong_params_count(cmd, params.size());

    auto folders = parseParam(params.front());
    if (folders.empty())
        throw_wrong_params_count(cmd, params.size());

    const auto fileToCreate = folders.back();
    folders.pop_back();

    EntryFolder* pEntryFolder = m_diskStorage.findFolder(folders);
    if (!pEntryFolder)
        throw_folder_not_found(folders);

    FMEStorage::ErrorCode ec;
    if (!m_diskStorage.createFile(*pEntryFolder, fileToCreate, ec))
    {
        // Notes: if such file already exists with the given path then FME should continue to the next
        //        command in the batch file without any error rising.
        if (ec != FMEStorage::ErrorCode::eExist)
            throw_operation_error(ec, fileToCreate);
    }
}

void FMECommandsEngine::processRemove(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    if (params.size() != 1)
        throw_wrong_params_count(cmd, params.size());

    auto folders = parseParam(params.front());
    if (folders.empty())
        throw_wrong_params_count(cmd, params.size());

    const auto itemToRemove = folders.back();
    folders.pop_back();

    EntryFolder* pEntryFolder = m_diskStorage.findFolder(folders);
    if (!pEntryFolder)
        throw_folder_not_found(folders);

    FMEStorage::ErrorCode ec;
    if (!m_diskStorage.remove(*pEntryFolder, itemToRemove, ec))
        throw_operation_error(ec, itemToRemove);
}

void FMECommandsEngine::processCopy(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    if (params.size() != 2)
        throw_wrong_params_count(cmd, params.size());

    auto folderFrom = parseParam(params[0]);
    if (folderFrom.empty())
        throw_wrong_params_count(cmd, params.size());

    auto folderTo = parseParam(params[1]);
    if (folderTo.empty())
        throw_wrong_params_count(cmd, params.size());

    const auto itemToProcess = folderFrom.back();
    folderFrom.pop_back();

    EntryFolder* pEntryFolderFrom = m_diskStorage.findFolder(folderFrom);
    if (!pEntryFolderFrom)
        throw_folder_not_found(folderFrom);

    auto entryItCopy = m_diskStorage.find(*pEntryFolderFrom, itemToProcess);
    if (entryItCopy == pEntryFolderFrom->entries.end())
        throw_operation_error(FMEStorage::ErrorCode::eNotFound, itemToProcess);

    EntryFolder* pEntryFolderTo = m_diskStorage.findFolder(folderTo);
    if (!pEntryFolderTo)
        throw_folder_not_found(folderTo);

    pEntryFolderTo->entries.push_back((*entryItCopy)->clone());
}

void FMECommandsEngine::processMove(const FMECmdBase& cmd, const TCmdParamsContainer& params)
{
    if (params.size() != 2)
        throw_wrong_params_count(cmd, params.size());

    auto folderFrom = parseParam(params[0]);
    if (folderFrom.empty())
        throw_wrong_params_count(cmd, params.size());

    auto folderTo = parseParam(params[1]);
    if (folderTo.empty())
        throw_wrong_params_count(cmd, params.size());

    if (isSameStartOfPath(folderTo, folderFrom))
        throw_bad_dest_folder(folderTo);

    const auto itemToProcess = folderFrom.back();
    folderFrom.pop_back();

    EntryFolder* pEntryFolderFrom = m_diskStorage.findFolder(folderFrom);
    if (!pEntryFolderFrom)
        throw_folder_not_found(folderFrom);

    EntryFolder* pEntryFolderTo = m_diskStorage.findFolder(folderTo);
    if (!pEntryFolderTo)
        throw_folder_not_found(folderTo);

    auto entryItMove = m_diskStorage.find(*pEntryFolderFrom, itemToProcess);
    if (entryItMove == pEntryFolderFrom->entries.end())
        throw_operation_error(FMEStorage::ErrorCode::eNotFound, itemToProcess);

    auto entryToMove = *entryItMove;
    pEntryFolderFrom->entries.erase(entryItMove);

    pEntryFolderTo->entries.push_back(entryToMove);
}

TEntryPath FMECommandsEngine::parseParam(const TCmdParam& param)
{
    TEntryPath result;

    // Initially file system contains only the root directory marked as “/”.
    result.push_back("/");

    auto item = std::strtok((char*)param.c_str(), FMEStorage::kSeparator.c_str());
    while (item)
    {
        result.push_back(item);
        item = std::strtok(nullptr, FMEStorage::kSeparator.c_str());
    }

    return result;
}

bool FMECommandsEngine::isSameStartOfPath(
        const TEntryPath& pathMain, const TEntryPath& pathTesting)
{
    bool bResult(pathMain.size() >= pathTesting.size());

    if (bResult)
    {
        auto it1 = pathMain.begin();
        auto it2 = pathTesting.begin();
        for (; bResult && it1 != pathMain.end() && it2 != pathTesting.end(); ++it1, ++it2)
        {
            bResult = bResult && *it1 == *it2;
        }
    }

    return bResult;

}
