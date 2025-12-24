add_executable(ask_me_system
  main.cpp
  AskMe.cpp
  Helper.cpp
  Question.cpp
  QuestionsManager.cpp
  User.cpp
  UsersManager.cpp
)


# Link external utilities
target_link_libraries(ask_me_system PRIVATE Sefn::Utils)
# Set output directory
set_target_properties(ask_me_system PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
