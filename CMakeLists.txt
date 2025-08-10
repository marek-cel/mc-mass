cmake_minimum_required(VERSION 3.22)

set(PROJECT_VERSION_MAJOR 2)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_STRING
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
)

project(mc-mass VERSION ${PROJECT_VERSION_STRING})

################################################################################

include(FetchContent)
include(GNUInstallDirs)

################################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "MC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Software for Estimating Aircraft Mass Properties")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_GENERATOR "ZIP")

include(CPack)

################################################################################

if (BUILD_TESTING)
    include(CTest)
    include(GoogleTest)
endif()

################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D__linux__)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DNOMINMAX)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    add_definitions(-D_DEBUG)
endif()

if (BUILD_TESTING)
    add_definitions(-D_GTEST_)
    add_definitions(-D_TESTS_)
endif()

################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets OpenGL)

################################################################################

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

################################################################################

find_package(OpenSceneGraph REQUIRED
    OpenThreads
    osg
    osgDB
    osgGA
    osgParticle
    osgSim
    osgText
    osgUtil
    osgViewer
    osgWidget
)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

################################################################################

FetchContent_Declare(
    units
    GIT_REPOSITORY https://github.com/nholthaus/units.git
    GIT_TAG        v2.3.4
)
FetchContent_MakeAvailable(units)

include_directories(${units_SOURCE_DIR}/include)

################################################################################

enable_testing()

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")

    if (BUILD_TESTING)
        if (TESTS_COVERAGE)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage -fno-default-inline -fno-inline -fno-inline-small-functions -fprofile-arcs -ftest-coverage -pedantic")
        else()
            set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
            set(CMAKE_CXX_FLAGS_RELEASE "-O0")
        endif()
    else()
        set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
        set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    endif()
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-W1")
    set(CMAKE_CXX_FLAGS_RELEASE "-W1 -O2")
    if (MSVC_VERSION GREATER_EQUAL "1930")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++20")
        endif()
    endif()
endif()

include_directories(./src)

################################################################################

add_subdirectory(src)

################################################################################

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
