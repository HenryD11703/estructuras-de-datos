cmake_minimum_required(VERSION 3.10)

# set the project name
project(server)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header files
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})