// Writed by wgaunt (wgaunt@student.21-school.ru) in 6.02.2022

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <stdint.h>

namespace ft{

template< class T >
struct remove_const				{ typedef T type; };
template< class T >
struct remove_const<const T>	{ typedef T type; };

template< bool B, class T = void >
struct enable_if { };

template<class T>
struct enable_if<true, T> { typedef T type; };

template<class T, T v>
struct integral_constant
{
	static const T				value = v;
	typedef	T					value_type;
	typedef integral_constant	type;
	operator value_type() const { return value; }
};

typedef integral_constant<bool, true>	my_true_type;
typedef integral_constant<bool, false>	my_false_type;

template< class T > struct is_integral				: public my_false_type {};
template<> struct is_integral<bool>					: public my_true_type {};
template<> struct is_integral<char>					: public my_true_type {};
template<> struct is_integral<char16_t>				: public my_true_type {};
template<> struct is_integral<char32_t>				: public my_true_type {};
template<> struct is_integral<wchar_t>				: public my_true_type {};
template<> struct is_integral<short>				: public my_true_type {};
template<> struct is_integral<int>					: public my_true_type {};
template<> struct is_integral<long>					: public my_true_type {};
template<> struct is_integral<long long>			: public my_true_type {};
template<> struct is_integral<unsigned char>		: public my_true_type {};
template<> struct is_integral<signed char>			: public my_true_type {};
template<> struct is_integral<unsigned short>		: public my_true_type {};
template<> struct is_integral<unsigned int>			: public my_true_type {};
template<> struct is_integral<unsigned long>		: public my_true_type {};
template<> struct is_integral<unsigned long long>	: public my_true_type {};

template<> struct is_integral<const bool>				: public my_true_type {};
template<> struct is_integral<const char>				: public my_true_type {};
template<> struct is_integral<const char16_t>			: public my_true_type {};
template<> struct is_integral<const char32_t>			: public my_true_type {};
template<> struct is_integral<const wchar_t>			: public my_true_type {};
template<> struct is_integral<const short>				: public my_true_type {};
template<> struct is_integral<const int>				: public my_true_type {};
template<> struct is_integral<const long>				: public my_true_type {};
template<> struct is_integral<const long long>			: public my_true_type {};
template<> struct is_integral<const unsigned char>		: public my_true_type {};
template<> struct is_integral<const signed char>		: public my_true_type {};
template<> struct is_integral<const unsigned short>		: public my_true_type {};
template<> struct is_integral<const unsigned int>		: public my_true_type {};
template<> struct is_integral<const unsigned long>		: public my_true_type {};
template<> struct is_integral<const unsigned long long>	: public my_true_type {};

};

#endif