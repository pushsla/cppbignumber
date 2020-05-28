cmake_minimum_required(VERSION 3.10)

project(main VERSION 0.1 LANGUAGES CXX)

set(SOURCE_MAIN main.cpp)
set(SOURCE_ALL cppbignumber/BigInt.c++)

add_executable(main ${SOURCE_MAIN} ${SOURCE_ALL})
include_directories(cppbignumber PRIVATE cppbignumber)

install(TARGETS main)