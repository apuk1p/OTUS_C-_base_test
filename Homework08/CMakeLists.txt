cmake_minimum_required(VERSION 3.5)

project(counter)

# if (MSVC)
#     # warning level 4 and all warnings as errors
#     add_compile_options(/W4 /WX)
# else()
#     # lots of warnings and all warnings as errors
#     add_compile_options(-Wall -Wextra -pedantic -Werror -g)
# endif()

add_executable(${PROJECT_NAME} topk_words.cpp)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


# counter.exe "C:\CPP_courses\Homework08\testText.txt" "C:\CPP_courses\Homework08\testText2.txt" "C:\CPP_courses\Homework08\testText3.txt" "C:\CPP_courses\Homework08\testText4.txt"