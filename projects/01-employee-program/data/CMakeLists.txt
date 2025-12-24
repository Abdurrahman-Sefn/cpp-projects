cmake_minimum_required(VERSION 3.10)

project(EmployeeManagementSystem VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(employee_program EmployeeSystem.cpp)

# Link external utilities (Assumes Sefn::Utils is available in the environment)
# If Sefn::Utils is a local library, ensure it is added via add_subdirectory or found via find_package
target_link_libraries(employee_program PRIVATE Sefn::Utils)

# Set output directory
set_target_properties(employee_program PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)