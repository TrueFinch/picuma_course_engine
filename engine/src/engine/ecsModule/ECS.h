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

	class Registry {
		// TODO implement
	};
}
