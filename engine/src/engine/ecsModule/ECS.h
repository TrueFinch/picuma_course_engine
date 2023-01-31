//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include <vector>
#include <memory>

#include "utilsModule/KeyId.h"

namespace pce::ecs {
	class Entity : utilsModule::UniqueIdProvider<Entity> {
		virtual void Setup() {};
		virtual void Update(float deltaTime) {};
		virtual void Teardown() {};
	};

	class Component {
		// TODO implement
	};

	class System : Entity {
		// TODO implement
	};

	class Registry {
		// TODO implement
	};
}
