cmake_minimum_required(VERSION 3.15)

set(ProjectName "CBS_Solution")

project(${ProjectName})

include_directories(include)

add_subdirectory(gtest)
add_subdirectory(src)
add_subdirectory(test)