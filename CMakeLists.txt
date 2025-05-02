cmake_minimum_required(VERSION 3.10)

project("Homework" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_MODULE_PATH)
cmake_print_variables(CMAKE_PREFIX_PATH)

include(CTest)

if(BUILD_TESTING)
    message(STATUS "Make Catch2 available...")

    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)


    include(Catch)

    cmake_print_variables(Catch2_DIR)
    cmake_print_variables(catch2_SOURCE_DIR)
    cmake_print_variables(Catch2_SOURCE_DIR)
    cmake_print_variables(CMAKE_MODULE_PATH)

endif()

include_directories("lib")
add_subdirectory(lib)

if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()
