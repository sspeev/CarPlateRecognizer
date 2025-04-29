cmake_minimum_required(VERSION 3.10)
project("Homework" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Include directories
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

# Set up Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Create test executable
add_executable(carRecognizer_tests
    lib/tests/tests_main.cpp
    lib/tests/isp_tests.cpp
    lib/tests/registration_plate_tests.cpp
)

target_link_libraries(carRecognizer_tests
    PRIVATE
        carRecognizer
        Catch2::Catch2WithMain
)

# Register tests
include(Catch)
catch_discover_tests(carRecognizer_tests)