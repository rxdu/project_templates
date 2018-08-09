## Dependency libraries
#find_package(LIBRARY_NAME REQUIRED)

## Add libraries
set(MOD_LIB_SRC
	# source files: xxx.cpp
	template.cpp
)
add_library(libmodule STATIC ${MOD_LIB_SRC})
# target_link_libraries(libmodule ${DEP_LIBS})
target_include_directories(libmodule PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>	
	PRIVATE src)

# Add executables
if(BUILD_TESTS)
add_subdirectory(tests)
endif()