//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <unordered_map>

#include "utilsModule/KeyId.h"

namespace pce::ecs {
	class Entity : public utilsModule::UniqueIdProvider<Entity> {
	public:
		explicit Entity() = default;

		explicit Entity(Entity::Id id) : utilsModule::UniqueIdProvider<Entity>(id) {}

		Entity(const Entity& other) noexcept = default;

		Entity(Entity&& other) noexcept = default;

		~Entity() override = default;

		Entity& operator=(const Entity& other) noexcept = default;

		Entity& operator=(Entity&&) noexcept = default;

		bool operator==(const Entity& other) noexcept { return GetId() == other.GetId(); }

		bool operator!=(const Entity& other) noexcept { return GetId() != other.GetId(); }

		bool operator<(const Entity& other) noexcept { return GetId() < other.GetId(); }

		bool operator>(const Entity& other) noexcept { return GetId() > other.GetId(); }

		virtual void Setup() {};

		virtual void Update(float deltaTime) {};

		virtual void Teardown() {};
	};

	const uint32 MAX_COMPONENTS = 32;
	typedef std::bitset<MAX_COMPONENTS> Signature;

	//TODO make class abstract
	class IComponent : public utilsModule::UniqueIdProvider<IComponent> {};

	template<typename T>
	class Component : public utilsModule::UniqueIdProvider<Component<T>> {
	public:
		using TypeId = utilsModule::UniqueIdProvider<IComponent>::Id;
		using ObjId = typename utilsModule::UniqueIdProvider<Component<T>>::Id;

		[[nodiscard]] TypeId GetTypeId() const noexcept {
			return utilsModule::UniqueIdProvider<IComponent>::GetId();
		}

		[[nodiscard]] ObjId GetId() const noexcept {
			return utilsModule::UniqueIdProvider<IComponent>::GetId();
		}
	};

	/***
	 * System is an entity that manages other entities
	 * that has specific associated components
	 */
	class System : public Entity {
	public:
		System() = default;

		~System() override = default;

		void AddEntity(std::weak_ptr<Entity> entity);

		void RemoveEntity(std::weak_ptr<Entity> entity);

		[[nodiscard]] std::vector<std::weak_ptr<Entity>> GetEntities() const;

		[[nodiscard]] const Signature& GetComponentSignature() const;

		template<typename T>
		void RequireComponent() {
			const auto id = Component<T>::GetTypeId();
			m_componentSignature.set(id);
		}

	private:
		Signature m_componentSignature;

		std::vector<std::weak_ptr<Entity>> m_entities;
	};

	class IPool {
	public:
		virtual ~IPool() = 0;
	};

	// TODO add check T is base of Component
	template<typename T>
	class Pool : public IPool {
	public:
		Pool(uint32 capacity) {
			m_data.resize(capacity);
		};

		Pool(const Pool&) = delete;

		Pool(Pool&&) = delete;

		Pool& operator=(const Pool&) = delete;

		Pool& operator=(Pool&&) = delete;

		~Pool() override = default;

		bool Empty() const {
			return m_data.empty();
		}

		uint32 Size() const {
			return m_size;
		}

		void Clear() {
			m_data.clear();
			m_entityIdToIndex.clear();
			m_indexToEntityId.clear();
			m_size = 0;
		}

		void Set(Entity::Id entityId, T component) {
			if (m_entityIdToIndex.count(entityId)) {
				const auto index = m_entityIdToIndex[entityId];
				m_data[index] = component;
			} else {
				if (m_size >= m_data.capacity()) {
					m_data.resize(m_size * 2);
				}
				const auto index = m_size;
				m_entityIdToIndex.emplace(entityId, index);
				m_indexToEntityId.emplace(index, entityId);
				m_data[index] = component;
				++m_size;
			}
		}

		void Remove(Entity::Id entityId) {
			if (!m_entityIdToIndex.count(entityId)) {
				return;
			}
			const auto indexOfRemoved = m_entityIdToIndex[entityId];
			const auto indexOfLast = m_size - 1;
			m_data[indexOfRemoved] = m_data[indexOfLast];

			const auto entityIdOfLastElement = m_indexToEntityId[indexOfLast];
			m_entityIdToIndex[entityIdOfLastElement] = indexOfRemoved;
			m_indexToEntityId[indexOfRemoved] = entityIdOfLastElement;

			m_entityIdToIndex.erase(entityId);
			m_indexToEntityId.erase(indexOfLast);

			--m_size;
		}

		T& Get(Entity::Id entityId) const {
			return m_data.at(m_entityIdToIndex.at(entityId));
		}

	private:
		uint32 m_size = 0;
		std::vector<T> m_data;
		std::unordered_map<Entity::Id, uint32> m_entityIdToIndex;
		std::unordered_map<uint32, Entity::Id> m_indexToEntityId;
	};
	class Registry {
		// TODO implement
	};
}
