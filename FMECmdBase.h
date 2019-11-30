//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMECMDBASE_H
#define FME_FMECMDBASE_H

#include <cstdio>
#include <string>
#include <memory>

enum class FMECommandKind
{
    eCreateDirectory,
    eCreateFile,
    eRemove,
    eCopy,
    eMove
};

using FMECmdParam = std::string;
using FMECmdParams = std::vector<FMECmdParam>;

////////////////////////////////////////////////////////////////////////////////
// class FMECmdBase - base FME commands class
class FMECmdBase
{
public:

    FMECmdBase(FMECommandKind kind, const std::string& cmdName, size_t paramsCount);
    virtual ~FMECmdBase() = default;

    FMECommandKind     getKind() const;
    const std::string& getCmdName() const;
    size_t             getParamsCount() const;

private:

    const FMECommandKind m_kind;
    const std::string m_cmdName;
    const size_t      m_paramsCount;
};
using FMECmdBasePtr = std::shared_ptr<FMECmdBase>;

////////////////////////////////////////////////////////////////////////////////
// md – creates a directory.
// Command format: md <path>
// Notes: md should not create any intermediate directories in the path.
// Examples:
//        a) md /Test – creates a directory called Test in the root directory.
//        b) md /Dir1/Dir2/NewDir – creates a subdirectory “NewDir” if directory “/Dir1/Dir2” exists.
class FMECmdCreateDirectory : public FMECmdBase
{
public:

    FMECmdCreateDirectory();
};

////////////////////////////////////////////////////////////////////////////////
// mf – creates a file.
// Command format: mf <path>
// Notes: if such file already exists with the given path then FME should continue to the next
//        command in the batch file without any error rising.
// Examples:
//        mf /Dir2/Dir3/file.txt – creates a file named file.txt in “/Dir2/Dir3” subdirectory.
class FMECmdCreateFile : public FMECmdBase
{
public:

    FMECmdCreateFile();
};

////////////////////////////////////////////////////////////////////////////////
/// rm – removes a file or a directory with all its contents.
/// Command format: rm <path>
/// Examples:
///        a) rm /Dir2/Dir3 – removes the directory “/Dir2/Dir3”.
///        b) rm /Dir2/Dir3/file.txt – removes the file “file.txt” from the directory “/Dir2/Dir3”.
class FMECmdRemove : public FMECmdBase
{
public:

    FMECmdRemove();
};

////////////////////////////////////////////////////////////////////////////////
// cp – copy an existed directory/file to another location.
// Command format: cp <source> <destination>
// Notes: Program should copy directory with all its content. Destination path should not
//        contain any file name except base-name otherwise FME should raise error (Base-name of
//        “/dir/file.txt” is “file.txt”).
// Examples:
//  a) cp /Dir2/Dir3 /Dir1 – copies directory Dir3 in /Dir2 to /Dir1.
//  b) cp /Dir2/Dir3/file.txt /Dir1 – copies file “file.txt” from /Dir2/Dir3 to /Dir1.
//  c) cp /Dir2/Dir3/file.txt /Dir1/newfile.txt – copies file “file.txt” from /Dir2/Dir3 to /Dir1 and renames it to “newfile.txt”.
class FMECmdCopy : public FMECmdBase
{
public:

    FMECmdCopy();
};

////////////////////////////////////////////////////////////////////////////////
// mv – moves an existing directory/file to another location
// Command format: mv <source> <destination>
class FMECmdMove : public FMECmdBase
{
public:

    FMECmdMove();
};

#endif //FME_FMECMDBASE_H
