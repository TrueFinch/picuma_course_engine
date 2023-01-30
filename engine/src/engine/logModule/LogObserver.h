//
// Created by Vladimir on 31.01.2023.
//

#pragma once

#include "utilsModule/Types.h"

namespace pce::logModule {
	class LogObserver {
		friend class LogManager;

	public:
		LogObserver() {
			m_id = m_index++;
		}

		bool operator==(const LogObserver& other) const {
			return m_id == other.m_id;
		}

		virtual ~LogObserver() = 0;

		virtual void OnRegistered() = 0;

		virtual void OnUnregistered() = 0;

		virtual void OnLog(pce::eLogLevel lvl, const std::string& msg) = 0;

	private:
		static inline uint32 m_index = 0;
		uint32 m_id;
	};
}
