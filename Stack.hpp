// Writed by wgaunt (wgaunt@student.21-school.ru) in 5.02.2022

#ifndef STACK_HPP
# define STACK_HPP

# include <string>
# include "Vector.hpp"

namespace ft{

template< class T, class Container = ft::Vector<T> >
class	Stack {

protected:
	Container	c;

public:

	typedef Container	container_type;

	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	explicit Stack(const Container& other = Container()) : c(other){}
	virtual ~Stack( void ) {}

	Stack&	operator=(const Stack& src)
	{
		this->c = src.c;
		return (*this);
	}

	bool	operator==( const Stack<T, Container>& rhs )
	{
		return (this->c == rhs.c ? true : false);
	}

	bool	operator!=( const Stack<T, Container>& rhs )
	{
		return (this->c != rhs.c ? true : false);
	}

	bool	operator<=( const Stack<T, Container>& rhs )
	{
		return (this->c <= rhs.c ? true : false);
	}

	bool	operator>=( const Stack<T, Container>& rhs )
	{
		return (this->c >= rhs.c ? true : false);
	}

	bool	operator>( const Stack<T, Container>& rhs )
	{
		return (this->c > rhs.c ? true : false);
	}

	bool	operator<( const Stack<T, Container>& rhs )
	{
		return (this->c < rhs.c ? true : false);
	}


	reference	top()
	{
		return (this->c.back());
	}

	const_reference	top() const
	{
		return (this->c.back());
	}

	bool	empty() const
	{
		return (this->c.empty());
	}

	size_type	size() const
	{
		return (this->c.size());
	}

	void	push( const value_type& value )
	{
		this->c.push_back(value);
	}

	void	pop()
	{
		this->c.pop_back();
	}
};
};

#endif