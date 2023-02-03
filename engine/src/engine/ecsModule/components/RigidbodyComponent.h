//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <glm/vec2.hpp>

#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::components {
	struct RigidbodyComponent : ecsModule::Component<RigidbodyComponent> {
		glm::vec2 velocity;
		// TODO : think about adding weight and some gravitation system to engine?

		explicit RigidbodyComponent(glm::vec2 velocity) : velocity(velocity) {}
	};
}
