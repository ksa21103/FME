//
// Created by Копиенко Сергей on 03.12.2019.
//

#include "gtest/gtest.h"

#include "../FMECommandsParser.h"

class FMECommandsParserTest : public FMECommandsParser
{
public:

    static std::vector<std::string> test_parseStr(const std::string& str)
    {
        return parseStr(str);
    }
};

class TestTokenizeString : public ::testing::Test
{
};

TEST(TestTokenizeString, TestParseString_0)
{
    const auto params_v1 = FMECommandsParserTest().test_parseStr("\t\t\t");
    ASSERT_EQ(params_v1.size(), 0);

    const auto params_v2 = FMECommandsParserTest().test_parseStr("");
    ASSERT_EQ(params_v2.size(), 0);
}

TEST(TestTokenizeString, TestParseString_1)
{
    const auto params = FMECommandsParserTest().test_parseStr("1");
    ASSERT_EQ(params.size(), 1);
}

TEST(TestTokenizeString, TestParseString_2)
{
    const auto params = FMECommandsParserTest().test_parseStr("\tparam1   param2\t\t");
    ASSERT_EQ(params.size(), 2);
    ASSERT_EQ(params[0], "param1");
    ASSERT_EQ(params[1], "param2");
}
