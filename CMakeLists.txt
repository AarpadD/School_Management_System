cmake_minimum_required(VERSION 3.28)
project(School_Management_System CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(School_Management_System
        data_structures.h
        test.cpp
        commands.cpp
        login_S_T.cpp)
