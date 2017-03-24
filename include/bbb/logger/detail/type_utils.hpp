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
			static constexpr std::size_t size = sizeof...(types);
            template <std::size_t index>
            using at = type_at_t<index, types ...>;
        };

		template <typename holder>
		struct is_holder : std::false_type  {};

		template <typename ... holded>
		struct is_holder<type_holder<holded ...>> : std::true_type {};

		template <typename t, typename holder>
		struct prepend_holder;
		template <typename t, typename holder>
		using prepend_holder_t = typename prepend_holder<t, holder>::type;
		
		template <typename t, typename ... types>
		struct prepend_holder<t, type_holder<types ...>> {
			using type = type_holder<t, types ...>;
		};
		
		template <typename lhs, typename rhs>
		struct concat_holder;
		template <typename lhs, typename rhs>
		using concat_holder_t = typename concat_holder<lhs, rhs>::type;
		template <typename ... lhs, typename ... rhs>
		struct concat_holder<type_holder<lhs ...>, type_holder<rhs ...>> {
			using type = type_holder<lhs ..., rhs ...>;
		};

		template <typename ... holders>
		struct flatten_holders;
		template <typename ... holders>
		using flatten_holders_t = typename flatten_holders<holders ...>::type;

		template <typename holder, typename ... holders>
		struct flatten_holders<holder, holders ...> {
			using first = typename std::conditional<
				is_holder<holder>::value,
				flatten_holders_t<holder>,
				type_holder<holder>
			>::type;
			using type = concat_holder_t<first, flatten_holders_t<holders ...>>;
		};

		template <typename ... holded>
		struct flatten_holders<type_holder<holded ...>> {
			using type = flatten_holders_t<holded ...>;
		};

		template <typename non_holded>
		struct flatten_holders<non_holded> {
			using type = type_holder<non_holded>;
		};

		template <>
		struct flatten_holders<> {
			using type = type_holder<>;
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
		struct make_unique_holder;
		template <typename holder>
		using make_unique_holder_t = typename make_unique_holder<holder>::type;

		template <typename ... types>
		struct make_unique_holder<type_holder<types ...>> {
			using type = make_unique_t<types ...>;
		};

		template <typename holder>
		struct multiple_inheritance_impl;
		
		template <typename ... base_types>
		struct multiple_inheritance_impl<type_holder<base_types ...>> : public base_types ... {
            using types = type_holder<base_types ...>;
            template <std::size_t index>
            using type_at = type_at_t<index, base_types ...>;
        };
		
		template <typename ... types>
		using multiple_inheritance = multiple_inheritance_impl<make_unique_holder_t<flatten_holders_t<types ...>>>;
		
		template <typename base_type, typename default_type, typename ... configs>
		struct search_inherited_type;
		template <typename base_type, typename default_type, typename ... configs>
		using search_inherited_type_t = typename search_inherited_type<base_type, default_type, configs ...>::type;
		
		template <typename base_type, typename default_type, typename config, typename ... configs>
		struct search_inherited_type<base_type, default_type, config, configs ...> {
			using type = typename std::conditional<
				std::is_base_of<base_type, config>::value,
				config,
				search_inherited_type_t<base_type, default_type, configs ...>
			>::type;
		};
		template <typename base_type, typename default_type>
		struct search_inherited_type<base_type, default_type> {
			using type = base_type;
		};

		template <typename base_type, typename default_type, typename ... configs>
		struct search_inherited_types_impl;
		template <typename base_type, typename default_type, typename ... configs>
		using search_inherited_types_impl_t = typename search_inherited_types_impl<base_type, default_type, configs ...>::type;
		
		template <typename base_type, typename default_type, typename config, typename ... configs>
		struct search_inherited_types_impl<base_type, default_type, config, configs ...> {
			using others = search_inherited_types_impl_t<base_type, default_type, configs ...>;
			using type = typename std::conditional<
				std::is_base_of<base_type, config>::value,
				prepend_holder_t<config, others>,
				others
			>::type;
		};

		template <typename base_type, typename default_type>
		struct search_inherited_types_impl<base_type, default_type> {
			using type = type_holder<>;
		};

		template <typename base_type, typename default_type, typename ... configs>
		struct search_inherited_types {
			using inherited = search_inherited_types_impl_t<base_type, default_type, configs ...>;
			using type = typename std::conditional<
				inherited::size == 0,
				type_holder<default_type>,
				inherited
			>::type;
		};

		template <typename base_type, typename default_type, typename ... configs>
		using search_inherited_types_t = typename search_inherited_types<base_type, default_type, configs ...>::type;
	};
};
