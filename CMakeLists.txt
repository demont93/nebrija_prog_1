cmake_minimum_required(VERSION 3.17)
project(nebrija_1_2_3)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(DOWNLOAD_DOCTEST OFF CACHE BOOL "Turn on to download doctest using git")

include(ExternalProject)
find_package(Git REQUIRED)

if (DOWNLOAD_DOCTEST)
    ExternalProject_Add(
            doctest
            PREFIX ${CMAKE_BINARY_DIR}/doctest
            GIT_REPOSITORY https://github.com/onqtam/doctest
            TIMEOUT 10
            UPDATE_COMMAND ${GIT_EXECUTABLE} pull
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            LOG_DOWNLOAD ON
    )
    ExternalProject_Get_Property(doctest source_dir)
    set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
    include_directories(${DOCTEST_INCLUDE_DIR})
else ()
    find_package(doctest REQUIRED)
endif ()

add_subdirectory(src)
