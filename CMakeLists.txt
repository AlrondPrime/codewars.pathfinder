cmake_minimum_required(VERSION 3.23)
project(pathfinder_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(pathfinder_1 main.cpp Pathfinder.h Labyrinth.hpp Crawler.cpp Labyrinth.cpp)
