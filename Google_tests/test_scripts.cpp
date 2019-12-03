//
// Created by Копиенко Сергей on 03.12.2019.
//

#include "gtest/gtest.h"

#include <string>
#include <fstream>

#include "../FMEMain.h"

#define SUCCESS_RESULT 0
#define ERROR_RESULT   -1

class TestScripts : public ::testing::Test
{

};

std::string readDataFromStream(std::istream& is)
{
    std::string result;

    std::string str;
    while (std::getline(is, str))
    {
        result += str;
        result += "\n";
    }

    return result;
}

void execTest(const std::string& srcScriptFileName,
              const std::string& srcPatternResultsFileName,
              int resultCode)
{
    // Read test file
    std::ifstream scriptFile(srcScriptFileName, std::ios::in);
    ASSERT_EQ(true, scriptFile.is_open());

    // Read pattern test results
    std::ifstream resultsFile(srcPatternResultsFileName, std::ios::in);
    ASSERT_EQ(true, resultsFile.is_open());

    // Execute test
    std::stringstream factResults;
    FMEStorage        disk;
    int result = FMEMain().worker(scriptFile, factResults, disk);
    ASSERT_EQ(result, resultCode);

    // Compare current results with pattern test results
    const auto allStringsFromPattern = readDataFromStream(resultsFile);
    const auto allStringsFromFactRes = factResults.str();
    ASSERT_EQ(allStringsFromPattern, allStringsFromFactRes);
}

TEST(TestScripts, test_errors)
{
    execTest(".//tests//test_errors.batch",
             ".//tests//test_errors_result.txt",
             ERROR_RESULT);
}

TEST(TestScripts, test_make_dir_create_file_copy_file)
{
    execTest(".//tests//test_make_dir_create_file_copy_file.batch",
             ".//tests//test_make_dir_create_file_copy_file_result.txt",
             SUCCESS_RESULT);
}

TEST(TestScripts, test_make_dir_root_error)
{
    execTest(".//tests//test_make_dir_root_error.batch",
             ".//tests//test_make_dir_root_error_result.txt",
             ERROR_RESULT);
}

TEST(TestScripts, test_make_file_as_dir_error)
{
    execTest(".//tests//test_make_file_as_dir_error.batch",
             ".//tests//test_make_file_as_dir_error_result.txt",
             ERROR_RESULT);
}

TEST(TestScripts, test_move_file_to_child)
{
    execTest(".//tests//test_move_file_to_child.batch",
             ".//tests//test_move_file_to_child_result.txt",
             SUCCESS_RESULT);
}

TEST(TestScripts, test_move_folder)
{
    execTest(".//tests//test_move_folder.batch",
             ".//tests//test_move_folder_result.txt",
             SUCCESS_RESULT);
}

TEST(TestScripts, test_move_folder_to_file_error)
{
    execTest(".//tests//test_move_folder_to_file_error.batch",
             ".//tests//test_move_folder_to_file_error_result.txt",
             ERROR_RESULT);
}

TEST(TestScripts, test_move_parent_folder_to_child_error)
{
    execTest(".//tests//test_move_parent_folder_to_child_error.batch",
             ".//tests//test_move_parent_folder_to_child_error_result.txt",
             ERROR_RESULT);
}
