//
// Created by Vladimir on 01.02.2023.
//

#pragma once

#include "types.h"

namespace pce::utilsModule {
	// TODO add check if K type has required operators
	template<typename T, typename K = uint32>
	class KeyId {
		friend T;
	public:
		using type = K;

		explicit KeyId(K id) noexcept: m_id(id) {}

		explicit operator K() const noexcept {
			return m_id;
		}

		bool operator==(const KeyId& other) const noexcept { return m_id == other.m_id; }

		bool operator!=(const KeyId& other) const noexcept { return m_id != other.m_id; }

		bool operator<(const KeyId& other) const noexcept { return m_id < other.m_id; }

		bool operator>(const KeyId& other) const noexcept { return m_id > other.m_id; }

	private:
		K m_id;
	};

	// TODO add check that K has ++ operator
	// 		and if not then NextK must have signature std::function<K(K&)>
	template<typename T, typename K = uint32/*, typename NextK = void*/>
	class UniqueIdProvider {
	public:
		using Id = KeyId<T, K>;

		explicit UniqueIdProvider() noexcept: m_id(GenerateId()) {}

		explicit UniqueIdProvider(Id id) noexcept: m_id(id) {}

		explicit UniqueIdProvider(K id) noexcept: m_id(id) {}

		UniqueIdProvider(const UniqueIdProvider& other) noexcept: m_id(other.m_id) {}

		UniqueIdProvider(UniqueIdProvider&& other) noexcept: m_id(other.m_id) {}

		UniqueIdProvider& operator=(const UniqueIdProvider& other) noexcept {
			m_id = other.m_id;
			return *this;
		};

		UniqueIdProvider& operator=(UniqueIdProvider&& other) noexcept {
			m_id = other.m_id;
			return *this;
		};

		virtual ~UniqueIdProvider() = default;

		[[nodiscard]] virtual Id GetId() const noexcept {
			return m_id;
		}

		[[nodiscard]] static Id GenerateId() noexcept {
//			if (K has ++ operator){
			return Id(m_current++);
//			} else {
//				return NextK(m_current);
//			}
		}

	private:
		inline static K m_current = K();
		Id m_id;
	};
}