//
// Created by Vladimir on 31.01.2023.
//

#include "LogManager.h"

using namespace pce::logModule;
using namespace pce::utilsModule;

std::unique_ptr<LogManager> LogManager::Create() {
	auto logManager = std::unique_ptr<LogManager>(new LogManager());
	// TODO create and register spdlog console
	logManager->RegisterObserver(logManager->m_spdLogger);
	return logManager;
}

void LogManager::Log(eLogLevel lvl, const std::string& msg) const {
	for (auto [_, obs]: m_observers) {
		obs.get().OnLog(lvl, msg);
	}
}

void LogManager::RegisterObserver(LogObserver& obs) {
	m_observers.insert({ obs.m_id, obs });
	obs.OnRegistered();
}

void LogManager::UnregisterObserver(LogObserver& obs) {
	if (!m_observers.count(obs.m_id)) {
		return;
	}
	obs.OnUnregistered();
	m_observers.erase(obs.m_id);
}

void LogManager::Teardown() {
	while (!m_observers.empty()) {
		auto [_, obs] = *(m_observers.begin());
		UnregisterObserver(obs.get());
	}
}
