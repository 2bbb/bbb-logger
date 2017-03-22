#pragma once

#include <iostream>

#include "../log_level.hpp"

namespace bbb {
	struct stream {
		std::ostream &os(log_level level) {
			switch(level) {
				case bbb::log_level::verbose:
				case bbb::log_level::info:
				case bbb::log_level::warning:
					return std::cout;
				default:
					return std::cerr;
			}
		}
	};
};
