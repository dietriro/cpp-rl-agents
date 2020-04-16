cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

# set(CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(ParralRL)

include_directories(include)

# Find all executables
file(GLOB project_SRCS src/*.cpp)

# add_executable(ParralRL src/main.cpp)
add_executable(ParralRL ${project_SRCS})

