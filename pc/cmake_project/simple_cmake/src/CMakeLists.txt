# Put all binary files into /bin and libraries into /lib
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Include path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Add libraries
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello STATIC ${LIBHELLO_SRC})

# Add executables
add_executable(helloexe main.cpp)
target_link_libraries(helloexe ${PROJECT_BINARY_DIR}/lib/libhello.a)
