//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMESTORAGE_H
#define FME_FMESTORAGE_H

#include <vector>
#include <memory>
#include <string>

class TEntryBase;
using TEntryBasePtr = std::shared_ptr<TEntryBase>;

using TEntryName = std::string;
using TEntryPath = std::vector<TEntryName>;

namespace std
{
    inline
    std::string to_string(const TEntryPath& path)
    {
        std::string text;

        for (const auto& item : path)
        {
            if (!text.empty() && text != "/")
                text += "/";
            text += item;
        }

        return text;
    }
};

////////////////////////////////////////////////////////////////////////////////
struct TEntryBase
{
    enum class EntryKind
    {
        eFolder,
        eFile
    };

    TEntryBase(const EntryKind& _kind, const TEntryName& _name, bool _redOnly = false)
        : kind(_kind),
          name(_name),
          readOnly(_redOnly)
    {
    }

    virtual ~TEntryBase() = default;

    virtual TEntryBasePtr clone() = 0;

    const EntryKind    kind;             //< Entry kind (file, folder,...)
    const TEntryName name;             //< Entry name
    const bool         readOnly = false; //< Readonly entry
};
using Entries = std::vector<TEntryBasePtr>;

////////////////////////////////////////////////////////////////////////////////
struct EntryFile : TEntryBase
{
    EntryFile(const TEntryName& name, bool readOnly = false)
        : TEntryBase(TEntryBase::EntryKind::eFile, name, readOnly)
    {
    }

    virtual TEntryBasePtr clone() override;
};

////////////////////////////////////////////////////////////////////////////////
struct EntryFolder : TEntryBase
{
    EntryFolder(const TEntryName& name, bool readOnly = false)
        : TEntryBase(TEntryBase::EntryKind::eFolder, name, readOnly)
    {
    }

    virtual TEntryBasePtr clone();

    Entries entries;    //< Child entries
};

////////////////////////////////////////////////////////////////////////////////
struct EntryFolderRoot : EntryFolder
{
    EntryFolderRoot()
        : EntryFolder("/", true)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////
// FME file system storage
class FMEStorage
{
public:

    static const TEntryName kSeparator;

    FMEStorage();

    const EntryFolder& root() const;
    EntryFolder& root();

    bool              exist(EntryFolder& folder, const TEntryName& name);
    bool              exist(EntryFolder& folder, const TEntryName& name, TEntryBase::EntryKind& entryKind);
    Entries::iterator find (EntryFolder& folder, const TEntryName& name);

    EntryFolder*      findFolder(const TEntryPath& folders);

    enum class ErrorCode
    {
        eSuccess,
        eNotFound,
        eExist,
        eExistWithDiffType,
        eReadOnly
    };

    bool createFile  (EntryFolder& folder, const TEntryName& name, ErrorCode& ec);
    bool createFolder(EntryFolder& folder, const TEntryName& name, ErrorCode& ec);
    bool remove      (EntryFolder& folder, const TEntryName& name, ErrorCode& ec);

private:

    EntryFolder m_rootContainer;
};

#endif //FME_FMESTORAGE_H
