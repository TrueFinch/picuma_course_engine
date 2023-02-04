//
// Created by Vladimir on 01.02.2023.
//

#include "MovementSystem.h"

#include "ecsModule/components/TransformComponent.h"
#include "ecsModule/components/RigidbodyComponent.h"

using namespace pce::ecsModule::systems;
using namespace pce::ecsModule;

MovementSystem::MovementSystem() {
	Setup();
}

void MovementSystem::Setup() {
	RequireComponent<components::TransformComponent>();
	RequireComponent<components::RigidbodyComponent>();
}

void MovementSystem::Update(float deltaTime) {
	for (const auto& entity : GetEntities()) {
		auto& transform = entity.GetComponent<components::TransformComponent>();
		auto& rigidbody = entity.GetComponent<components::RigidbodyComponent>();

		transform.position += rigidbody.velocity * deltaTime;
	}
}
