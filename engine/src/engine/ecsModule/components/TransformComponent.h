//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include <glm/vec2.hpp>

namespace pce::ecs::components {
	struct TransformComponent : ecs::Component<TransformComponent> {
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

		TransformComponent(glm::vec2 position, glm::vec2 scale, float rotation)
				: position(position), scale(scale), rotation(rotation) {};
		// TODO should I add here anchor and pivot points data?
	};
}
