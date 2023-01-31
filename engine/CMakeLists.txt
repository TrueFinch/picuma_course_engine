add_library(${ENGINE_LIB} STATIC)

set(ENGINE_HEADERS
	src/engine/coreModule/Game.h
	src/engine/utilsModule/types.h
	src/engine/utilsModule/KeyId.h
	src/engine/logModule/LogObserver.h
	src/engine/logModule/SpdLogger.h
	src/engine/logModule/LogManager.h
	src/engine/utilsModule/SystemInstance.h
)

set(ENGINE_SOURCES
	src/engine/coreModule/Game.cpp
	src/engine/logModule/LogManager.cpp
	src/engine/logModule/SpdLogger.cpp
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
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_include_directories(${ENGINE_LIB}
	PUBLIC ${PNG_INCLUDE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
)

target_link_libraries(${ENGINE_LIB}
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

	PRIVATE
	$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>

	PRIVATE PNG::PNG
	PRIVATE glm::glm

	PRIVATE spdlog::spdlog_header_only
	PRIVATE fmt::fmt-header-only
)
