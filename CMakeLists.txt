cmake_minimum_required(VERSION 3.23)
project(picuma_course_engine)

set(CMAKE_CXX_STANDARD 17)
set(DEMO_TARGET demo)
set(ENGINE_LIB engine)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fuse-ld=lld -Wall -Wextra -pedantic")

add_subdirectory("engine" engine)

if (BUILD_DEMO)
	message("BUILD_DEMO=TRUE")
	add_subdirectory("demo")
endif ()
