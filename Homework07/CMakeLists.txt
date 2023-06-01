cmake_minimum_required(VERSION 3.14)

project(Homework)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -g)
endif()
# link_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(${PROJECT_NAME} containerChecks.cpp)

enable_testing()

add_subdirectory(gtests)

# target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
# target_link_libraries(${PROJECT_NAME} PUBLIC testprint)
