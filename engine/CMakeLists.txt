include(utilities/cmake/CPM.cmake)

# --- Dependencies ---
set(FMT_VERSION     9.1.0)
set(NLOHMANN_VERSION 3.11.2)
# TODO add tests support
#set(CATCH2_VERSION  3.2.1)

CPMAddPackage(
    NAME fmt
    GIT_TAG ${FMT_VERSION}
    GITHUB_REPOSITORY fmtlib/fmt
)

#CPMAddPackage(
#        NAME Catch2
#        GITHUB_REPOSITORY catchorg/Catch2
#        VERSION ${CATCH2_VERSION}
#)

CPMAddPackage(
    NAME nlohmann_json
    VERSION ${NLOHMANN_VERSION}
    URL https://github.com/nlohmann/json/releases/download/v${NLOHMANN_VERSION}/include.zip
)

if(nlohmann_json_ADDED)
    add_library(nlohmann_json INTERFACE)
    target_include_directories(nlohmann_json SYSTEM INTERFACE ${nlohmann_json_SOURCE_DIR}/single_include)
endif()

# --- Target ---

add_library(${ENGINE_LIB} STATIC
    src/engine/coreModule/Game.cpp
    src/engine/coreModule/Game.h
)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_include_directories(${ENGINE_LIB}
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${ENGINE_LIB}
    PRIVATE
    fmt::fmt nlohmann_json
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

    PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

target_include_directories(${ENGINE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
