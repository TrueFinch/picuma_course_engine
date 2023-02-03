//
// Created by Vladimir on 31.01.2023.
//

#pragma once

#include <memory>

namespace pce::utilsModule {
	template<typename T>
	class Instance {
	public:
		Instance() = delete;

		static T& GetInstance() {
			return *m_instance;
		}

		static void Init(std::unique_ptr<T> instance) {
			m_instance = std::move(instance);
		}

		static void Cleanup() {
			m_instance.reset();
		}

	protected:
		static inline std::unique_ptr<T> m_instance;
	};
}
