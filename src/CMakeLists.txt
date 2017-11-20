set(INSTC_LLVM_SOURCE_FILES "")

#add_library(instc_lib ${INSTC_LLVM_SOURCE_FILES})


#add_executable(insc_llvm insc_llvm.cpp)
#add_executable(insc_jvm insc_jvm.cpp)

#target_link_libraries(insc_llvm instc_lib)
#target_link_libraries(insc_jvm instc_lib)



set(antlr_files LLVMCodeGenVisitor.cpp LLVMCodeGenVisitor.h
        InstantLexer.cpp InstantLexer.h InstantLexer.tokens InstantParser.cpp
        InstantParser.h StaticAnalysis.cpp StaticAnalysis.h Diagnostic.cpp Diagnostic.h common.h
        JasminCodeGenVisitor.cpp JasminCodeGenVisitor.h VariableAllocator.cpp
        VariableAllocator.h DefaultVisitor.h DefaultVisitor.cpp StackHeightOptimizer.cpp StackHeightOptimizer.h common.cpp)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files})

add_library(instant_lib ${antlr_files})



add_executable(llvm llvm.cpp)
target_link_libraries(llvm instant_lib)
#target_link_libraries(llvm ${PROJECT_SOURCE_DIR}/lib/libantlr4-runtime.a)
target_link_libraries(llvm ${PROJECT_SOURCE_DIR}/thirdparty/antlr-build/lib/libantlr4-runtime.a)


add_executable(jvm jvm.cpp)
target_link_libraries(jvm instant_lib)
#target_link_libraries(llvm ${PROJECT_SOURCE_DIR}/lib/libantlr4-runtime.a)
target_link_libraries(jvm ${PROJECT_SOURCE_DIR}/thirdparty/antlr-build/lib/libantlr4-runtime.a)
