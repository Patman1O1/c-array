#-----------------------------------------------------------------------------------------------------------------------
# Settings
#-----------------------------------------------------------------------------------------------------------------------
# C Settings
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Project Settings
option(PROJECT_BUILD_TESTS "Build the library tests" OFF)
option(PROJECT_BUILD_SHARED_LIBS "Build the library as a shared library" OFF)

# Set the library type as a variable
set(LIBRARY_TYPE "STATIC" CACHE STRING "The type of library")
if(BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE "SHARED" CACHE STRING "The type of library")
endif()
string(TOLOWER "${LIBRARY_TYPE}" LIBRARY_TYPE_LOWER)
set(LIBRARY_TYPE_LOWER ${LIBRARY_TYPE_LOWER} CACHE STRING "The type of library with all lowercase characters")

# Set default build type if not specified
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
