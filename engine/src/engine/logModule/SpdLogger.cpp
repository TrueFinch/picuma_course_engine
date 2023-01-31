//
// Created by Vladimir on 31.01.2023.
//

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>

#include "SpdLogger.h"
#include "LogManager.h"

using namespace pce::logModule;

SpdLogger::SpdLogger() {
}

void SpdLogger::OnRegistered() {
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("%^%l%$: %v");

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
	fileSink->set_pattern("[%d-%m-%Y %H:%M:%S.%e] %l: %v");

	std::vector<spdlog::sink_ptr> sinks { consoleSink, fileSink };
	auto logger = std::make_shared<spdlog::logger>("console", sinks.begin(), sinks.end());
	spdlog::register_logger(logger);
}

void SpdLogger::OnUnregistered() {
	spdlog::shutdown();
}

void SpdLogger::OnLog(pce::eLogLevel lvl, const std::string& msg) {
	auto logger = spdlog::get("console");
	switch (lvl) {
		case eLogLevel::PCE_LOG:
			logger->info(msg);
			break;
		case eLogLevel::PCE_WARNING:
			logger->warn(msg);
			break;
		case eLogLevel::PCE_ERROR:
			logger->error(msg);
			break;
	}
}

SpdLogger::~SpdLogger() {
}
