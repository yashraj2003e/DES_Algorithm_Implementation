cmake_minimum_required(VERSION 3.26)
project(cryptography)

set(CMAKE_CXX_STANDARD 17)

add_executable(cryptography DES_implementation.cpp
        DES_implementation.cpp)
