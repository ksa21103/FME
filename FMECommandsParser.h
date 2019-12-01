//
// Created by Копиенко Сергей on 30.11.2019.
//

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

    std::vector<std::string> parseStr(const std::string& str);

private:

    std::unordered_map<std::string, FMECmdBasePtr> m_commands;  //< Registered FME commands container
};


#endif //FME_FMECOMMANDSPARSER_H
