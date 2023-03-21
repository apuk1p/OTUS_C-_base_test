cmake_minimum_required(VERSION 3.5)

# add_subdirectory(src)

project(homework06)

add_executable(main 
			main.cpp
			array.cpp)

set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
