cmake_minimum_required(VERSION 3.8)


set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

project(instant)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR})
add_subdirectory(Tests)




set(INSTC_LLVM_SOURCE_FILES  Lexer.cpp  LexStream.cpp
        Lexer.h LexStream.h Token.h AST.h Parser.cpp Parser.h AST.cpp
        LLVMCodeGen.cpp LLVMCodeGen.h JasminCodeGen.cpp JasminCodeGen.h)
set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES})



add_library(instc_lib ${INSTC_LLVM_SOURCE_FILES})


add_executable(instc_llvm insc_llvm.cpp)
target_link_libraries(instc_llvm instc_lib)
