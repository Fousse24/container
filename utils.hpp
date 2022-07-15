/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:32:19 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/15 17:33:06 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iterator>
namespace ft {

template <bool B, class T = void>
struct enable_if_c { typedef T type; };

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};

struct true_type 
{ 
	static const bool value = true; 
	operator bool(){ return value; };
	bool	operator()() { return value; };
};
struct false_type 
{	
	static const bool value = false;
	operator bool(){ return value; };
	bool	operator()() { return value; };
};

template <class T, class U> struct is_same				: public false_type {};
template <class T> struct is_same<T, T>					: public true_type {};

template <class T, class U> struct is_not_same			: public true_type {};
template <class T> struct is_not_same<T, T>				: public false_type {};

template <class T> struct is_input_iter								: public false_type {};
template <> struct is_input_iter<std::random_access_iterator_tag>	: public true_type {};

// Default false
template <class T> struct is_integral 					: public false_type {};

template <class T> struct is_integral<const T> 			: public is_integral<T> {};
template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
template <class T> struct is_integral<volatile T> 		: public is_integral<T>{};

// template<typename T> struct remove_const{typedef T type;};
// template<typename T> struct remove_const<const T>{typedef T type;};  //cool stuff

template<> struct is_integral<char> 					: public true_type{};
template<> struct is_integral<signed char> 				: public true_type{};
template<> struct is_integral<unsigned char> 			: public true_type{};
template<> struct is_integral<wchar_t> 					: public true_type {};
template<> struct is_integral<char16_t> 				: public true_type{};
template<> struct is_integral<char32_t> 				: public true_type{};

template<> struct is_integral<short> 					: public true_type{};
template<> struct is_integral<unsigned short>			: public true_type{};

template<> struct is_integral<int> 						: public true_type{};
template<> struct is_integral<unsigned int> 			: public true_type{};

template<> struct is_integral<long> 					: public true_type{};
template<> struct is_integral<unsigned long> 			: public true_type{};

template<> struct is_integral<bool> 					: public true_type{};



template <class T> struct is_not_integral 					: public true_type {};

template <class T> struct is_not_integral<const T> 			: public is_not_integral<T> {};
template <class T> struct is_not_integral<volatile const T> : public is_not_integral<T>{};
template <class T> struct is_not_integral<volatile T> 		: public is_not_integral<T>{};

template<> struct is_not_integral<char> 					: public false_type{};
template<> struct is_not_integral<signed char> 				: public false_type{};
template<> struct is_not_integral<unsigned char> 			: public false_type{};
template<> struct is_not_integral<wchar_t> 					: public false_type {};
template<> struct is_not_integral<char16_t> 				: public false_type{};
template<> struct is_not_integral<char32_t> 				: public false_type{};

template<> struct is_not_integral<short> 					: public false_type{};
template<> struct is_not_integral<unsigned short>			: public false_type{};

template<> struct is_not_integral<int> 						: public false_type{};
template<> struct is_not_integral<unsigned int> 			: public false_type{};

template<> struct is_not_integral<long> 					: public false_type{};
template<> struct is_not_integral<unsigned long> 			: public false_type{};

template<> struct is_not_integral<bool> 					: public false_type{};


// template<> struct is_integral<unsigned __int8> : public true_type{};
// template<> struct is_integral<unsigned __int16> : public true_type{};
// template<> struct is_integral<unsigned __int32> : public true_type{};
// template<> struct is_integral<__int8> : public true_type{};
// template<> struct is_integral<__int16> : public true_type{};
// template<> struct is_integral<__int32> : public true_type{};
// template<> struct is_integral<unsigned __int64> : public true_type{};
// template<> struct is_integral<__int64> : public true_type{};
// template<> struct is_integral< ::boost::ulong_long_type> : public true_type{};
// template<> struct is_integral< ::boost::long_long_type> : public true_type{};
// template<> struct is_integral<unsigned __int64> : public true_type{};
// template<> struct is_integral<__int64> : public true_type{};
        
// template<> struct is_integral<boost::int128_type> : public true_type{};
// template<> struct is_integral<boost::uint128_type> : public true_type{};

}
#endif
