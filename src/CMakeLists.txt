set(INSTC_LLVM_SOURCE_FILES "")
set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files})



#add_library(instc_lib ${INSTC_LLVM_SOURCE_FILES})


#add_executable(insc_llvm insc_llvm.cpp)
#add_executable(insc_jvm insc_jvm.cpp)

#target_link_libraries(insc_llvm instc_lib)
#target_link_libraries(insc_jvm instc_lib)


include_directories(${PROJECT_SOURCE_DIR}/antlr4-runtime/
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/misc
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/atn
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/dfa
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/tree
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/support)
set(antlr_files LLVMCodeGenVisitor.cpp LLVMCodeGenVisitor.h
        InstantLexer.cpp InstantLexer.h InstantLexer.tokens InstantParser.cpp
        InstantParser.h)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files})

add_library(instant_antlr ${antlr_files})



add_executable(llvm llvm.cpp)
target_link_libraries(llvm instant_antlr)
target_link_libraries(llvm ${PROJECT_SOURCE_DIR}/lib/libantlr4-runtime.a)

