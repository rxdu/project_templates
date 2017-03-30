# Include path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Dependency libraries
#find_package(OpenCV REQUIRED)

# Add libraries
#set(LIB_SRC
#    code.cpp
#)
#add_library(libname STATIC ${LIB_SRC})
#add_definitions(-DMYDEF)
#target_link_libraries(libname ${LCM_LIBRARIES})

# Add executables
#add_executable(quad_motion_client motion_server/motion_client.cpp)
#target_link_libraries(quad_motion_client ${LCM_LIBRARIES})

add_executable(test_py python_test.cpp)
#target_link_libraries(test_py)
