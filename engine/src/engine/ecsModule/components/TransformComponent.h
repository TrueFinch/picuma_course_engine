//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include <glm/vec2.hpp>

#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::components {
	struct TransformComponent : ecsModule::Component<TransformComponent> {
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

		explicit TransformComponent(glm::vec2 position, glm::vec2 scale, float rotation)
				: position(position), scale(scale), rotation(rotation) {};
		// TODO should I add here anchor and pivot points data?
	};
}
