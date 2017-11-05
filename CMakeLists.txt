cmake_minimum_required(VERSION 3.8)
project(instant)


set(CMAKE_CXX_STANDARD 11)



set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR})
add_subdirectory(Tests)




set(INSTC_LLVM_SOURCE_FILES  Lexer.cpp  LexStream.cpp Lexer.h LexStream.h Token.h)
set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES})



add_library(instc_lib ${INSTC_LLVM_SOURCE_FILES})


add_executable(instc_llvm insc_llvm.cpp)
target_link_libraries(instc_llvm instc_lib)
