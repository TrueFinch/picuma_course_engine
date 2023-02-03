//
// Created by Vladimir on 31.01.2023.
//

#pragma once

#include <fmt/format.h>

#include "LogObserver.h"
#include "SpdLogger.h"
#include "engine/utilsModule/Instance.h"
#include "engine/utilsModule/types.h"

namespace pce {
	namespace logModule {
		class LogManager final {
		public:
			static std::unique_ptr<LogManager> Create();

			~LogManager() = default;

			LogManager(const LogManager&) = delete;

			LogManager(LogManager&&) = delete;

			LogManager& operator=(const LogManager&) = delete;

			LogManager& operator=(LogManager&&) = delete;

			void Log(pce::eLogLevel lvl, const std::string& msg) const;

			void RegisterObserver(LogObserver& obs);

			void UnregisterObserver(LogObserver& obs);

			void Teardown();

		protected:
			LogManager() = default;

		private:
			std::unordered_map<uint32, std::reference_wrapper<LogObserver>> m_observers;
			SpdLogger m_spdLogger;
		};

		class LogManagerInstance final : public utilsModule::Instance<LogManager> {};
	}

	inline void log(pce::eLogLevel lvl, const std::string& msg) {
		using namespace logModule;
		const auto& logger = LogManagerInstance::GetInstance();
		logger.Log(lvl, msg);
	}

	template<typename... Args>
	void log(const std::string& msg, Args&& ... args) {
		log(eLogLevel::PCE_LOG, fmt::format(msg, args...));
	}

	inline void log(const std::string& msg) {
		log(eLogLevel::PCE_LOG, msg);
	}

	template<typename... Args>
	void logWarning(const std::string& msg, Args&& ... args) {
		log(eLogLevel::PCE_WARNING, fmt::format(msg, args...));
	}

	inline void logWarning(const std::string& msg) {
		log(eLogLevel::PCE_WARNING, msg);
	}

	template<typename... Args>
	void logError(const std::string& msg, Args&& ... args) {
		log(eLogLevel::PCE_ERROR, fmt::format(msg, args...));
	}

	inline void logError(const std::string& msg) {
		log(eLogLevel::PCE_ERROR, msg);
	}
}
