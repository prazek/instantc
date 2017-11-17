
set(gtest_SOURCE_DIR "googletest/googletest")
include_directories(${COMMON_INCLUDES})


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(${gtest_SOURCE_DIR})
enable_testing()

#set(TEST_FILES LexerTests.cpp ParserTests.cpp LLVMCGTests.cpp JasminCGTests.cpp)
#set(SOURCE_FILES {$SOURCE_FILES} ${TEST_FILES})

#add_executable(runTests ${TEST_FILES})

#target_link_libraries(runTests gtest gtest_main)
#target_link_libraries(runTests instc_lib)

#add_test(NAME that-test-I-made COMMAND runUnitTests)
#add_test(that-other-test-I-made runUnitTests)