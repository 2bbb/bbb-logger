#pragma once

#include <string>
#include <iomanip>
#include <utility>

#include "../log_level.hpp"
#include "../modules/header.hpp"
#include "../detail/time_utils.hpp"

namespace bbb {
    struct time_header : header {
        std::string head(std::string tag, log_level level) const {
            return "[" + to_string(level) + "] (at " + time_utils::get_current_date_string() + ") " + ((tag == "") ? "" : (tag + ": "));
        }
    };

    struct elapsed_time_header : header {
        std::string head(std::string tag, log_level level) const {
            return "[" + to_string(level) + "] (elapsed " + std::to_string(time_utils::get_elapsed_time()) + "] " + ((tag == "") ? "" : (tag + ": "));
        }
    };
};