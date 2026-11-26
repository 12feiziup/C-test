set(INCLUDE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE "*.cpp")
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(training ${SOURCE})

target_include_directories(training PUBLIC ${INCLUDE})

# 功能代码零告警：MSVC 用 /WX，gcc/clang 用 -Werror。
target_compile_options(training PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror>)
