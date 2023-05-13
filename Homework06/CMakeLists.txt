cmake_minimum_required(VERSION 3.5)

# add_subdirectory(src)

project(homework06)

add_executable(main 
			main.cpp)

set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
# target_link_directories()
# target_include_directories(main PUBLIC &{CMAKE_CURRENT_SOURCE_DIR}/include/)


# if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
#         CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
#         CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#         target_compile_options(${target} PRIVATE
#             -g -Wall -Wextra -Werror -pedantic)
#     elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#         target_compile_options(${target} PRIVATE
#             /W4 /WX)
#     endif()