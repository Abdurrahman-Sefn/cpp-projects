# 01-employee-program
project(EmployeeProgram)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(employee_program ${SOURCES})

target_include_directories(employee_program PRIVATE src)
target_link_libraries(employee_program PRIVATE Sefn::Utils)

set_target_properties(employee_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy data files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)
