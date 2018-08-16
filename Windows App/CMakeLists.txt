# Important installation step
# Do not miss this or you will get strange error messages

# Open "C:\Program Files (x86)\Embarcadero\Studio\19.0\cmake"
# copy and paste "Windows-Embarcadero.cmake"
# to: "C:\Program Files\CMake\share\cmake-3.11\Modules\Platform"

cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE "DEBUG")
set(APP_NAME "Sudoku")

project(${APP_NAME})

# Create a sources variable with a link to all cpp files to compile
file(GLOB SOURCES
    "*.h"
    "*.cpp"
)

set_embt_target("VCL")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${APP_NAME} WIN32 ${SOURCES} Sudoku.res)
target_link_libraries(${APP_NAME} rtl.lib vcl.lib import32.lib cp32mt.lib)

# cd Out
# cmake .. -DCMAKE_C_COMPILER=bcc32x.exe -DCMAKE_CXX_COMPILER=bcc32x.exe -G Ninja
