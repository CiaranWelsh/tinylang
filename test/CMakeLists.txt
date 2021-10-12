add_subdirectory(googletest-master)


macro(add_test_executable TARGET)
    add_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} PRIVATE  tinylangBasic gtest gtest_main)
    add_dependencies(${TARGET} tinylangBasic gtest gtest_main)

endmacro()



add_subdirectory(Basic)