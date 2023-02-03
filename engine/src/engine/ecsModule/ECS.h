//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include <type_traits>
#include <typeindex>

#include "utilsModule/KeyId.h"

namespace pce::ecs {
	class IEntity {
	public:
		virtual ~IEntity() = 0;

		virtual void Setup() {};

		virtual void Update(float deltaTime) {};

		virtual void Teardown() {};
	};

	class Entity : public IEntity, public utilsModule::UniqueIdProvider<Entity> {
	public:
		explicit Entity() = default;

		explicit Entity(Entity::Id id) : utilsModule::UniqueIdProvider<Entity>(id) {}

		Entity(const Entity& other) noexcept = default;

		Entity(Entity&& other) noexcept = default;

		~Entity() override = default;

		Entity& operator=(const Entity& other) noexcept = default;

		Entity& operator=(Entity&&) noexcept = default;

		bool operator==(const Entity& other) const noexcept { return GetId() == other.GetId(); }

		bool operator!=(const Entity& other) const noexcept { return GetId() != other.GetId(); }

		bool operator<(const Entity& other) const noexcept { return GetId() < other.GetId(); }

		bool operator>(const Entity& other) const noexcept { return GetId() > other.GetId(); }
	};

	const uint32 MAX_COMPONENTS = 32;
	typedef std::bitset<MAX_COMPONENTS> Signature;

	template<typename T>
	class Component {
	public:
		[[nodiscard]] static utilsModule::UniqueIdProvider<Component<void>>::Id GetTypeId() noexcept {
			static utilsModule::UniqueIdProvider<Component<void>>::Id id = utilsModule::UniqueIdProvider<Component<void>>::GenerateId();
			return id;
		}
	};

	/***
	 * System is an entity that manages other entities
	 * that has specific associated components
	 */
	class System {
	public:
		System() = default;

		virtual void Update(float deltaTime) = 0;

		void AddEntity(const Entity& entity);

		void RemoveEntity(const Entity& entity);

		[[nodiscard]] std::vector<Entity> GetEntities() const;

		[[nodiscard]] const Signature& GetComponentSignature() const;

		template<typename TComponent,
				typename = std::enable_if_t<std::is_base_of_v<Component<TComponent>, TComponent>>>
		void RequireComponent() {
			const auto id = Component<TComponent>::GetTypeId();
			m_componentSignature.set(id);
		}

	private:
		Signature m_componentSignature;
		std::vector<Entity> m_entities;
	};

	class IPool {
	public:
		virtual ~IPool() = 0;
	};

	// TODO add check T is base of Component
	template<typename T>
	class Pool : public IPool {
	public:
		Pool() = default;

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
				const auto index = m_size;
				m_entityIdToIndex.emplace(entityId, index);
				m_indexToEntityId.emplace(index, entityId);
				m_data.push_back(component);
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

	/***
	 * The Registry manages the creation and destruction of both entities
	 * and components and adding systems
	 */
	class Registry { // TODO inherit from SystemInstance
	public:
		Registry() = default;

		[[nodiscard]] Entity CreateEntity();

		void RemoveEntity(Entity entity);

		void Update();

		void AddEntityToSystem(const Entity& entity);

		void RemoveEntityToSystem(const Entity& entity);

		template<typename T, typename... Args,
				typename = std::enable_if_t<std::is_base_of_v<Component<T>, T>>>
		void AddComponent(const Entity& entity, Args&& ... args) {
			const auto entityId = entity.GetId();
			const auto componentTypeId = Component<T>::GetTypeId();

			auto component = T(std::forward<Args>(args)...);

			if (uint32(componentTypeId) > m_componentPools.size()) {
				m_componentPools.emplace_back();
			}
			auto pool = std::static_pointer_cast<Pool<T>>(m_componentPools.at(uint32(componentTypeId)));
			pool->Set(entityId, std::move(component));

			m_entitiesToComponentsSignatures[entityId].set(uint32(componentTypeId));
		}

		template<typename T,
				typename = std::enable_if_t<std::is_base_of_v<Component<T>, T>>>
		void RemoveComponent(const Entity& entity) {
			const auto entityId = entity.GetId();
			const auto componentTypeId = Component<T>::GetTypeId();

			auto pool = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentTypeId));
			pool->Remove(entityId);

			m_entitiesToComponentsSignatures[entityId].set(componentTypeId, false);
		};

		template<typename T,
				typename = std::enable_if_t<std::is_base_of_v<Component<T>, T>>>
		[[nodiscard]] bool HasComponent(const Entity& entity) const {
			const auto entityId = entity.GetId();
			const auto componentTypeId = Component<T>::GetTypeId();
			return m_entitiesToComponentsSignatures.at(entityId).test(componentTypeId);
		}

		template<typename T,
				typename = std::enable_if_t<std::is_base_of_v<Component<T>, T>>>
		T& GetComponent(const Entity& entity) const {
			const auto entityId = entity.GetId();
			const auto componentTypeId = Component<T>::GetTypeId();
			auto pool = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentTypeId));
			return pool->Get(entityId);
		}

		template<typename T, typename... Args,
				typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		void AddSystem(Args&& ... args) {
			m_systems.insert(std::type_index(typeid(T)), std::make_shared<T>(std::forward<Args>(args)...));
		}

		template<typename T, typename... Args,
				typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		void RemoveSystem() {
			if (!m_systems.count(std::type_index(typeid(T)))) {
				return;
			}
			m_systems.erase(std::type_index(typeid(T)));
		}

		template<typename T, typename... Args,
				typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		[[nodiscard]] bool HasSystem() {
			return m_systems.count(std::type_index(typeid(T)));
		}

		template<typename T, typename... Args,
				typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		std::weak_ptr<T> GetSystem() const {
			return std::weak_ptr<T>(m_systems.at(std::type_index(typeid(T))));
		}

	private:
		std::set<Entity> m_entityToAdd, m_entityToRemove;
		std::vector<std::shared_ptr<IPool>> m_componentPools;
		std::map<Entity::Id, Signature> m_entitiesToComponentsSignatures;
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
	};
}
