# 04-library-system-v2
project(LibrarySystemV2)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(library_system_v2 ${SOURCES})

target_include_directories(library_system_v2 PRIVATE src)
target_link_libraries(library_system_v2 PRIVATE Sefn::Utils)

set_target_properties(library_system_v2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy data files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)
