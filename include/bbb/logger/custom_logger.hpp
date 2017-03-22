#pragma once

#include "./detail/type_utils.hpp"
#include "./detail/logger_utils.hpp"
#include "./detail/logger_stream.hpp"
#include "./builtin_modules/streams.hpp"

namespace bbb {
	template <typename ... configs>
	struct custom_logger : detail::multiple_inheritance<
		detail::get_stream_t<configs ...>,
		detail::get_header_t<configs ...>,
		detail::get_footer_t<configs ...>,
		detail::get_separater_t<configs ...>
	> {
		using stream_type = detail::get_stream_t<configs ...>;
		using header_type = detail::get_header_t<configs ...>;
		using footer_type = detail::get_footer_t<configs ...>;
		using separater_type = detail::get_separater_t<configs ...>;

		using logger_stream = detail::logger_stream<custom_logger>;
		
		custom_logger() {}
		
		logger_stream log(std::string tag = "", log_level level = log_level::info) {
			return logger_stream(tag, level, *this);;
		}
		inline logger_stream operator()(std::string tag = "", log_level level = log_level::info) { return log(tag, level); }
		inline logger_stream verbose(std::string tag = "") { return log(tag, log_level::verbose); }
		inline logger_stream info(std::string tag = "")    { return log(tag, log_level::info); }
		inline logger_stream warning(std::string tag = "") { return log(tag, log_level::warning); }
		inline logger_stream error(std::string tag = "")   { return log(tag, log_level::error); }
		inline logger_stream fatal(std::string tag = "")   { return log(tag, log_level::fatal); }
		
		inline void enable() { set_enable(true); }
		inline void disable() { set_enable(false); }
		inline void set_enable(bool enable) { this->enabled = enabled; }
		inline bool is_enabled() const { return enabled; }
	private:
		bool enabled{true};
		
		using stream_type::os;
		using header_type::head;
		using footer_type::foot;
		using separater_type::separate;
		
		inline std::ostream &os(log_level level) {
			return log_level_manager::is_enabled(level) ? stream_type::os(level) : ns.os(level);
		}
		null_stream ns;
		friend logger_stream;
	};
};
