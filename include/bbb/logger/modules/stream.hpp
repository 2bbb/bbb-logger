/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/modules/stream.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iostream>

#include <bbb/logger/log_level.hpp>

namespace bbb {
	namespace loggers {
		struct stream {
			std::ostream &os(log_level level) {
				return std::cout;
			}
		};

		struct console_stream : stream {
			std::ostream &os(log_level level) {
				switch(level) {
					case log_level::verbose:
					case log_level::info:
					case log_level::warning:
						return std::cout;
					default:
						return std::cerr;
				}
			}
		};
	};
};
