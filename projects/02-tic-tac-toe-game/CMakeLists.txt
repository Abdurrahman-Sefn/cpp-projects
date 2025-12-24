# 02-tic-tac-toe-game
project(TicTacToe)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(tic_tac_toe ${SOURCES})

target_include_directories(tic_tac_toe PRIVATE src)
target_link_libraries(tic_tac_toe PRIVATE Sefn::Utils)

set_target_properties(tic_tac_toe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)