cmake_minimum_required(VERSION 3.10)
project("Homework" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories - add specific directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Create library with all required source files
add_library(carRecognizer
    lib/Services/isp.cpp
    lib/Services/registration_plate.cpp
    lib/Services/vehicle_register.cpp
)

# Main executable
add_executable(Homework main.cpp)

# Link libraries
target_link_libraries(
    Homework
    PRIVATE
        carRecognizer
)