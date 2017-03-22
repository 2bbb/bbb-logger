#pragma once

#include <string>

#include "../log_level.hpp"

namespace bbb {
	struct header {
		std::string head(std::string tag, log_level level) const {
			return "[ " + to_string(level) + " ] " + ((tag == "") ? "" : (tag + ": "));
		};
	protected:
		inline static std::string to_string(log_level level) { return bbb::to_string(level); }
	};
};