# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run
               test_tokenize_string.cpp
               test_parse_commands.cpp
               test_path_presentation.cpp
               test_scripts.cpp
               ../FMEStorage.cpp ../FMEStorage.h
               ../FMEStoragePresenter.cpp ../FMEStoragePresenter.h
               ../FMECmdBase.cpp ../FMECmdBase.h
               ../FMECommandsEngine.h ../FMECommandsEngine.cpp
               ../FMECommandsParser.h ../FMECommandsParser.cpp
               ../FMEMain.h ../FMEMain.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)