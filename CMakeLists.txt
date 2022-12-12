cmake_minimum_required(VERSION 3.15)
project(sm64-pyramid-sc-finder
  LANGUAGES CXX
  DESCRIPTION "Bruteforces bully speed/angle combinations for triple-bully-collision displacement. Now with less precision!"
)

# Set default build type to Release.
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_executable(bruteforce
  "main.cpp"
  "Constants.hpp"
  "Surface.cpp"
  "Surface.hpp"
  "SurfaceUtils.cpp"
  "SurfaceUtils.hpp"
  "Trig.cpp"
  "Trig.hpp"
  "vmath.cpp"
  "vmath.hpp"
  "WallsFloors.cpp"
  "WallsFloors.hpp"
)
# For Tyler
target_compile_features(bruteforce PRIVATE cxx_std_20)

# Equivalent to specifying a bunch of compiler flags.
# ===================================================

# LTO
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT lto_error LANGUAGES CXX)
if(lto_supported)
  set_target_properties(bruteforce PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION true
  )
endif()


# OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(bruteforce PRIVATE OpenMP::OpenMP_CXX)
endif()

# compiler settings not integrated into cmake.
# enable or disable as needed.
include("cmake/compiler_settings.cmake")
enable_march_native(bruteforce)
disable_fp_contract(bruteforce)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

# -O3 is already handled by using release mode.