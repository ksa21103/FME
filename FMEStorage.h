/**
 * @file   FMEStorage.h
 * @author Kopienko S.A.
 * @brief  Declaration of FME disk storage
 */

#ifndef FME_FMESTORAGE_H
#define FME_FMESTORAGE_H

#include <utility>
#include <vector>
#include <memory>
#include <string>

/// class TEntryBase - describes base type of FME disk storage
class TEntryBase;
using TEntryBasePtr = std::shared_ptr<TEntryBase>;

/// TEntryName - describes FME disk storage entry name
using TEntryName = std::string;

/// TEntryPath - describes FME disk storage entry path
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
}

////////////////////////////////////////////////////////////////////////////////
/// class TEntryBase - describes base type of FME disk storage
struct TEntryBase
{
    /// enum EntryKind - describe FME disk storage entry kinds
    enum class EntryKind
    {
        eFolder,
        eFile
    };

    /// Constructor
    ///
    /// \param _kind - FME disk storage entry kind
    /// \param _name - FME disk storage entry name
    /// \param _redOnly - FME disk storage entry kind readonly state
    TEntryBase(const EntryKind& _kind, TEntryName  _name, bool _redOnly = false)
        : kind(_kind),
          name(std::move(_name)),
          readOnly(_redOnly)
    {
    }

    virtual ~TEntryBase() = default;

    /// Deep copy of FME disk storage entry
    /// \return - new object
    virtual TEntryBasePtr clone() = 0;

    const EntryKind  kind;             //< Entry kind (file, folder,...)
    const TEntryName name;             //< Entry name
    const bool       readOnly = false; //< Readonly state
};
using Entries = std::vector<TEntryBasePtr>;

////////////////////////////////////////////////////////////////////////////////
/// struct EntryFile - describe FME disk storage entry file
struct EntryFile : TEntryBase
{
    /// Constructor
    ///
    /// \param name - name of file
    /// \param readOnly - readonly state
    explicit EntryFile(const TEntryName& name, bool readOnly = false)
        : TEntryBase(TEntryBase::EntryKind::eFile, name, readOnly)
    {
    }

    /// Deep copy of FME disk storage entry
    virtual TEntryBasePtr clone() override;
};

////////////////////////////////////////////////////////////////////////////////
/// struct EntryFolder - describe FME disk storage entry folder
struct EntryFolder : TEntryBase
{
    /// Constructor
    /// \param name - name of folder
    /// \param readOnly - readonly state
    explicit EntryFolder(const TEntryName& name, bool readOnly = false)
        : TEntryBase(TEntryBase::EntryKind::eFolder, name, readOnly)
    {
    }

    /// Deep copy of FME disk storage entry
    virtual TEntryBasePtr clone();

    Entries entries;    //< Child entries
};

////////////////////////////////////////////////////////////////////////////////
/// struct EntryFolderRoot - describe FME disk storage root folder
///     Name of this folder is "/"
///     This folder is read only
struct EntryFolderRoot : EntryFolder
{
    EntryFolderRoot()
        : EntryFolder("/", true)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////
/// class FMEStorage - FME file system storage
class FMEStorage
{
public:

    static const TEntryName kSeparator;

    FMEStorage();

    /// Get root FME folder
    /// \return - root FME folder
    [[nodiscard]] const EntryFolder& root() const;
    EntryFolder& root();

    /// Check than specified folder contain specified entry
    ///
    /// \param folder - describe full path to folder for checking
    /// \param name - name of checking entry
    /// \return true - if folder contains entry; false - otherwise
    bool              exist(EntryFolder& folder, const TEntryName& name);

    /// Check than specified folder contain specified entry
    ///
    /// \param folder - describe full path to folder for checking
    /// \param name - name of checking entry
    /// \param entryKind - return type of checking entry, if it was found
    /// \return true - if folder contains entry; false - otherwise
    bool              exist(EntryFolder& folder, const TEntryName& name, TEntryBase::EntryKind& entryKind);

    /// Get operation iterator
    ///
    /// \param folder - describe full path to folder for checking
    /// \param name - name of checking entry
    /// \return - iterafor for entry; end() - if not found
    Entries::iterator find (EntryFolder& folder, const TEntryName& name);

    /// Find folder
    /// \param folders - full path to folder and it's name
    /// \return - pointer to folder object - if found; nullptr - otherwise
    ///
    /// \exception std::runtime_error - if specified folder not found
    EntryFolder*      findFolder(const TEntryPath& folders);

    /// enum ErrorCode - describe error codes
    enum class ErrorCode
    {
        eSuccess,
        eNotFound,
        eExist,
        eExistWithDiffType,
        eReadOnly
    };

    /// Create file entry
    /// \param folder - path to parent folder
    /// \param name - name of creating file
    /// \param ec - filled by error code
    /// \return true - if operation success, false - otherwise
    bool createFile  (EntryFolder& folder, const TEntryName& name, ErrorCode& ec);

    /// Create folder entry
    /// \param folder - path to parent folder
    /// \param name - name of creating folder
    /// \param ec - filled by error code
    /// \return true - if operation success, false - otherwise
    bool createFolder(EntryFolder& folder, const TEntryName& name, ErrorCode& ec);

    /// Erase entry
    /// \param folder - path to parent folder
    /// \param name - name of entry to erase
    /// \param ec - filled by error code
    /// \return true - if operation success, false - otherwise
    bool remove      (EntryFolder& folder, const TEntryName& name, ErrorCode& ec);

private:

    EntryFolder m_rootContainer;    ///< Container for root FME folder
};

#endif //FME_FMESTORAGE_H
