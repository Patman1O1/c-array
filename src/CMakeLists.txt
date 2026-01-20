cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})
project(${LIBRARY_TARGET}-main LANGUAGES C)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    find_package(${LIBRARY_TARGET} REQUIRED)
endif()

add_executable(${LIBRARY_TARGET}-main)

set(SOURCES main.c)
target_sources(${LIBRARY_TARGET}-main PRIVATE ${SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(${LIBRARY_TARGET}-main PRIVATE ${LIBRARY_NAMESPACE}::${LIBRARY_TARGET})

