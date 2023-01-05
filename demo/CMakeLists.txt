add_executable(${DEMO_TARGET} src/main.cpp)

target_link_libraries(${DEMO_TARGET} ${ENGINE_LIB})

message(CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR})
target_include_directories(${DEMO_TARGET} PRIVATE src)
