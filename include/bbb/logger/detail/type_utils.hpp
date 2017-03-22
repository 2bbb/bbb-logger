#pragma once

#include <type_traits>

namespace bbb {
    namespace detail {
        template <std::size_t index, typename ... types>
        struct type_at;
        template <std::size_t index, typename ... types>
        using type_at_t = typename type_at<index, types ...>::type;

        template <std::size_t index, typename t, typename ... types>
        struct type_at<index, t, types ...> {
            using type = typename std::conditional<
                index == 0,
                t,
                type_at_t<index - 1, types ...>
            >::type;
        };

		template <typename ... types>
		struct type_holder {
            template <std::size_t index>
            using at = type_at_t<index, types ...>;
        };

		template <typename t, typename holder>
		struct prepend_holder;
		template <typename t, typename holder>
		using prepend_holder_t = typename prepend_holder<t, holder>::type;
		
		template <typename t, typename ... types>
		struct prepend_holder<t, type_holder<types ...>> {
			using type = type_holder<t, types ...>;
		};
		
		template <typename type, typename ... types>
		struct is_in;

		template <typename needle, typename type, typename ... types>
		struct is_in<needle, type, types ...> {
			static constexpr bool value = std::is_same<needle, type>::value || is_in<needle, types ...>::value;
		};
		
		template <typename needle>
		struct is_in<needle> {
			static constexpr bool value = false;
		};
		
		template <typename ... types>
		struct make_unique;
		template <typename ... types>
		using make_unique_t = typename make_unique<types ...>::type;
		
		template <typename head, typename ... tails>
		struct make_unique<head, tails ...> {
			using type = typename std::conditional<
				is_in<head, tails ...>::value,
				make_unique_t<tails ...>,
				prepend_holder_t<head, make_unique_t<tails ...>>
			>::type;
		};
		
		template <>
		struct make_unique<> {
			using type = type_holder<>;
		};
		
		template <typename holder>
		struct multiple_inheritance_impl;
		
		template <typename ... base_types>
		struct multiple_inheritance_impl<type_holder<base_types ...>> : public base_types ... {
            using types = type_holder<base_types ...>;
            template <std::size_t index>
            using type_at = type_at_t<index, base_types ...>;
        };
		
		template <typename ...types>
		using multiple_inheritance = multiple_inheritance_impl<make_unique_t<types ...>>;
		
		template <typename base_type, typename ... configs>
		struct search_inherit_type;
		template <typename base_type, typename ... configs>
		using search_inherit_type_t = typename search_inherit_type<base_type, configs ...>::type;
		
		template <typename base_type, typename config, typename ... configs>
		struct search_inherit_type<base_type, config, configs ...> {
			using type = typename std::conditional<
				std::is_base_of<base_type, config>::value,
				config,
				search_inherit_type_t<base_type, configs ...>
			>::type;
		};
		template <typename base_type>
		struct search_inherit_type<base_type> {
			using type = base_type;
		};
	};
};
