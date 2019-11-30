//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMESTORAGE_H
#define FME_FMESTORAGE_H

#include <vector>
#include <memory>
#include <string>

class EntryBase;
using EntryBasePtr = std::shared_ptr<EntryBase>;

////////////////////////////////////////////////////////////////////////////////
struct EntryBase
{
    enum class EntryKind
    {
        eFolder,
        eFile
    };

    EntryBase(const EntryKind& _kind, const std::string& _name, bool _redOnly = false)
        : kind(_kind),
          name(_name),
          readOnly(_redOnly)
    {
    }

    virtual ~EntryBase() = default;

    virtual EntryBasePtr clone() = 0;

    const EntryKind   kind;             //< Entry kind (file, folder,...)
    const std::string name;             //< Entry name
    const bool        readOnly = false; //< Readonly entry
};
using Entries = std::vector<EntryBasePtr>;

////////////////////////////////////////////////////////////////////////////////
struct EntryFile : EntryBase
{
    EntryFile(const std::string& name, bool readOnly = false)
        : EntryBase(EntryBase::EntryKind::eFile, name, readOnly)
    {
    }

    virtual EntryBasePtr clone() override;
};

////////////////////////////////////////////////////////////////////////////////
struct EntryFolder : EntryBase
{
    EntryFolder(const std::string& name, bool readOnly = false)
        : EntryBase(EntryBase::EntryKind::eFolder, name, readOnly)
    {
    }

    virtual EntryBasePtr clone();

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

    static const std::string kSeparator;

    FMEStorage();

    const EntryFolder& root() const;
    EntryFolder& root();

    bool              exist(EntryFolder& folder, const std::string& name);
    bool              exist(EntryFolder& folder, const std::string& name, EntryBase::EntryKind& entryKind);
    Entries::iterator find (EntryFolder& folder, const std::string& name);

    EntryFolder*      findFolder(const std::vector<std::string>& folders);

    enum class ErrorCode
    {
        eSuccess,
        eNotFound,
        eExist,
        eExistWithDiffType,
        eReadOnly
    };

    bool createFile  (EntryFolder& folder, const std::string& name, ErrorCode& ec);
    bool createFolder(EntryFolder& folder, const std::string& name, ErrorCode& ec);
    bool remove      (EntryFolder& folder, const std::string& name, ErrorCode& ec);

private:

    EntryFolder m_rootContainer;
};

#endif //FME_FMESTORAGE_H
