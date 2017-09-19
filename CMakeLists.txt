cmake_minimum_required(VERSION 3.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(pwar)

set(SFML_ROOT "${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2")
include_directories("${PROJECT_SOURCE_DIR}/src")

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")

# Set version information in a config.h file
set(pwar_VERSION_MAJOR 1)
set(pwar_VERSION_MINOR 0)

configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "pwar")
add_executable(
        ${EXECUTABLE_NAME} WIN32 main.cpp

        src/Packman.cpp
        src/Packman.h

        src/States.h
        src/Pwar.h src/Pwar.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    FIND_LIBRARY (PSAPI Psapi)

    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${PSAPI} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} -static-libgcc -static-libstdc++)
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${pwar_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${pwar_VERSION_MINOR}")
include(CPack)