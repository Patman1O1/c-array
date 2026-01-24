#-----------------------------------------------------------------------------------------------------------------------
# Includes
#-----------------------------------------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

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
if(NOT TARGET uninstall)
    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake
            COMMENT "Uninstalling all installed files...")
endif()
