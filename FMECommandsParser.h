//
// Created by Копиенко Сергей on 30.11.2019.
//

#ifndef FME_FMECOMMANDSPARSER_H
#define FME_FMECOMMANDSPARSER_H

#include <vector>
#include <unordered_map>

#include "FMECmdBase.h"

////////////////////////////////////////////////////////////////////////////////
class FMECommandsParser
{
public:

    FMECommandsParser();

    FMECmdBasePtr parse(const std::string& strCmd, FMECmdParams& cmdParams);

private:

    template <typename TCmd>
    void registerCommand();

    std::vector<std::string> parseStr(const std::string& str);

private:

    std::unordered_map<std::string, FMECmdBasePtr> m_commands;
};


#endif //FME_FMECOMMANDSPARSER_H
