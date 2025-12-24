# 06-educational-management-system
project(EducationalManagementSystem)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(educational_management_system ${SOURCES})

target_include_directories(educational_management_system PRIVATE src)
target_link_libraries(educational_management_system PRIVATE Sefn::Utils)

set_target_properties(educational_management_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy data files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)