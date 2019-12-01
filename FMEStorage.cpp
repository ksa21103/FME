/**
 * @file   FMEStorage.cpp
 * @author Kopienko S.A.
 * @brief  Implementation of FME disk storage
 */

#include <algorithm>

#include "FMEStorage.h"

const TEntryName FMEStorage::kSeparator = "/";

FMEStorage::FMEStorage()
    : m_rootContainer("")
{
    m_rootContainer.entries.push_back(std::make_shared<EntryFolderRoot>());
}

const EntryFolder& FMEStorage::root() const
{
    return *static_cast<const EntryFolder*>(m_rootContainer.entries.front().get());
}

EntryFolder& FMEStorage::root()
{
    return *static_cast<EntryFolder*>(m_rootContainer.entries.front().get());
}

bool
FMEStorage::exist(EntryFolder& folder, const TEntryName& name)
{
    TEntryBase::EntryKind entryKind;
    return exist(folder, name, entryKind);
}

bool
FMEStorage::exist(EntryFolder& folder, const TEntryName& name, TEntryBase::EntryKind& entryKind)
{
    bool bResult(false);

    auto it = find(folder, name);
    if (it != folder.entries.end())
    {
        entryKind = (*it)->kind;
        bResult = true;
    }

    return bResult;
}

Entries::iterator
FMEStorage::find(EntryFolder& folder, const TEntryName& name)
{
    return std::find_if(folder.entries.begin(), folder.entries.end(),
                        [&name](const auto& item)
                        {
                            return item->name == name;
                        });
}

EntryFolder*
FMEStorage::findFolder(const TEntryPath& folders)
{
    if (folders.empty())
        return &m_rootContainer;

    if (folders.front() != root().name)
        return nullptr;

    EntryFolder* pEntryFolder = &root();
    for (auto it = folders.begin() + 1; it != folders.end(); ++it)
    {
        if (!exist(*pEntryFolder, *it))
            throw std::runtime_error("Folder not found " + *it);

        auto entryIt = find(*pEntryFolder, *it);
        auto pEntryBase = entryIt->get();
        if (pEntryBase->kind != TEntryBase::EntryKind::eFolder)
            return nullptr;

        pEntryFolder = static_cast<EntryFolder*>(pEntryBase);
    }

    return pEntryFolder;
}

bool
FMEStorage::createFile(EntryFolder& folder, const TEntryName& name, FMEStorage::ErrorCode& ec)
{
    TEntryBase::EntryKind entryKind;
    if (exist(folder, name, entryKind))
    {
        ec = entryKind == TEntryBase::EntryKind::eFile ? ErrorCode::eExist : ErrorCode::eExistWithDiffType;
        return false;
    }

    folder.entries.emplace_back(std::make_shared<EntryFile>(name));
    ec = ErrorCode::eSuccess;

    return true;
}

bool
FMEStorage::createFolder(EntryFolder& folder, const TEntryName& name, FMEStorage::ErrorCode& ec)
{
    if (&folder == &root() && name == "/")
    {
        ec = ErrorCode::eExist;
        return false;
    }

    TEntryBase::EntryKind entryKind;
    if (exist(folder, name, entryKind))
    {
        ec = entryKind == TEntryBase::EntryKind::eFolder ? ErrorCode::eExist : ErrorCode::eExistWithDiffType;
        return false;
    }

    folder.entries.emplace_back(std::make_shared<EntryFolder>(name));
    ec = ErrorCode::eSuccess;

    return true;
}

bool
FMEStorage::remove(EntryFolder& folder, const TEntryName& name, FMEStorage::ErrorCode& ec)
{
    auto it = find(folder, name);
    if (it == folder.entries.end())
    {
        ec = ErrorCode::eNotFound;
        return false;
    }

    if ((*it)->readOnly)
    {
        ec = ErrorCode::eReadOnly;
        return false;
    }

    folder.entries.erase(it);

    ec = ErrorCode::eSuccess;
    return true;
}

TEntryBasePtr EntryFile::clone()
{
    return std::make_shared<EntryFile>(name, readOnly);
}

TEntryBasePtr EntryFolder::clone()
{
    auto newFolder = std::make_shared<EntryFolder>(name, readOnly);

    std::transform(entries.begin(), entries.end(),
                   std::back_inserter(newFolder->entries),
                   [](TEntryBasePtr pEntry) { return pEntry->clone(); });

    return newFolder;
}
