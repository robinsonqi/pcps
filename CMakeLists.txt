cmake_minimum_required(VERSION 3.4)
project(pcps-project)

# Define build options:
option(PCPS_BUILD_ALL "Build all pcps artefacts" OFF)
option(PCPS_BUILD_TESTS "Build pcps tests" OFF)
option(PCPS_BUILD_VIEWER "Build pcps viewer" OFF)

# Enable C++11:
set(CMAKE_CXX_STANDARD 11)

# Set compiler warnings
# (https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#compilers)
# (https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c)
# (https://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings):
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANGXX)
    add_definitions("-Wall -Wextra -Wnon-virtual-dtor -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual
        -Wpedantic -Wdouble-promotion -Wformat=2 -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wswitch-enum
        -Wunreachable-code -Winit-self -Wuninitialized -Wno-unused-result -Wctor-dtor-privacy -Wdisabled-optimization
        -Wmissing-declarations -Wredundant-decls -Wno-unused")
endif()

# Add library subdirectory:
add_subdirectory(lib)

# Add tests subdirectory:
if(PCPS_BUILD_TESTS OR PCPS_BUILD_ALL)
    add_subdirectory(tests)
endif()

# Add viewer subdirectory:
if(PCPS_BUILD_VIEWER OR PCPS_BUILD_ALL)
    add_subdirectory(viewer)
endif()
