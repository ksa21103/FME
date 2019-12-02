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
    EXPECT_EQ(params_v1.size(), 0);

    const auto params_v2 = FMECommandsParserTest().test_parseStr("");
    EXPECT_EQ(params_v2.size(), 0);
}

TEST(TestTokenizeString, TestParseString_1)
{
    const auto params = FMECommandsParserTest().test_parseStr("1");
    EXPECT_EQ(params.size(), 1);
}

TEST(TestTokenizeString, TestParseString_2)
{
    const auto params = FMECommandsParserTest().test_parseStr("\tparam1   param2\t\t");
    EXPECT_EQ(params.size(), 2);
    EXPECT_EQ(params[0], "param1");
    EXPECT_EQ(params[1], "param2");
}
