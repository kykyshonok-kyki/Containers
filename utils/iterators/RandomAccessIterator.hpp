#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "../type_traits.hpp"

namespace ft{

template< class Iter >
class RandomAccessIterator
{
public:

	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter *>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter *>::value_type		value_type;
	typedef typename iterator_traits<Iter *>::difference_type	difference_type;
	typedef typename iterator_traits<Iter *>::pointer			pointer;
	typedef typename iterator_traits<Iter *>::reference			reference;

protected:
	pointer	c_point;

public:
	RandomAccessIterator() : c_point() {}
	explicit RandomAccessIterator( pointer x ) : c_point(x) {}
	~RandomAccessIterator( void ) {}

	RandomAccessIterator(const RandomAccessIterator<typename ft::remove_const<value_type>::type >& src) : c_point(&(*src)) {}

	RandomAccessIterator& operator=( const RandomAccessIterator<typename ft::remove_const<value_type>::type >& other )
	{
		this->c_point = &(*other);
		return (*this);
	}

	iterator_type base() const
	{
		return (*(this->c_point));
	}

	reference operator*() const
	{
		return (*(this->c_point));
	}
	pointer operator->() const
	{
		return (std::addressof(operator*()));
	}

	reference operator[]( difference_type n ) const
	{
		return (this->c_point[n]);
	}

	RandomAccessIterator& operator++()
	{
		++this->c_point;
		return (*this);
	}
	RandomAccessIterator& operator--()
	{
		--this->c_point;
		return (*this);
	}
	RandomAccessIterator operator++( int )
	{
		RandomAccessIterator	tmp(this->c_point);
		++this->c_point;
		return (tmp);
	}
	RandomAccessIterator operator--( int )
	{
		RandomAccessIterator	tmp(this->c_point);
		--this->c_point;
		return (tmp);
	}
	RandomAccessIterator operator+( difference_type n ) const
	{
		return (RandomAccessIterator(this->c_point + n));
	}
	RandomAccessIterator operator-( difference_type n ) const
	{
		return (RandomAccessIterator(this->c_point - n));
	}
	RandomAccessIterator& operator+=( difference_type n )
	{
		this->c_point = this->c_point + n;
		return (*this);
	}
	RandomAccessIterator& operator-=( difference_type n )
	{
		this->c_point = this->c_point - n;
		return (*this);
	}
};

template< class Iterator1, class Iterator2 >
bool operator==( const RandomAccessIterator<Iterator1>& lhs,
                 const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) == &(*rhs) ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator!=( const RandomAccessIterator<Iterator1>& lhs,
                 const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) != &(*rhs) ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator<( const RandomAccessIterator<Iterator1>& lhs,
                const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) < &(*rhs) ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator<=( const RandomAccessIterator<Iterator1>& lhs,
                 const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) <= &(*rhs) ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator>( const RandomAccessIterator<Iterator1>& lhs,
                const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) > &(*rhs) ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator>=( const RandomAccessIterator<Iterator1>& lhs,
				 const RandomAccessIterator<Iterator2>& rhs )
{
	return (&(*lhs) >= &(*rhs) ? true : false);
}

template< class Iter >
RandomAccessIterator<Iter>
	operator+( typename RandomAccessIterator<Iter>::difference_type n,
               const RandomAccessIterator<Iter>& it )
{
	return (it + n);
}

template< class Iter >
RandomAccessIterator<Iter>
	operator-( typename RandomAccessIterator<Iter>::difference_type n,
               const RandomAccessIterator<Iter>& it )
{
	return (it - n);
}

};

#endif