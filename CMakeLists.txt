cmake_minimum_required(VERSION 3.10)
project("Homework" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Library sources
set(LIB_SOURCES
    lib/Services/carRecognizer.cpp
)

# Create libraries
add_library(carRecognizer lib/carRecognizer.cpp)

# Main executable
add_executable(Homework main.cpp)

# Link libraries
target_link_libraries(
    Homework
    PRIVATE
        carRecognizer
)