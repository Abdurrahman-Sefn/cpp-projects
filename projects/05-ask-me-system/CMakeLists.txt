# 05-ask-me-system
project(AskMeSystem)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ask_me_system ${SOURCES})

target_include_directories(ask_me_system PRIVATE src)
target_link_libraries(ask_me_system PRIVATE Sefn::Utils)

set_target_properties(ask_me_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy data files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)
