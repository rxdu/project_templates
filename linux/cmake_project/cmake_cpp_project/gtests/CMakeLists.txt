# Include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Dependency libraries
#find_package(LIBRARY_NAME REQUIRED)

# Add executables
set(TESTCASES_SRC
    # graph_unittest.cpp
)
add_executable(gtest_all start_tests.cpp ${TESTCASES_SRC})
target_link_libraries(gtest_all gtest)

