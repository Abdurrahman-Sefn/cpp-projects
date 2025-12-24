add_executable(hospital_system HospitalSystem.cpp)


# Link external utilities
target_link_libraries(hospital_system PRIVATE Sefn::Utils)
# Set output directory
set_target_properties(hospital_system PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
