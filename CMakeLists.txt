cmake_minimum_required(VERSION 3.23)
project(picuma_course_engine)

set(CMAKE_CXX_STANDARD 17)
set(DEMO_TARGET demo)
set(ENGINE_LIB engine)

add_subdirectory("engine" engine)

if (BUILD_DEMO)
    message("BUILD_DEMO = true")
    add_subdirectory("demo")
endif()
