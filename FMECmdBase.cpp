//
// Created by Копиенко Сергей on 30.11.2019.
//

#include "FMECmdBase.h"

static std::string kCmdNameCreateDirectory = "md";
static std::string kCmdNameCreateFile      = "mf";
static std::string kCmdNameRemove          = "rm";
static std::string kCmdNameCopy            = "cp";
static std::string kCmdNameMove            = "mv";

FMECmdBase::FMECmdBase(FMECommandKind kind, const std::string& cmdName, size_t paramsCount)
    : m_kind(kind),
      m_cmdName(cmdName),
      m_paramsCount(paramsCount)
{
}

const std::string& FMECmdBase::getCmdName() const
{
    return m_cmdName;
}

size_t FMECmdBase::getParamsCount() const
{
    return m_paramsCount;
}

FMECommandKind FMECmdBase::getKind() const
{
    return m_kind;
}

FMECmdCreateDirectory::FMECmdCreateDirectory()
    : FMECmdBase(FMECommandKind::eCreateDirectory, kCmdNameCreateDirectory, 1)
{
}

FMECmdCreateFile::FMECmdCreateFile()
    : FMECmdBase(FMECommandKind::eCreateFile, kCmdNameCreateFile, 1)
{
}

FMECmdRemove::FMECmdRemove()
    : FMECmdBase(FMECommandKind::eRemove, kCmdNameRemove, 1)
{
}


FMECmdCopy::FMECmdCopy()
    : FMECmdBase(FMECommandKind::eCopy, kCmdNameCopy, 2)
{
}

FMECmdMove::FMECmdMove()
    : FMECmdBase(FMECommandKind::eMove, kCmdNameMove, 2)
{
}
