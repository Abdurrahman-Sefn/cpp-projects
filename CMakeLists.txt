cmake_minimum_required(VERSION 3.20)
project(
  MyCPP_Portfolio
  VERSION 1.0.0
  DESCRIPTION "A portfolio of C++ projects"
  LANGUAGES CXX
)

# C++ Standard Configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Compiler flags for better warnings and optimizations
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Optional: Fetch external dependencies
include(FetchContent)

FetchContent_Declare(
  SefnUtils
  GIT_REPOSITORY https://github.com/Abdurrahman-Sefn/sefn-utils.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(SefnUtils)

# Add subdirectories
add_subdirectory(projects/01-employee-program)
add_subdirectory(projects/02-tic-tac-toe-game)
add_subdirectory(projects/03-hospital-system)
add_subdirectory(projects/04-library-system-v1)
add_subdirectory(projects/04-library-system-v2)
add_subdirectory(projects/05-ask-me-system)
add_subdirectory(projects/06-educational-management-system)