#pragma once

#include "./custom_logger.hpp"
#include "./builtin_modules.hpp"

namespace bbb {
	using logger = custom_logger<time_header>;
	using file_logger = custom_logger<file_stream>;
	using string_logger = custom_logger<string_stream>;
	using trasher = custom_logger<null_stream>;
	
	static logger log;
	static file_logger flog;
	static string_logger slog;
};
