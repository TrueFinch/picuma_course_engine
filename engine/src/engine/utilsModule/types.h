//
// Created by Vladimir on 30.01.2023.
//

#pragma once

#include <string>
#include <cstdint>

using int32 = int32_t;
using uint32 = uint32_t;

namespace pce {
	enum class eLogLevel {
		PCE_LOG, PCE_WARNING, PCE_ERROR
	};
}