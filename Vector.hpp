// Writed by wgaunt (wgaunt@student.21-school.ru) in 5.02.2022

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <string>
# include <vector>
# include <iterator>
# include "utils/algorithm.hpp"
# include "utils/iterators/reverse_iterator.hpp"
# include "utils/iterators/RandomAccessIterator.hpp"
# include "utils/type_traits.hpp"
# include <iostream>

namespace ft{

template< class T, class Allocator = std::allocator<T> >
class	Vector {

public:

	typedef T			value_type;
	typedef Allocator	allocator_type;

	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef typename	Allocator::pointer			pointer;
	typedef typename	Allocator::const_pointer	const_pointer;
	typedef RandomAccessIterator<value_type>		iterator;
	typedef RandomAccessIterator<const value_type>	const_iterator;
	typedef reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef reverse_iterator<iterator>				reverse_iterator;

private:
	pointer			_array;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_alloc;

	template< class InputIt >
	difference_type	find_len(InputIt begin, InputIt end)
	{
		difference_type	res = 0;

		for (; begin != end; begin++, res++) {}
		return (res);
	}

public:

	explicit Vector( const Allocator& alloc = Allocator() ) : _array(0), _size(0), _capacity(0), _alloc(alloc) {}
	explicit Vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_size(count), _capacity(count), _alloc(alloc)
	{
		this->_array = this->_alloc.allocate(count);
		for (size_type i = 0; i < count; i++)
			this->_alloc.construct(this->_array + i, value);
	}
	template< class InputIt >
	Vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0) : _alloc(alloc)
	{
		this->_capacity = 0;
		this->_size = 0;
		this->_array = this->_alloc.allocate(find_len(first, last));
		this->_capacity = find_len(first, last);
		for (size_type i = 0; first != last; i++, first++)
		{
			this->_alloc.construct(this->_array + i, *first);
			this->_size++;
		}
	}
	Vector( const Vector& other ) : _size(0), _capacity(0)
	{
		*this = other;
	}

	virtual ~Vector( void )
	{
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		if (this->_capacity)
			this->_alloc.deallocate(this->_array, this->_capacity);
	}

	Vector&	operator=(const Vector& src)
	{
		if (this == &src)
			return (*this);
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		if (this->_capacity < src._size)
		{
			if (this->_capacity)
				this->_alloc.deallocate(this->_array, this->_capacity);
			this->_capacity = src._size;
			this->_array = this->_alloc.allocate(this->_capacity);
		}
		this->_size = src._size;
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.construct(this->_array + i, *(src._array + i));
		return (*this);
	}

	void assign( size_type count, const T& value )
	{
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		if (this->_capacity < count)
		{
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_capacity = 0;
			this->_size = 0;
			this->_array = this->_alloc.allocate(count);
			this->_capacity = count;
		}
		this->_size = count;
		for (size_type i = 0; i < this->_size && i < count; i++)
			this->_alloc.construct(this->_array + i, value);
	}
	template< class InputIt >
	void assign( InputIt first, InputIt last,
		typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0 )
	{
		size_type	new_size = this->find_len(first, last);

		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		this->_size = 0;
		if (this->_capacity < new_size)
		{
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_capacity = 0;
			this->_array = this->_alloc.allocate(new_size);
			this->_capacity = new_size;
		}
		for (size_type i = 0; first != last; first++, i++)
		{
			this->_alloc.construct(this->_array + i, *first);
			this->_size++;
		}
	}
	allocator_type get_allocator() const
	{
		return (this->_alloc);
	}
	reference at( size_type pos )
	{
		if (pos >= this->_size)
			throw std::out_of_range("Vector: at: out of range");
		return (*(this->_array + pos));
	}
	const_reference at( size_type pos ) const
	{
		if (pos >= this->_size)
			throw std::out_of_range("Vector: at: out of range");
		return (*(this->_array + pos));
	}
	reference operator[]( size_type pos )
	{
		return (*(this->_array + pos));
	}
	const_reference operator[]( size_type pos ) const
	{
		return (*(this->_array + pos));
	}
	reference front()
	{
		return (*(this->_array));
	}
	const_reference front() const
	{
		return (*(this->_array));
	}
	reference back()
	{
		return (*(this->_array + this->_size - 1));
	}
	const_reference back() const
	{
		return (*(this->_array + this->_size - 1));
	}
	T* data()
	{
		return (this->_array);
	}
	const T* data() const
	{
		return (this->_array);
	}

	iterator begin()
	{
		return (this->_size ? iterator(this->_array) : this->end());
	}
	const_iterator begin() const
	{
		return (this->_size ? const_iterator(this->_array) : this->end());
	}
	iterator end()
	{
		return (iterator(this->_array + this->_size));
	}
	const_iterator end() const
	{
		return (const_iterator(this->_array + this->_size));
	}
	reverse_iterator rbegin()
	{
		return (this->_size ? reverse_iterator(end()) : this->rend());
	}
	const_reverse_iterator rbegin() const
	{
		return (this->_size ? const_reverse_iterator(end()) : this->rend());
	}
	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}
	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}


	bool	empty() const
	{
		return (this->_size ? false : true);
	}

	size_type	size() const
	{
		return (this->_size);
	}

	size_type max_size() const
	{
		return (this->_alloc.max_size());
	}
	void reserve( size_type new_cap )
	{
		if (new_cap > this->_capacity)
		{
			pointer	new_array = this->_alloc.allocate(new_cap * 2);
			try
			{
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(new_array + i, *(this->_array + i));
				}
			}
			catch(const std::exception& e)
			{
				for (size_type i = 0; new_array + i && i < this->_size; i++)
					this->_alloc.destroy(new_array + i);
				this->_alloc.deallocate(new_array, new_cap * 2);
				throw;
			}
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			if (this->_capacity)
				this->_alloc.deallocate(this->_array, this->_capacity);
			this->_array = new_array;
			this->_capacity = new_cap * 2;
		}
	}
	size_type capacity() const
	{
		return (this->_capacity);
	}


	void clear()
	{
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		this->_size = 0;
	}
	iterator insert( iterator pos, const T& value )
	{
		size_type		size = this->_size + 1;
		difference_type	i_pos = 0;

		if (this->_array)
			i_pos = this->find_len(this->begin(), pos);
		if (size > this->_capacity)
		{
			pointer	new_array = this->_alloc.allocate(size);
			try
			{
				for (size_type end = size - 1; end > static_cast<size_type>(i_pos); end--)
					this->_alloc.construct(new_array + end, *(this->_array + end - 1));
				this->_alloc.construct(new_array + i_pos, value);
				for (size_type i = i_pos - 1; i > 0; i--)
					this->_alloc.construct(new_array + i, *(this->_array + i));
				if (pos != this->begin())
					this->_alloc.construct(new_array, *(this->_array));
			}
			catch(const std::exception& e)
			{
				for (size_type i = size - 1; new_array + i && i > 0; i--)
					this->_alloc.destroy(new_array + i);
				this->_alloc.deallocate(new_array, size);
				throw;
			}
			for (size_t i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_capacity = size;
			this->_array = new_array;
		}
		else
		{
			for (size_type end = this->_size - 1; end > static_cast<size_type>(i_pos); end--)
			{
				this->_alloc.destroy(this->_array + end);
				this->_alloc.construct(this->_array + end, *(this->_array + end - 1));
			}
			this->_alloc.destroy(this->_array + i_pos);
			this->_alloc.construct(this->_array + i_pos, value);
		}
		this->_size = size;
		return (iterator(this->_array + i_pos));
	}
	void insert( iterator pos, size_type count, const T& value )
	{
		if (count == 0)
			return ;

		size_type		size = this->_size + count;
		difference_type	i_pos = 0;

		if (this->_array)
			i_pos = find_len(this->begin(), pos) + count - 1;
		if (size > this->_capacity)
			this->resize(size, T());
		for (size_type end = this->_size - 1; end > static_cast<size_type>(i_pos); end--)
		{
			this->_alloc.destroy(this->_array + end);
			this->_alloc.construct(this->_array + end, *(this->_array + end - count));
		}
		while (count >= 0)
		{
			this->_alloc.destroy(this->_array + i_pos);
			this->_alloc.construct(this->_array + i_pos, value);
			if (!count)
				break ;
			--i_pos;
			--count;
		}
	}
	template< class InputIt >
	void insert( iterator pos, InputIt first, InputIt last,
		typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0 )
	{
		difference_type	count = this->find_len(first, last);
		difference_type	size = count + this->_size;
		difference_type	i_pos = size - 1;

		if (this->_array)
			i_pos = this->find_len(this->begin(), pos) + count - 1;
		if (static_cast<size_type>(size) > this->_capacity)
		{
			pointer			new_array = this->_alloc.allocate(size);
			difference_type	i = this->find_len(this->begin(), pos);
			try
			{
				for (difference_type end = size - 1; end > i_pos; end--)
					this->_alloc.construct(new_array + end, *(this->_array + end - count));
				--first;
				--last;
				while (first != last)
				{
					this->_alloc.construct(new_array + i_pos, *last);
					--i_pos;
					--last;
				}
				for ( ; i > 0; i--)
					this->_alloc.construct(new_array + i, *(this->_array + i));
				if (pos != this->begin())
					this->_alloc.construct(new_array, *(this->_array));
			}			
			catch(...)
			{
				++i;
				difference_type	end = this->find_len(this->begin(), pos);
				for (; i <= end; i++)
					this->_alloc.destroy(new_array + i);
				this->_alloc.deallocate(new_array, size);
				throw;
			}
			for (size_t i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_array + i);
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_capacity = size;
			this->_array = new_array;
		}
		else
		{
			for (difference_type end = this->_size - 1; end > i_pos; end--)
			{
				this->_alloc.destroy(this->_array + end);
				this->_alloc.construct(this->_array + end, *(this->_array + end - count));
			}
			--first;
			--last;
			while (first != last)
			{
				this->_alloc.destroy(this->_array + i_pos);
				this->_alloc.construct(this->_array + i_pos, *last);
				--i_pos;
				--last;
			}
		}
		this->_size = size;
	}
	iterator erase( iterator pos )
	{
		difference_type i_pos = this->find_len(this->begin(), pos);

		for (difference_type i = i_pos + 1; i < static_cast<difference_type>(this->_size); i++)
		{
			this->_alloc.destroy(this->_array + i);
			this->_alloc.construct(this->_array + i - 1, *(this->_array + i));
		}
		this->_alloc.destroy(this->_array + this->_size - 1);
		--this->_size;
		return (iterator(this->_array + i_pos));
	}
	iterator erase( iterator first, iterator last )
	{
		difference_type	c_size = this->find_len(first, last);
		difference_type	i_pos = this->find_len(this->begin(), last);
		difference_type	start = this->find_len(this->begin(), first);

		for (difference_type i = start; i < static_cast<difference_type>(this->_size); i++)
		{
			if (i_pos < static_cast<difference_type>(this->_size))
			{
				this->_alloc.destroy(this->_array + i);
				this->_alloc.construct(this->_array + i, *(this->_array + i_pos));
				++i_pos;
			}
			else
				this->_alloc.destroy(this->_array + i);
		}
		this->_size -= c_size;
		return (iterator(this->_array + start));
	}
	void push_back( const T& value )
	{
		if (this->_size >= this->_capacity)
			this->reserve(this->_capacity + 1);
		this->_alloc.construct(this->_array + this->_size, value);
		++(this->_size);
	}
	void pop_back()
	{
		this->_alloc.destroy(this->_array + this->_size - 1);
		--(this->_size);
	}
	void resize( size_type count, T value = T() )
	{
		if (count > this->_size)
		{
			this->reserve(count);
			for (size_type i = this->_size; i < count; i++)
				this->_alloc.construct(this->_array + i, value);
		}
		for (size_type i = count; i < this->_size; i++)
			this->_alloc.destroy(this->_array + i);
		this->_size = count;
	}
	void swap( Vector& other )
	{
		std::swap(this->_array, other._array);
		std::swap(this->_alloc, other._alloc);
		std::swap(this->_size, other._size);
		std::swap(this->_capacity, other._capacity);
	}

};

	template< class T, class Allocator >
	bool	operator==( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		std::size_t	 len = lhs.size();
		for (std::size_t	 i = 0; i < len; i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template< class T, class Allocator >
	bool	operator!=( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T, class Allocator >
	bool	operator<( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Allocator >
	bool	operator<=( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class T, class Allocator >
	bool	operator>=( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class T, class Allocator >
	bool	operator>( const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T, class Allocator >
	void swap( Vector<T,Allocator>& lhs, Vector<T,Allocator>& rhs )
	{
		std::swap(lhs._array, rhs._array);
		std::swap(lhs.__alloc, rhs.__alloc);
		std::swap(lhs._size, rhs._size);
		std::swap(lhs._capacity, rhs._capasity);
	}
};

#endif