cmake_minimum_required(VERSION 3.25)

project(AOD VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Includes)

set(SRC_LIST
Sources/Graph.cpp
Includes/Graph.hpp
)

add_executable(${PROJECT_NAME} Sources/main.cpp ${SRC_LIST})
