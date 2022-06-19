#ifndef UTILITY_HPP
# define UTILITY_HPP

#include "algorithm.hpp"
#include "type_traits.hpp"
#include "iterators/iterator_traits.hpp"

namespace ft{

template< class T1, class T2 > struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	T1	first;
	T2	second;

	pair()								: first(), second() {}
	pair( const T1& x, const T2& y )	: first(x), second(y) {}
	pair( const pair<T1, T2>& p )		: first(p.first), second(p.second) {}
	template< class U1, class U2 >
	pair( const pair<U1, U2>& p )		: first(p.first), second(p.second) {}

	pair& operator=( const pair& other )
	{
		this->first = other.first;
		this->second = other.second;
		return (*this);
	}
};

template< class T1, class T2 >
pair<T1, T2> make_pair( T1 t, T2 u )
{
	return (pair<T1, T2>(t, u));
}

template< class T1, class T2 >
bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (lhs.first != rhs.first || lhs.second != rhs.second);
}

template< class T1, class T2 >
bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (lhs.first < rhs.first ? true : lhs.first > rhs.first ? false : lhs.second < rhs.second);
}

template< class T1, class T2 >
bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(rhs < lhs));
}

template< class T1, class T2 >
bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (rhs < lhs);
}

template< class T1, class T2 >
bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (rhs <= lhs);
}
};

#endif