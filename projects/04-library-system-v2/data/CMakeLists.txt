add_executable(library_system_v2
  main.cpp
  Book.cpp
  BooksManager.cpp
  BorrowOperation.cpp
  BorrowsManager.cpp
  Helper.cpp
  LibrarySystem.cpp
  User.cpp
  UsersManager.cpp
)


# Link external utilities
target_link_libraries(library_system_v2 PRIVATE Sefn::Utils)

# Set output directory
set_target_properties(library_system_v2 PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
