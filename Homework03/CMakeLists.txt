cmake_minimum_required(VERSION 3.5)

project(03.homework)
set(CMAKE_CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

set(SOURCE_EXE 
	guess_the_number.cpp
)

set(SOURCE_LIB 
	high_scores.cpp
	levels.cpp
	check_value.cpp
	random_value.cpp
)
add_executable(guess_the_number ${SOURCE_EXE})

add_library(logic STATIC ${SOURCE_LIB})

target_include_directories(logic PRIVATE
	${CMAKE_SOURCE_DIR}
)

target_link_libraries(guess_the_number PRIVATE logic)