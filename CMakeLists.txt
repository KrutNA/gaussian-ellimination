cmake_minimum_required(VERSION 3.10)
project(program)

set(CMAKE_CXX_STANDARD 17)

file (GLOB program_src
        "*.hpp"
        "*.cpp"
)

add_executable(program ${program_src})