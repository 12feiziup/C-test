cmake_minimum_required(VERSION 3.16)

project(cpp-training VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wnon-virtual-dtor -Woverloaded-virtual -Wno-deprecated-declarations)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
