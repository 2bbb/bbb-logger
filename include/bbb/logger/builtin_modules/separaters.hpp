#pragma once

#include "../modules/separater.hpp"

namespace bbb {
	struct camma_separater : separater {
		std::string separate() const { return ", "; };
	};

    struct space_separater : separater {
		std::string separate() const { return " "; };
    };
};
