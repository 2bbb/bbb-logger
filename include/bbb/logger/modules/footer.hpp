#pragma once

#include <string>

#include "../log_level.hpp"

namespace bbb {
	struct footer {
		std::string foot(std::string tag, log_level level) const {
			return "";
		};
	protected:
		inline static std::string to_string(log_level level) { return bbb::to_string(level); }
	};
};