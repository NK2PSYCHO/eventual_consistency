# This line specifies the minimum version of CMake required to build the project.
cmake_minimum_required(VERSION 3.10)

# This line sets the name of the project to "eventual_consistency".
project(eventual_consistency)

# This line sets the C standard for the project to C11.
set(CMAKE_C_STANDARD 11)
# This line makes the C standard a required feature. If the compiler does not support C11, CMake will raise an error.
set(CMAKE_C_STANDARD_REQUIRED True)

# This line adds the current source directory to the list of directories to be searched for include files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# This line adds an executable target called "PrimaryLikesServer" to be built from the source file "PrimaryLikesServer.c".
add_executable(PrimaryLikesServer PrimaryLikesServer.c)

# This line adds an executable target called "ParentProcess" to be built from the source file "ParentProcess.c".
add_executable(ParentProcess ParentProcess.c)
