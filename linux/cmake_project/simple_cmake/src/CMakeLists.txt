# Put all binary files into /bin and libraries into /lib
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add libraries
set(LIBHELLO_SRC 
    hello.cpp
)
add_library(hello STATIC ${LIBHELLO_SRC})

# Add executables
add_executable(hello_demo main.cpp)
target_link_libraries(hello_demo hello)
