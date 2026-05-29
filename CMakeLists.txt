cmake_minimum_required(VERSION 3.23)

project(ModernCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(classing
    classing.cc
)

add_executable(type_homework
    homework/Type.cc
)

add_executable(fast_inv_sqrt
    fast_inv_sqrt.cc
)
