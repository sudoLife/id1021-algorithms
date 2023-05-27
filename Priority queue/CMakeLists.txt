cmake_minimum_required(VERSION 3.15)

project(priority LANGUAGES CXX)

add_executable(stupid_queue_test stupid_queue_test.cpp)
add_executable(tree_heap tree_heap.cpp)
add_executable(${PROJECT_NAME} main.cpp)
