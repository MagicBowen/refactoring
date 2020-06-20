project(test_sdk)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
    "/usr/local/include/")

file(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

link_directories("/usr/local/lib")

add_executable(test_sdk ${all_files})

target_link_libraries(test_sdk sdk gtest gtest_main)
