/**
 * @file   FMECommandsParser.cpp
 * @author Kopienko S.A.
 * @brief  Implementation of command line parser
 */


#include "FMECommandsParser.h"

void throw_unknown_command()
{
    throw std::runtime_error("Unknown command");
}

void throw_wrong_params_count(const FMECmdBase& cmd, size_t paramsCount)
{
    std::string errorStr = "Invalid params count for command " + cmd.getName() + " : ";
    errorStr += std::to_string(paramsCount);
    errorStr += " (required : " + std::to_string(cmd.getParamsCount()) + ")";

    throw std::runtime_error(errorStr);
}

FMECommandsParser::FMECommandsParser()
{
    registerCommand<FMECmdCreateDirectory>();
    registerCommand<FMECmdCreateFile>();
    registerCommand<FMECmdRemove>();
    registerCommand<FMECmdCopy>();
    registerCommand<FMECmdMove>();
}

FMECmdBasePtr FMECommandsParser::parse(const std::string& strCmd, TCmdParamsContainer& cmdParams)
{
    cmdParams.clear();

    auto parts = parseStr(strCmd);
    if (parts.empty())
        throw_unknown_command();

    auto it = m_commands.find(parts.front());
    if (it == m_commands.end())
        throw_unknown_command();

    const auto& cmd = *it->second;
    if (cmd.getParamsCount() != (parts.size() - 1))
        throw_wrong_params_count(cmd, parts.size() - 1);

    std::copy(parts.begin() + 1, parts.end(),
              std::back_insert_iterator(cmdParams));

    return it->second;
}

std::string::size_type skipSpaces(const std::string& str, size_t pos)
{
    if (pos == std::string::npos)
        return pos;

    for (auto i = pos; i < str.length(); ++i)
    {
        if (!std::isspace(str[i]))
            return i;
    }

    return std::string::npos;
}

std::string::size_type skipNonSpaces(const std::string& str, size_t pos)
{
    if (pos == std::string::npos)
        return pos;

    for (auto i = pos; i < str.length(); ++i)
    {
        if (std::isspace(str[i]))
            return i;
    }

    return std::string::npos;
}

std::vector<std::string> FMECommandsParser::parseStr(const std::string& str)
{
    std::string::size_type startPos = 0;
    std::vector<std::string> strParts;

    while ((startPos = skipSpaces(str, startPos)) != std::string::npos)
    {
        const auto nextPos = skipNonSpaces(str, startPos + 1);

        strParts.push_back(nextPos != std::string::npos
                           ? str.substr(startPos, nextPos - startPos)
                           : str.substr(startPos));

        startPos = nextPos;
    }

    return strParts;
}

template<typename TCmd>
void FMECommandsParser::registerCommand()
{
    FMECmdBasePtr pCmd = std::make_shared<TCmd>();
    m_commands.emplace(pCmd->getName(), pCmd);
}
