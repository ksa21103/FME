//
// Created by Копиенко Сергей on 03.12.2019.
//

#include "gtest/gtest.h"

#include "../FMEStorage.h"

class TestPathPresentation : public ::testing::Test
{
};

TEST(TestPathPresentation, TestPathEmpty)
{
    TEntryPath path;
    const auto presStr = std::to_string(path);
    ASSERT_EQ(presStr, "");
}

TEST(TestPathPresentation, TestPath1)
{
    TEntryPath path;
    path.push_back("dir1");
    const auto presStr = std::to_string(path);
    ASSERT_EQ(presStr, "dir1");
}

TEST(TestPathPresentation, TestPath2)
{
    TEntryPath path;
    path.push_back("dir1");
    path.push_back("dir2");
    const auto presStr = std::to_string(path);
    ASSERT_EQ(presStr, "dir1/dir2");
}

TEST(TestPathPresentation, TestPath3WithRoot)
{
    TEntryPath path;
    path.push_back("/");
    path.push_back("dir1");
    path.push_back("dir2");
    const auto presStr = std::to_string(path);
    ASSERT_EQ(presStr, "/dir1/dir2");
}
