cmake_minimum_required (VERSION 2.6)
project (Final_Project_PUBLIC)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory (include)

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

add_executable (Final ./src/main.c)
target_link_libraries (Final map)
target_link_libraries (Final gui)
target_link_libraries (Final a_star)
target_link_libraries (Final find_way)
target_link_libraries (Final find_way_genetic)
target_link_libraries (Final mingw32)
target_link_libraries (Final SDL2main)
target_link_libraries (Final SDL2)