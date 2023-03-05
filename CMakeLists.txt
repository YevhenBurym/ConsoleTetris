cmake_minimum_required(VERSION 3.24)
project(ConsoleTetris)

set(CMAKE_CXX_STANDARD 11)

add_executable(ConsoleTetris main.cpp
        Map.cpp
        Figure.cpp
        Game.cpp
        RandomGenerator.cpp)
