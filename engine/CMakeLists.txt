add_library(${ENGINE_LIB} STATIC)

set(ENGINE_HEADERS
    src/engine/coreModule/Game.h
    src/engine/utilsModule/types.h
)

set(ENGINE_SOURCES
    src/engine/coreModule/Game.cpp
)

target_sources(${ENGINE_LIB}
        PUBLIC ${ENGINE_HEADERS}
        PRIVATE ${ENGINE_SOURCES}
)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_include_directories(${ENGINE_LIB}
    PUBLIC ${PNG_INCLUDE_DIR}
)

target_link_libraries(${ENGINE_LIB}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

    PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>

    PRIVATE PNG::PNG
    PRIVATE glm::glm
)

target_include_directories(${ENGINE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
