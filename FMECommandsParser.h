/**
 * @file   FMECommandsParser.h
 * @author Kopienko S.A.
 * @brief  Declaration of command line parser
 */

#ifndef FME_FMECOMMANDSPARSER_H
#define FME_FMECOMMANDSPARSER_H

#include <vector>
#include <unordered_map>

#include "FMECmdBase.h"

////////////////////////////////////////////////////////////////////////////////
// class FMECommandsParser - FME command line parser
class FMECommandsParser
{
public:

    FMECommandsParser();

    /// Parse FME command line and return created FME command
    /// \param strCmd - source command line text
    /// \param cmdParams - filled by parsed params
    /// \return - parsed FME command
    FMECmdBasePtr parse(const std::string& strCmd, TCmdParamsContainer& cmdParams);

private:

    /// Register FME command
    template <typename TCmd>
    void registerCommand();

    /// Parse source string to vector of substrings.
    ///
    /// Separation processed by any space-chars.
    ///
    /// \param str - source string to parse
    /// \return std::vector<std::string> - vector of substrings
    static std::vector<std::string> parseStr(const std::string& str);

private:

    std::unordered_map<std::string, FMECmdBasePtr> m_commands;  //< Registered FME commands container
};

#endif //FME_FMECOMMANDSPARSER_H
