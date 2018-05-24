cmake_minimum_required(VERSION 3.10)

project(Sudoku)
set(CMAKE_BUILD_TYPE "DEBUG")

# Create a sources variable with a link to all cpp files to compile
file(GLOB SOURCES
    "*.h"
    "*.cpp"
)

set_embt_target("VCL")
add_executable(Sudoku WIN32 ${SOURCES})

# cmake -DCMAKE_C_COMPILER=bcc64.exe -DCMAKE_CXX_COMPILER=bcc64.exe -G Ninja
