set(INSTC_LLVM_SOURCE_FILES "")


set(antlr_files LLVMCodeGen.cpp LLVMCodeGen.h
        InstantLexer.cpp InstantLexer.h InstantLexer.tokens InstantParser.cpp
        InstantParser.h StaticAnalysis.cpp StaticAnalysis.h Diagnostic.cpp Diagnostic.h common.h
        JasminCodeGen.cpp JasminCodeGen.h VariableAllocator.cpp
        VariableAllocator.h DefaultVisitor.h DefaultVisitor.cpp StackHeightOptimizer.cpp
        StackHeightOptimizer.h common.cpp JasminVisitor.cpp JasminVisitor.h
        InstantVisitor.cpp InstantVisitor.h)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files})

add_library(instant_lib ${antlr_files})
target_link_libraries(instant_lib antlr4lib)
add_dependencies(instant_lib antlr4lib)


add_executable(insc_llvm llvm.cpp)
#add_dependencies(insc_llvm antlr4lib)
target_link_libraries(insc_llvm instant_lib)
target_link_libraries(insc_llvm antlr4lib)


add_executable(insc_jvm jvm.cpp)
#add_dependencies(insc_jvm antlr4lib)
target_link_libraries(insc_jvm instant_lib)
target_link_libraries(insc_jvm antlr4lib)

