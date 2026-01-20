#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28.0)
project(array
        VERSION 0.1.0
        DESCRIPTION "An implementation of an array data structure written in C."
        LANGUAGES C)

cmake_file_api(
        QUERY
        API_VERSION 1
        CODEMODEL 2.3
)

string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)

#-----------------------------------------------------------------------------------------------------------------------
# Includes
#-----------------------------------------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

#-----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#-----------------------------------------------------------------------------------------------------------------------
# C Settings
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build the library tests" OFF)
option(BUILD_SHARED_LIBS "Build the library as a shared library" OFF)

# Set the library type as a variable
set(LIBRARY_TYPE "STATIC")
if(BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE "SHARED")
endif()
string(TOLOWER "${LIBRARY_TYPE}" LIBRARY_TYPE_LOWER)

# Set default build type if not specified
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Set namespace to the library name if not specified
if(NOT DEFINED PROJECT_NAMESPACE)
    set(PROJECT_NAMESPACE ${PROJECT_NAME} CACHE STRING "PROJECT_NAMESPACE")
endif()

#-----------------------------------------------------------------------------------------------------------------------
# Targets
#-----------------------------------------------------------------------------------------------------------------------
# Define the library as a target
add_library(${PROJECT_NAME} ${LIBRARY_TYPE})

# Set the library properties
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION}
)

# Set the library header files
set(PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}.h"
                    "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/export.h"
)

# Include library directories
target_include_directories(${PROJECT_NAME}
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# Add the header files to the library target
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_HEADERS})

# Set the ARRAY_STATIC_DEFINE C macro to true or false depending on the boolean value of BUILD_SHARED_LIBS
target_compile_definitions(${PROJECT_NAME} PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${PROJECT_NAME_UPPER}_STATIC_DEFINE>")

# Group sources for the IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${PROJECT_HEADERS})

# Add the source subdirectory
add_subdirectory(src)

# Add the test subdirectory if the user specified they wanted to build the tests
if(BUILD_TESTS)
    add_subdirectory(test)
endif()

#-----------------------------------------------------------------------------------------------------------------------
# Installation
#-----------------------------------------------------------------------------------------------------------------------
configure_package_config_file("cmake/${PROJECT_NAME}-config.cmake.in" "${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

write_basic_package_version_file("${PROJECT_NAME}-config-version.cmake" COMPATIBILITY SameMajorVersion)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}_export
        RUNTIME COMPONENT ${PROJECT_NAME}
        LIBRARY COMPONENT ${PROJECT_NAME} NAMELINK_COMPONENT ${PROJECT_NAME}-dev
        ARCHIVE COMPONENT ${PROJECT_NAME}-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(DIRECTORY "include/"
        TYPE INCLUDE
        COMPONENT ${PROJECT_NAME}-dev)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/export_${LIBRARY_TYPE_LOWER}.h"
        COMPONENT ${PROJECT_NAME}-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install(EXPORT ${PROJECT_NAME}_export
        COMPONENT ${PROJECT_NAME}-dev
        FILE "${PROJECT_NAME}-${LIBRARY_TYPE_LOWER}-targets.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        NAMESPACE ${PROJECT_NAMESPACE}::)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        COMPONENT ${PROJECT_NAME}-dev
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

#-----------------------------------------------------------------------------------------------------------------------
# Uninstallation
#-----------------------------------------------------------------------------------------------------------------------
