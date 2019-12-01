/**
 * @file   FMECmdBase.cpp
 * @author Kopienko S.A.
 * @brief  Implementation of FME console commands
 */


#include "FMECmdBase.h"

static std::string kCmdNameCreateDirectory = "md";
static std::string kCmdNameCreateFile      = "mf";
static std::string kCmdNameRemove          = "rm";
static std::string kCmdNameCopy            = "cp";
static std::string kCmdNameMove            = "mv";

FMECmdBase::FMECmdBase(CommandKinds kind, const std::string& cmdName, size_t paramsCount)
    : m_kind(kind),
      m_cmdName(cmdName),
      m_paramsCount(paramsCount)
{
}

const std::string& FMECmdBase::getName() const
{
    return m_cmdName;
}

size_t FMECmdBase::getParamsCount() const
{
    return m_paramsCount;
}

CommandKinds FMECmdBase::getKind() const
{
    return m_kind;
}

FMECmdCreateDirectory::FMECmdCreateDirectory()
    : FMECmdBase(CommandKinds::eCreateDirectory, kCmdNameCreateDirectory, 1)
{
}

FMECmdCreateFile::FMECmdCreateFile()
    : FMECmdBase(CommandKinds::eCreateFile, kCmdNameCreateFile, 1)
{
}

FMECmdRemove::FMECmdRemove()
    : FMECmdBase(CommandKinds::eRemove, kCmdNameRemove, 1)
{
}


FMECmdCopy::FMECmdCopy()
    : FMECmdBase(CommandKinds::eCopy, kCmdNameCopy, 2)
{
}

FMECmdMove::FMECmdMove()
    : FMECmdBase(CommandKinds::eMove, kCmdNameMove, 2)
{
}
