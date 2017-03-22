#pragma once

#include "./type_utils.hpp"
#include "../modules.hpp"

namespace bbb {
    namespace detail {
		template <typename ... configs>
		using get_stream_t = search_inherit_type_t<stream, configs ...>;
		template <typename ... configs>
		using get_header_t = search_inherit_type_t<header, configs ...>;
		template <typename ... configs>
		using get_footer_t = search_inherit_type_t<footer, configs ...>;
		template <typename ... configs>
		using get_separater_t = search_inherit_type_t<separater, configs ...>;
    };
};