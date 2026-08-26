cmake_minimum_required(VERSION 3.23)

project(ModernCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(type_homework
    homework/02-Basics.cc
)

add_executable(container_homework
    homework/03-container.cc
)

add_executable(ranges_homework
    homework/04-ranges.cc
)