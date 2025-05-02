# Executable target for the unit tests
add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
        CarPlateRecognizer
        Catch2::Catch2WithMain
)

target_sources(
    unit-tests
    PRIVATE
        "isp_tests.cpp"
        "registration_plate_tests.cpp"
)

# Automatically register all tests
catch_discover_tests(unit-tests)
