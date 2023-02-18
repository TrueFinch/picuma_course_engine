//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <utility>
#include <optional>

#include <SDL2/SDL.h>

#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::components {
	struct SpriteComponent : public Component<SpriteComponent> {
		std::string id;
		glm::i32vec2 srcRectPos;
		SDL_RendererFlip flip;
		std::optional<glm::u32vec2> size;

		explicit SpriteComponent(std::string id, glm::i32vec2 srcRectPos = { 0, 0 },
								 std::optional<glm::u32vec2> size = std::nullopt,
								 SDL_RendererFlip flip = SDL_FLIP_NONE)
			: id(std::move(id)), srcRectPos(srcRectPos), flip(flip), size(size) {}
	};
}
