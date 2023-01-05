include(utilities/cmake/CPM.cmake)

# --- Dependencies ---

set(SDL2_VERSION    2.26.2)
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
        URL  https://github.com/nlohmann/json/releases/download/v${NLOHMANN_VERSION}/include.zip
)

if(nlohmann_json_ADDED)
    add_library(nlohmann_json INTERFACE)
    target_include_directories(nlohmann_json SYSTEM INTERFACE ${nlohmann_json_SOURCE_DIR}/single_include)
endif()

CPMAddPackage(
        NAME SDL2
        VERSION ${SDL2_VERSION}
        URL https://libsdl.org/release/SDL2-${SDL2_VERSION}.zip
)

# --- Target ---

add_library(${ENGINE_LIB} STATIC src/tmp.cpp)

target_link_libraries(${ENGINE_LIB} fmt::fmt nlohmann_json SDL2main SDL2-static)