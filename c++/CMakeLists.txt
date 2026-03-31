cmake_minimum_required(VERSION 3.10)
project(whenwords)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_library(whenwords src/whenwords.cpp)

add_executable(test_whenwords src/test_whenwords.cpp)
target_link_libraries(test_whenwords whenwords)
