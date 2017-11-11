set(INSTC_LLVM_SOURCE_FILES  Lexer.cpp  LexStream.cpp
        Lexer.h LexStream.h Token.h AST.h Parser.cpp Parser.h AST.cpp
        LLVMCodeGen.cpp LLVMCodeGen.h JasminCodeGen.cpp JasminCodeGen.h insc_jvm.cpp)
set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES})



add_library(instc_lib ${INSTC_LLVM_SOURCE_FILES})


add_executable(instc_llvm insc_llvm.cpp)
add_executable(instc_jvm insc_jvm.cpp)

target_link_libraries(instc_llvm instc_lib)
target_link_libraries(instc_jvm instc_lib)