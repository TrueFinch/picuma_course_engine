//
// Created by Vladimir on 01.02.2023.
//

#include <algorithm>

#include "ECS.h"

using namespace pce::ecs;
using namespace pce::utilsModule;

IEntity::~IEntity() = default;

void System::AddEntity(const Entity& entity) {
	m_entities.emplace_back(entity);
}

void System::RemoveEntity(const Entity& entity) {
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&entity](const Entity& el) {
		return el == entity;
	}), m_entities.end());
}

std::vector<Entity> System::GetEntities() const {
	return m_entities;
}

const Signature& System::GetComponentSignature() const {
	return m_componentSignature;
}

IPool::~IPool() = default;

std::unique_ptr<Registry> Registry::Create() {
	return std::unique_ptr<Registry>(new Registry());
}

Entity Registry::CreateEntity() {
	auto entity = Entity();
	if (!m_entitiesToComponentsSignatures.count(entity.GetId())) {
		m_entitiesToComponentsSignatures[entity.GetId()] = Signature();
	}
	m_entityToAdd.insert(entity);
	return entity;
}

void Registry::RemoveEntity(Entity entity) {
	m_entityToRemove.insert(entity);
}

void Registry::Update() {
	for (auto& entity : m_entityToAdd) {
		AddEntityToSystem(entity);
	}
	m_entityToAdd.clear();



	for (auto& entity : m_entityToRemove) {
		RemoveEntityToSystem(entity);
	}
	m_entityToRemove.clear();
}

void Registry::AddEntityToSystem(const Entity& entity) {
	const auto entityId = entity.GetId();
	const auto& entityCS = m_entitiesToComponentsSignatures.at(entityId);
	for (auto& [_, system] : m_systems) {
		const auto& systemCS = system->GetComponentSignature();

		if ((entityCS & systemCS) == systemCS) {
			system->AddEntity(entity);
		}
	}
}

void Registry::RemoveEntityToSystem(const Entity& entity) {
	for (auto& [_, system] : m_systems) {
		system->RemoveEntity(entity);
	}
}
