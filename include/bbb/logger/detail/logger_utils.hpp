#pragma once

#include "./type_utils.hpp"
#include "../modules.hpp"

namespace bbb {
	namespace detail {
		template <typename ... configs>
		using get_streams_t = search_inherited_types_t<stream, console_stream, configs ...>;
		template <typename ... configs>
		using get_header_t = search_inherited_type_t<header, header, configs ...>;
		template <typename ... configs>
		using get_footer_t = search_inherited_type_t<footer, footer, configs ...>;
		template <typename ... configs>
		using get_separater_t = search_inherited_type_t<separater, separater, configs ...>;

		template <typename ... configs>
		using logger_basis = detail::multiple_inheritance<
			detail::get_streams_t<configs ...>,
			detail::get_header_t<configs ...>,
			detail::get_footer_t<configs ...>,
			detail::get_separater_t<configs ...>
		>;

		template <typename holder>
		struct print_adaptor;

		template <typename type, typename ... types>
		struct print_adaptor<type_holder<type, types ...>> {
			template <typename printer, typename value_type>
			static void print(printer &p, const value_type &v, log_level level) {
				p.type::os(level) << v;
				print_adaptor<type_holder<types ...>>::print(p, v, level);
			}

			template <typename printer>
			static void print(printer &p, std::ostream& (*f)(std::ostream&), log_level level) {
				f(p.type::os(level));
				print_adaptor<type_holder<types ...>>::print(p, f, level);
			}
		};

		template <>
		struct print_adaptor<type_holder<>> {
			template <typename printer, typename value_type>
			static void print(printer &p, const value_type &v, log_level level) {}

			template <typename printer>
			static void print(printer &p, std::ostream& (*f)(std::ostream&), log_level level) {}
		};
	};
};