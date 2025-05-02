add_library(CarPlateRecognizer STATIC
    # Header files
    "Contracts/ucn.hpp"
    "Contracts/registration_plate.hpp"
    "Contracts/vehicle_register.hpp"

    # Source files
    "Entities/ucn.cpp"
    "Entities/registration_plate.cpp"
    "Entities/vehicle_register.cpp"
)

target_include_directories(
    CarPlateRecognizer
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_features(
    CarPlateRecognizer
    PRIVATE
    cxx_std_17
)

set_target_properties(
    CarPlateRecognizer
    PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
)
