/**
 * @file		type_traits.hpp
 * @brief
 * @date		2018年6月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#ifdef KERBAL_ENABLE_CLANGPP_MODULES

export module kerbal.type_traits;
export namespace kerbal
{
	namespace type_traits
	{

	}
}

#endif

#include <cstddef>
#include <kerbal/compatibility/compatibility_macro.hpp>

namespace kerbal
{
	namespace type_traits
	{

		MODULE_EXPORT
		template <typename Type, Type val>
		struct integral_constant
		{
#			if __cplusplus >= 201103L
				static constexpr Type value = val;
#			else
				static const Type value = val;
#			endif

				typedef Type value_type;
				typedef integral_constant<Type, val> type;

				KERBAL_CONSTEXPR operator value_type() const
				{
					return value;
				}
		};

		MODULE_EXPORT
		struct false_type : integral_constant<bool, false>
		{
		};

		MODULE_EXPORT
		struct true_type : integral_constant<bool, true>
		{
		};

		MODULE_EXPORT
		template <bool condition, typename Tp = void>
		struct enable_if
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct enable_if<true, Tp>
		{
				typedef Tp type;
		};

#	if __cplusplus >= 201103L

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser;

		template <typename Type0, typename ... Args>
		struct type_chooser<0, Type0, Args...>
		{
				typedef Type0 type;
		};

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser
		{
				static_assert(N <= sizeof...(Args), "N is larger than the number of template type arguments");
				typedef typename type_chooser<N - 1, Args...>::type type;
		};

#	endif

		MODULE_EXPORT
		template <bool condition, typename TrueType, typename FalseType>
		struct conditional
		{
				typedef TrueType type;
		};

		MODULE_EXPORT
		template <typename TrueType, typename FalseType>
		struct conditional<false, TrueType, FalseType>
		{
				typedef FalseType type;
		};

		MODULE_EXPORT
		template <bool condition>
		struct conditional_boolean : kerbal::type_traits::conditional<condition,
											kerbal::type_traits::true_type,
											kerbal::type_traits::false_type>::type
		{
		};

#	if __cplusplus < 201103L

		template <typename Tp0 = kerbal::type_traits::true_type,
					typename Tp1 = kerbal::type_traits::true_type,
					typename Tp2 = kerbal::type_traits::true_type,
					typename Tp3 = kerbal::type_traits::true_type,
					typename Tp4 = kerbal::type_traits::true_type,
					typename Tp5 = kerbal::type_traits::true_type,
					typename Tp6 = kerbal::type_traits::true_type,
					typename Tp7 = kerbal::type_traits::true_type,
					typename Tp8 = kerbal::type_traits::true_type,
					typename Tp9 = kerbal::type_traits::true_type,
					typename Tp10 = kerbal::type_traits::true_type,
					typename Tp11 = kerbal::type_traits::true_type,
					typename Tp12 = kerbal::type_traits::true_type,
					typename Tp13 = kerbal::type_traits::true_type,
					typename Tp14 = kerbal::type_traits::true_type
		>
		struct conjunction : kerbal::type_traits::conditional<Tp0::value, conjunction<Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14>, kerbal::type_traits::false_type>::type
		{
		};

		template <>
		struct conjunction <>: kerbal::type_traits::true_type
		{
		};


		template <typename Tp0 = kerbal::type_traits::false_type,
					typename Tp1 = kerbal::type_traits::false_type,
					typename Tp2 = kerbal::type_traits::false_type,
					typename Tp3 = kerbal::type_traits::false_type,
					typename Tp4 = kerbal::type_traits::false_type,
					typename Tp5 = kerbal::type_traits::false_type,
					typename Tp6 = kerbal::type_traits::false_type,
					typename Tp7 = kerbal::type_traits::false_type,
					typename Tp8 = kerbal::type_traits::false_type,
					typename Tp9 = kerbal::type_traits::false_type,
					typename Tp10 = kerbal::type_traits::false_type,
					typename Tp11 = kerbal::type_traits::false_type,
					typename Tp12 = kerbal::type_traits::false_type,
					typename Tp13 = kerbal::type_traits::false_type,
					typename Tp14 = kerbal::type_traits::false_type
		>
		struct disjunction : kerbal::type_traits::conditional<Tp0::value, kerbal::type_traits::true_type, disjunction<Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14> >::type
		{
		};

		template <>
		struct disjunction <>: kerbal::type_traits::true_type
		{
		};

		/**
		 * @brief gcc 一个神奇的特性, 没有这个特化, disjunction<kerbal::type_traits::false_type> 会直接
		 * 套用 disjunction <>, 即 value 为 true; 而 disjunction<std::false_type> 工作正常
		 */
		template <typename Tp1,
					typename Tp2,
					typename Tp3,
					typename Tp4,
					typename Tp5,
					typename Tp6,
					typename Tp7,
					typename Tp8,
					typename Tp9,
					typename Tp10,
					typename Tp11,
					typename Tp12,
					typename Tp13,
					typename Tp14
		>
		struct disjunction <kerbal::type_traits::false_type, Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14> : kerbal::type_traits::false_type
		{
		};


		template <typename Tp>
		struct disjunction <Tp>: kerbal::type_traits::conditional_boolean<Tp::value>::type
		{
		};

#	else

		MODULE_EXPORT
		template <typename ...Args>
		struct conjunction;

		MODULE_EXPORT
		template <>
		struct conjunction<> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename T>
		struct conjunction<T> : kerbal::type_traits::conditional_boolean<T::value>::type
		{
		};

		MODULE_EXPORT
		template <typename T, typename ...Args>
		struct conjunction<T, Args...> : kerbal::type_traits::conditional<T::value, conjunction <Args...>, kerbal::type_traits::false_type>::type
		{
		};

		MODULE_EXPORT
		template <typename ...Args>
		struct disjunction;

		MODULE_EXPORT
		template <>
		struct disjunction<> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename T>
		struct disjunction<T> : kerbal::type_traits::conditional_boolean<T::value>::type
		{
		};

		MODULE_EXPORT
		template <typename T, typename ...Args>
		struct disjunction<T, Args...> : kerbal::type_traits::conditional<T::value, kerbal::type_traits::true_type, disjunction <Args...>>::type
		{
		};

#	endif

#	if __cplusplus < 201103L

		template <typename Tp, typename Up, typename = Up, typename = Up, typename = Up,
					typename = Up, typename = Up, typename = Up, typename = Up, typename = Up,
					typename = Up, typename = Up, typename = Up, typename = Up, typename = Up>
		struct is_same : kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_same<Tp, Tp> : kerbal::type_traits::true_type
		{
		};

#	else

		MODULE_EXPORT
		template <typename Tp, typename Up, typename ... Types>
		struct is_same: kerbal::type_traits::conjunction<kerbal::type_traits::is_same<Tp, Up>,
														kerbal::type_traits::is_same<Up, Types...> >
		{
		};

		MODULE_EXPORT
		template <typename Tp, typename Up>
		struct is_same<Tp, Up> : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_same<Tp, Tp> : kerbal::type_traits::true_type
		{
		};

#endif
		MODULE_EXPORT
		template <typename>
		struct is_lvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_lvalue_reference<Tp&> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename>
		struct is_rvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_rvalue_reference<Tp&&> : kerbal::type_traits::true_type
		{
		};

#	endif

#	if __cplusplus < 201103L

		template <typename Tp>
		struct is_reference : kerbal::type_traits::is_lvalue_reference<Tp>
		{
		};

#	else

		MODULE_EXPORT
		template <typename Tp>
		struct is_reference : kerbal::type_traits::disjunction<
									kerbal::type_traits::is_lvalue_reference<Tp>,
									kerbal::type_traits::is_rvalue_reference<Tp>
								>
		{
		};

#	endif

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&>
		{
				typedef Tp type;
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&&>
		{
				typedef Tp type;
		};

#	endif

		MODULE_EXPORT
		template <typename >
		struct is_const: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_const<Tp const> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename >
		struct is_volatile: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_volatile<Tp volatile> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_const
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_const<Tp const>
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_volatile
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_volatile<Tp volatile>
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_cv: kerbal::type_traits::remove_const<typename kerbal::type_traits::remove_volatile<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_cvref: kerbal::type_traits::remove_cv<typename kerbal::type_traits::remove_reference<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename>
		struct is_array : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_array<Tp[]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct is_array<Tp[N]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename>
		struct array_traits;

		MODULE_EXPORT
		template <typename Tp>
		struct array_traits<Tp[]>
		{
				typedef Tp value_type;
		};

		MODULE_EXPORT
		template <typename Tp, size_t N>
		struct array_traits<Tp[N]> : kerbal::type_traits::array_traits<Tp[]>
		{
				typedef Tp value_type;
#				if __cplusplus >= 201103L
					static constexpr size_t size = N;
#				else
					static const size_t size = N;
#				endif
		};


		template <typename >
		struct __is_floating_point_helper: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_floating_point_helper<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_floating_point_helper<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_floating_point_helper<long double> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_floating_point: kerbal::type_traits::__is_floating_point_helper<
															typename kerbal::type_traits::remove_cv<Tp>::type
														>
		{
		};

		template <typename>
		struct __is_integral_helper : kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_integral_helper<bool> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<char> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		template <>
		struct __is_integral_helper<char16_t> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<char32_t> : kerbal::type_traits::true_type
		{
		};

#	endif

		template <>
		struct __is_integral_helper<signed char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_integral: kerbal::type_traits::__is_integral_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <class T>
		struct is_arithmetic: kerbal::type_traits::disjunction<is_integral<T>, is_floating_point<T> >
		{
		};

		template <typename >
		struct __is_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename T>
		struct __is_pointer_helper<T*> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename T>
		struct is_pointer: kerbal::type_traits::__is_pointer_helper<typename kerbal::type_traits::remove_cv<T>::type>::type
		{
		};

#	if __cplusplus < 201103L

		struct __for_all_types_has_types_empty_args_helper
		{
		};

		template <template <typename> typename Traits,
										typename T0 = __for_all_types_has_types_empty_args_helper,
										typename T1 = T0,
										typename T2 = T0,
										typename T3 = T0,
										typename T4 = T0,
										typename T5 = T0,
										typename T6 = T0,
										typename T7 = T0,
										typename T8 = T0,
										typename T9 = T0,
										typename T10 = T0,
										typename T11 = T0,
										typename T12 = T0,
										typename T13 = T0,
										typename T14 = T0>
		struct for_all_types : kerbal::type_traits::conjunction<
			Traits<T0>, Traits<T1>, Traits<T2>, Traits<T3>, Traits<T4>,
			Traits<T5>, Traits<T6>, Traits<T7>, Traits<T8>, Traits<T9>,
			Traits<T10>, Traits<T11>, Traits<T12>, Traits<T13>, Traits<T14> >
		{
		};

		template <template <typename> typename Traits>
		struct for_all_types<Traits, __for_all_types_has_types_empty_args_helper> : kerbal::type_traits::true_type
		{
		};

		template <template <typename> typename Traits,
										typename T0 = __for_all_types_has_types_empty_args_helper,
										typename T1 = T0,
										typename T2 = T0,
										typename T3 = T0,
										typename T4 = T0,
										typename T5 = T0,
										typename T6 = T0,
										typename T7 = T0,
										typename T8 = T0,
										typename T9 = T0,
										typename T10 = T0,
										typename T11 = T0,
										typename T12 = T0,
										typename T13 = T0,
										typename T14 = T0>
		struct has_types : kerbal::type_traits::disjunction<
			Traits<T0>, Traits<T1>, Traits<T2>, Traits<T3>, Traits<T4>,
			Traits<T5>, Traits<T6>, Traits<T7>, Traits<T8>, Traits<T9>,
			Traits<T10>, Traits<T11>, Traits<T12>, Traits<T13>, Traits<T14> >
		{
		};

		template <template <typename> typename Traits>
		struct has_types<Traits, __for_all_types_has_types_empty_args_helper> : kerbal::type_traits::true_type
		{
		};

#	else

		MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct for_all_types : kerbal::type_traits::conjunction<Traits<Types>...>
		{
		};

		MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct has_types : kerbal::type_traits::disjunction<Traits<Types>...>
		{
		};

#	endif

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_ */
