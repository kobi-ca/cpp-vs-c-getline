cmake_minimum_required(VERSION 3.17)
project(cpp_vs_c_getline)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp-vs-c-getline main.cpp)

if (INSTRUMENT)
    target_compile_options(cpp-vs-c-getline PRIVATE -finstrument-functions)
    target_link_options(cpp-vs-c-getline PRIVATE -finstrument-functions)
endif()
