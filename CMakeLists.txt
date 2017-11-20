cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

project(instant)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()


set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

#set(ENABLE_SANITIZERS ON)
if (ENABLE_SANITIZERS)
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
endif()


set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)


SET(antlr_sources "${PROJECT_SOURCE_DIR}/thirdparty/antlr4/runtime/Cpp/runtime/src/")
message(${antlr_sources})
include_directories(
        ${antlr_sources}/
        ${antlr_sources}/misc
        ${antlr_sources}atn
        ${antlr_sources}/dfa
        ${antlr_sources}/tree
        ${antlr_sources}/support)



add_subdirectory(Tests)
add_subdirectory(src)





