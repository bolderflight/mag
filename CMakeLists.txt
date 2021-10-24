cmake_minimum_required(VERSION 3.13)
# Project information
project(Mag
	VERSION 1.0.0
	DESCRIPTION "Mag interface"
	LANGUAGES CXX
)
# Add the library target
add_library(mag INTERFACE)
# Setup include directories 
target_include_directories(mag INTERFACE include/)
# Compile options
add_compile_options(
	$<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
)

# Example if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(example examples/example.cc)
	# Add the includes
	target_include_directories(example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the example target
	target_link_libraries(example
		PRIVATE 
			mag
	)
endif()


