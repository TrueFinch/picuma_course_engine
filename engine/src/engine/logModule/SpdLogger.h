//
// Created by Vladimir on 31.01.2023.
//

#pragma once

#include <spdlog/spdlog.h>

#include "utilsModule/types.h"
#include "logModule/LogObserver.h"

namespace pce::logModule {
	class SpdLogger final : public LogObserver {
	public:
		explicit SpdLogger();
		~SpdLogger() override;
		void OnRegistered() override;
		void OnUnregistered() override;
		void OnLog(pce::eLogLevel lvl, const std::string &msg) override;
	};
}


