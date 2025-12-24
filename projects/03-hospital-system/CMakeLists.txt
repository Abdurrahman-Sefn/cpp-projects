# 03-hospital-system
project(HospitalSystem)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(hospital_system ${SOURCES})

target_include_directories(hospital_system PRIVATE src)
target_link_libraries(hospital_system PRIVATE Sefn::Utils)

set_target_properties(hospital_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy data files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)
