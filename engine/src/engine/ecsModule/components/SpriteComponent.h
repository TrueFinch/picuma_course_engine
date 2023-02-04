//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <utility>

#include <SDL2/SDL.h>

#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::components {
	struct SpriteComponent : public Component<SpriteComponent> {
		std::string id;
		uint32 width;
		uint32 height;

		SpriteComponent(std::string id, uint32 width, uint32 height)
			: id(std::move(id)), width(width), height(height) {}
	};
}
