# 04-library-system-v1
project(LibrarySystemV1)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(library_system_v1 ${SOURCES})

target_include_directories(library_system_v1 PRIVATE src)
target_link_libraries(library_system_v1 PRIVATE Sefn::Utils)

set_target_properties(library_system_v1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)