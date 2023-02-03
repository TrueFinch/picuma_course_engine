//
// Created by Vladimir on 01.02.2023.
//

#pragma once


#include "engine/ecsModule/ECS.h"

namespace pce::ecs::systems {
	class MovementSystem final: public System {
	public:
		explicit MovementSystem();
		void Update(float deltaTime) override;
	};
}
