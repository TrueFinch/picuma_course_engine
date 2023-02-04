add_library(${ENGINE_LIB} STATIC)

set(ENGINE_HEADERS
	src/engine/coreModule/Game.h
	src/engine/utilsModule/types.h
	src/engine/utilsModule/KeyId.h
	src/engine/logModule/LogObserver.h
	src/engine/logModule/SpdLogger.h
	src/engine/logModule/LogManager.h
	src/engine/utilsModule/Instance.h
	src/engine/ecsModule/ECS.h
	src/engine/ecsModule/components/TransformComponent.h
	src/engine/ecsModule/components/RigidbodyComponent.h
	src/engine/ecsModule/components/SpriteComponent.h
	src/engine/ecsModule/systems/MovementSystem.h
	src/engine/ecsModule/systems/RenderSystem.h
	src/engine/resourceModule/ResourceManager.h
)

set(ENGINE_SOURCES
	src/engine/coreModule/Game.cpp
	src/engine/logModule/LogManager.cpp
	src/engine/logModule/SpdLogger.cpp
	src/engine/ecsModule/ECS.cpp
	src/engine/ecsModule/systems/MovementSystem.cpp
	src/engine/ecsModule/systems/RenderSystem.cpp
	src/engine/resourceModule/ResourceManager.cpp
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
	PUBLIC ${fmt_INCLUDE_DIR}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
)

target_link_libraries(${ENGINE_LIB}
	PUBLIC
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

	PUBLIC
	$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>

	PUBLIC PNG::PNG
	PUBLIC glm::glm

	PUBLIC spdlog::spdlog_header_only
	PUBLIC fmt::fmt-header-only
)
