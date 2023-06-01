cmake_minimum_required(VERSION 3.5)

# add_subdirectory(src)

project(counter)

# if (MSVC)
#     # warning level 4 and all warnings as errors
#     add_compile_options(/W4 /WX)
# else()
#     # lots of warnings and all warnings as errors
#     add_compile_options(-Wall -Wextra -pedantic -Werror -g)
# endif()

add_executable(${PROJECT_NAME} topk_words.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)