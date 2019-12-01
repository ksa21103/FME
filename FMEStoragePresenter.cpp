/**
 * @file   FMEStoragePresenter.cpp
 * @author Kopienko S.A.
 * @brief  Implementation of FME storage visualisation
 */

#include <iostream>

#include "FMEStoragePresenter.h"

static std::string kLevelPrefix = "| ";

FMEStoragePresenter::FMEStoragePresenter(std::ostream& os)
    : m_os(os)
{
}

void FMEStoragePresenter::show(const FMEStorage& disk)
{
    m_os << "/" << std::endl;
    show(disk.root(), "");
}

void FMEStoragePresenter::show(const EntryFolder& folder, const std::string& prefix)
{
    //  /
    //  | _Dir1
    //  | |_Dir2
    //  | | |_Dir3
    //  | | |_readme.txt
    //  | |_EDir4
    //  | | |_temp.dat

    std::vector<TEntryBasePtr> sortedEntries;
    sortedEntries.reserve(folder.entries.size());

    std::copy(folder.entries.begin(), folder.entries.end(), std::back_inserter(sortedEntries));

    std::sort(sortedEntries.begin(), sortedEntries.end(),
              [](TEntryBasePtr& entry1, TEntryBasePtr& entry2)
              {
                  return entry1->kind < entry2->kind
                         || (entry1->kind == entry2->kind
                             && entry1->name < entry2->name);
              }
             );

    for (const auto& item : sortedEntries)
    {
        m_os << prefix << kLevelPrefix << item->name << std::endl;

        switch (item->kind)
        {
        case TEntryBase::EntryKind::eFolder:
            {
                auto thisFolder = *static_cast<EntryFolder*>(item.get());
                show(thisFolder, prefix + kLevelPrefix);
            }
            break;

        case TEntryBase::EntryKind::eFile:
            break;
        }
    }
}
