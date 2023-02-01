//
// Created by Vladimir on 01.02.2023.
//

#include <algorithm>

#include "ECS.h"

using namespace pce::ecs;
using namespace pce::utilsModule;

void System::AddEntity(std::weak_ptr<Entity> entity) {
	m_entities.emplace_back(entity);
}

void System::RemoveEntity(std::weak_ptr<Entity> entity) {
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&entity](std::weak_ptr<Entity> el) {
		return *el.lock() == *entity.lock();
	}), m_entities.end());
}

std::vector<std::weak_ptr<Entity>> System::GetEntities() const {
	return m_entities;
}

const Signature& System::GetComponentSignature() const {
	return m_componentSignature;
}
