//
// Created by Копиенко Сергей on 02.12.2019.
//

#include "gtest/gtest.h"

#include "../FMECommandsParser.h"

class TestParsing : public ::testing::Test
{
};

TEST(TestParsing, TestParseCmdCreateDirectory)
{
    // FMECmdCreateDirectory
    TCmdParamsContainer cmdParams;
    auto cmd = FMECommandsParser().parse("md /dir1", cmdParams);
    EXPECT_EQ(cmd->getName(), "md");
    EXPECT_EQ(cmd->getKind(), CommandKinds::eCreateDirectory);
    EXPECT_EQ(cmdParams.size(), 1);
}

TEST(TestParsing, TestParseCmdCreateFile)
{
    // FMECmdCreateFile
    TCmdParamsContainer cmdParams;
    auto cmd = FMECommandsParser().parse("mf /file.txt", cmdParams);
    EXPECT_EQ(cmd->getName(), "mf");
    EXPECT_EQ(cmd->getKind(), CommandKinds::eCreateFile);
    EXPECT_EQ(cmdParams.size(), 1);
}

TEST(TestParsing, TestParseCmdRemove)
{
    // FMECmdRemove
    TCmdParamsContainer cmdParams;
    auto cmd = FMECommandsParser().parse("rm /file.txt", cmdParams);
    EXPECT_EQ(cmd->getName(), "rm");
    EXPECT_EQ(cmd->getKind(), CommandKinds::eRemove);
    EXPECT_EQ(cmdParams.size(), 1);
}

TEST(TestParsing, TestParseCmdCopy)
{
    // FMECmdCopy
    TCmdParamsContainer cmdParams;
    auto cmd = FMECommandsParser().parse("cp /dir1/dir11 /dir1", cmdParams);
    EXPECT_EQ(cmd->getName(), "cp");
    EXPECT_EQ(cmd->getKind(), CommandKinds::eCopy);
    EXPECT_EQ(cmdParams.size(), 2);
}

TEST(TestParsing, TestParseCmdMove)
{
    // FMECmdMove
    TCmdParamsContainer cmdParams;
    auto cmd = FMECommandsParser().parse("mv /dir1/dir11 /dir1", cmdParams);
    EXPECT_EQ(cmd->getName(), "mv");
    EXPECT_EQ(cmd->getKind(), CommandKinds::eMove);
    EXPECT_EQ(cmdParams.size(), 2);
}
