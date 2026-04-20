cmake_minimum_required(VERSION 4.0)
project(Tarea3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tarea3 main.cpp
        Entity.cpp
        Entity.h
        CommandCenter.cpp
        CommandCenter.h)
