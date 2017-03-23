#pragma once

#include <iostream>

#include "../log_level.hpp"

namespace bbb {
    namespace detail {
		template <typename logger>
		struct logger_stream {
			logger_stream(std::string tag, log_level level, logger &body)
			: tag(tag)
			, level(level)
			, body(body)
			{
				body.os(level) << body.head(tag, level);
			}
			
			~logger_stream() {
				body.os(level) << body.foot(tag, level);
				if(without_br) return;
				body.os(level) << std::endl;
			}
			
			template <typename type>
			logger_stream &operator<<(const type &v) {
				separated() << v;
				return *this;
			}
			logger_stream &operator<<(std::ostream& (*f)(std::ostream&)) {
				f(body.os(level));
				return *this;
			}
			logger_stream &nobr() {
				without_br = true;
				return *this;
			}
		protected:
			std::string tag;
			log_level level;
			logger &body;
			bool without_br{false};
			bool initial{true};
			inline std::ostream &separated() {
				if(initial) {
					initial = false;
					return body.os(level);
				}
				return body.os(level) << body.separate();
			}
		};
    }; // namespace detail
}; // namespace bbb
