cmake_minimum_required(VERSION 3.16)
project(Chess-Engine VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
	src/main.cpp
	include/main.hpp
)

add_executable(Chess-Engine ${SOURCES})
target_include_directories(Chess-Engine PRIVATE include)
