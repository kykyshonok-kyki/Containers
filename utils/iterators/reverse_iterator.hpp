// Writed by wgaunt (wgaunt@student.21-school.ru) in 6.02.2022

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{

template< class Iter >
class reverse_iterator
{
public:

	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;

protected:
	iterator_type	current;

public:
	reverse_iterator() : current() {}
	explicit reverse_iterator( iterator_type x ) : current(x) {}
	template< class U >
	reverse_iterator( const reverse_iterator<U>& other ) : current(other.current) {}
	~reverse_iterator( void ) {}

	template< class U >
	reverse_iterator& operator=( const reverse_iterator<U>& other )
	{
		this->current = other->current;
		return (*this);
	}

	iterator_type base() const
	{
		return (this->current);
	}

	reference operator*() const
	{
		iterator_type	tmp = this->current;
		return (*--tmp);
	}
	pointer operator->() const
	{
		return (std::addressof(operator*()));
	}

	reference operator[]( difference_type n ) const
	{
		return (this->current[-n-1]);
	}

	reverse_iterator& operator++()
	{
		--this->current;
		return (*this);
	}
	reverse_iterator& operator--()
	{
		++this->current;
		return (*this);
	}
	reverse_iterator operator++( int )
	{
		reverse_iterator	tmp(this->current);
		--this->current;
		return (tmp);
	}
	reverse_iterator operator--( int )
	{
		reverse_iterator	tmp(this->current);
		++this->current;
		return (tmp);
	}
	reverse_iterator operator+( difference_type n ) const
	{
		return (reverse_iterator(this->current - n));
	}
	reverse_iterator operator-( difference_type n ) const
	{
		return (reverse_iterator(this->current + n));
	}
	reverse_iterator& operator+=( difference_type n )
	{
		this->current = this->current - n;
		return (*this);
	}
	reverse_iterator& operator-=( difference_type n )
	{
		this->current = this->current + n;
		return (*this);
	}
};

template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() == rhs.base() ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() != rhs.base() ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() < rhs.base() ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs,
                 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() <= rhs.base() ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() > rhs.base() ? true : false);
}

template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs,
				 const reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() >= rhs.base() ? true : false);
}

template< class Iter >
reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
               const reverse_iterator<Iter>& it )
{
	return (it.base() + n);
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs )
{
	return (lhs.base() - rhs.base());
}
};

#endif