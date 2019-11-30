cmake_minimum_required(VERSION 3.15)
project(FME)

set(CMAKE_CXX_STANDARD 17)

add_executable(FME
        main.cpp
        FMEStorage.cpp FMEStorage.h
        FMEStoragePresenter.cpp FMEStoragePresenter.h
        FMECmdBase.cpp FMECmdBase.h
        FMECommandsEngine.h FMECommandsEngine.cpp
        FMECommandsParser.h FMECommandsParser.cpp)