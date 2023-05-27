cmake_minimum_required(VERSION 3.15)

project(graphs LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

add_executable(naive naive.cpp)
add_executable(paths paths.cpp)
