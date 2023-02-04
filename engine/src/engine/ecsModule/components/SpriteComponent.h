//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <utility>

#include <SDL2/SDL.h>

#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::components {
	struct SpriteComponent : public Component<SpriteComponent> {
		std::string path;
		uint32 width;
		uint32 height;

		SpriteComponent(std::string  path, uint32 width, uint32 height)
			: path(std::move(path)), width(width), height(height) {}
	};
}
