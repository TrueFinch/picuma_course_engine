add_executable(${DEMO_TARGET} src/main.cpp)

set_target_properties(${DEMO_TARGET}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demo/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demo/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demo/bin"
)

target_include_directories(${DEMO_TARGET} PRIVATE src)

target_link_libraries(${DEMO_TARGET} ${ENGINE_LIB})

