
set(gtest_SOURCE_DIR "googletest/googletest")
include_directories(${COMMON_INCLUDES})

message("abc ${COMMON_INCLUDES}")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(${gtest_SOURCE_DIR})
enable_testing()


set(SOURCE_FILES {$SOURCE_FILES} LexerTests.cpp)

add_executable(runTests LexerTests.cpp)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests instc_lib)

add_test(NAME that-test-I-made COMMAND runUnitTests)
add_test(that-other-test-I-made runUnitTests)