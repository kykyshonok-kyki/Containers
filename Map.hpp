// Writed by wgaunt (wgaunt@student.21-school.ru) in 5.02.2022

#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <vector>
# include <iterator>
# include "utils/utility.hpp"
# include "utils/AVLTree.hpp"
# include "utils/algorithm.hpp"
# include "utils/iterators/TreeIt.hpp"
# include "utils/type_traits.hpp"
# include <functional>

namespace ft{

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>class	map {

public:

	typedef	Key												key_type;
	typedef	T												mapped_type;

	typedef	ft::pair<const Key, T>							value_type;
	typedef	std::size_t										size_type;
	typedef	std::ptrdiff_t		 							difference_type;
	typedef	Compare											key_compare;
	typedef	Allocator										allocator_type;
	typedef	value_type&										reference;
	typedef	const value_type&								const_reference;
	typedef typename Allocator::pointer						pointer;
	typedef	typename Allocator::const_pointer				const_pointer;
	typedef	ft::TreeIt<key_type, mapped_type>				iterator;
	typedef	ft::TreeIt<const key_type, const mapped_type>	const_iterator;
	typedef	ft::reverse_iterator<iterator>					reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	class	value_compare : std::binary_function<value_type, value_type, bool>
	{
		protected:
			key_compare	comp;
		public:
			value_compare( key_compare c ) : comp(c) {}
			bool	operator()( const value_type& lhs, const value_type& rhs ) const
			{
				return (this->comp(lhs.first, rhs.first));
			}
	};

private:
	typedef AVLTree<Key, T>	tree_type;

	tree_type		_tree;
	key_compare		_compare;
	allocator_type	_alloc;

	template< class InputIt >
	size_type	size_dif(InputIt first, InputIt last)
	{
		size_type	size = 0;

		while (first != last)
		{
			++size;
			++first;
		}
		return (size);
	}

public:

	map() : _tree(), _compare(Compare()), _alloc(Allocator()) {}

	explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _tree(), _compare(comp), _alloc(alloc) {}

	template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator() ) : _tree(this->size_dif(first, last)), _compare(comp), _alloc(alloc)
	{
		while (first != last)
		{
			this->_tree.insert(*first);
			++first;
		}
	}

	map( const map& other ) : _tree(other._tree), _compare(other._compare), _alloc(other._alloc) {}

	~map() {}

	map& operator=( const map& other )
	{
		this->_tree = other._tree;
		this->_compare = other._compare;
		this->_alloc = other._alloc;
		return (*this);
	}

	allocator_type get_allocator() const
	{
		return (this->_alloc);
	}

	T& at( const Key& key )
	{
		return ((this->_tree.at(key)).pair.second);
	}

	const T& at( const Key& key ) const
	{
		return ((this->_tree.at(key)).pair.second);
	}

	T& operator[]( const Key& key )
	{
		AVLTNode<key_type, mapped_type>	*res = &(this->_tree[key]);

		return (res->pair.second);
	}

	iterator begin()
	{
		if (this->_tree.get_size() == 0)
			return (iterator(this->_tree.get_end(), &(this->_tree)));
		return (iterator(this->_tree.findMin(), &(this->_tree)));
	}

	const_iterator begin() const
	{
		if (this->_tree.get_size() == 0)
			return (const_iterator(this->_tree.get_end(), &(this->_tree)));
		return (const_iterator(this->_tree.findMin(), &(this->_tree)));
	}

	iterator end()
	{
		return (iterator(this->_tree.get_end(), &(this->_tree)));
	}

	const_iterator end() const
	{
		AVLTNode<key_type, mapped_type>*	resN = this->_tree.get_end();
		return (const_iterator(resN, &this->_tree));
	}

	reverse_iterator rbegin()
	{
		if (this->_tree.get_size() == 0)
			return (this->rend());
		return (reverse_iterator(this->end()));
	}

	const_reverse_iterator rbegin() const
	{
		if (this->_tree.get_size() == 0)
			return (this->rend());
		return (const_reverse_iterator(this->end()));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(this->begin()));
	}

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	bool empty() const
	{
		return (this->_tree.get_size() ? false : true);
	}

	size_type size() const
	{
		return (this->_tree.get_size());
	}

	size_type max_size() const
	{
		return (this->_tree.gmax_size());
	}

	void clear()
	{
		this->_tree.clear();
	}

	ft::pair<iterator, bool> insert( const value_type& value )
	{
		ft::pair<iterator, bool>		res;
		AVLTNode<key_type, mapped_type>	*node_res;

		node_res = this->_tree.insert(value);
		if (!node_res)
		{
			res.first = iterator(&this->_tree[value.first], &this->_tree);
			res.second = 0;
		}
		else
		{
			res.second = 1;
			res.first = iterator(node_res, &this->_tree);
		}
		return (res);
	}

	iterator insert( iterator hint, const value_type& value )
	{
		AVLTNode<key_type, mapped_type>	*node_res;

		(void)hint;
		node_res = this->_tree.insert(value);
		if (!node_res)
			return (iterator(&this->_tree[value.first], &this->_tree));
		else
			return (iterator(node_res, &this->_tree));
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{
		while (first != last)
		{
			this->_tree.insert(*first);
			++first;
		}
	}

	void erase( iterator pos )
	{
		this->_tree.remove((*pos).first);
	}

	void erase( iterator first, iterator last )
	{
		while (first != last)
		{
			this->erase(first);
			++first;
		}
	}

	size_type erase( const Key& key )
	{
		return (this->_tree.remove(key));
	}

	void swap( map& other )
	{
		map	tmp(other);

		other._tree = this->_tree;
		other._alloc = this->_alloc;
		this->_tree = tmp._tree;
		this->_alloc = tmp._alloc;
		std::swap(this->_compare, other._compare);
	}

	size_type count( const Key& key ) const
	{
		return (static_cast<size_type>(this->_tree.findKey(key)));
	}

	iterator find( const Key& key )
	{
		AVLTNode<key_type, mapped_type>	*res = this->_tree.find(key);

		if (!res)
			return (this->end());
		return (iterator(res, &this->_tree));
	}

	const_iterator find( const Key& key ) const
	{
		AVLTNode<key_type, mapped_type>	*res = this->_tree.find(key);

		if (!res)
			return (this->end());
		return (const_iterator(res, &this->_tree));
	}

	ft::pair<iterator,iterator> equal_range( const Key& key )
	{
		ft::pair<iterator, iterator>	res;
		iterator						end = this->end();

		res.first = this->begin();
		while (res.first != end && this->_compare((*(res.first)).first, key))
		{
			++res.first;
		}
		res.second = this->begin();
		while (res.second != end && !(this->_compare(key, (*(res.second)).first)))
		{
			++res.second;
		}
		return (res);
	}

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
	{
		ft::pair<const_iterator, const_iterator>	res;
		const_iterator								end = this->end();

		res.first = this->begin();
		while (res.first != end && this->_compare((*(res.first)).first, key))
		{
			++res.first;
		}
		res.second = this->begin();
		while (res.second != end && !(this->_compare(key, (*(res.second)).first)))
		{
			++res.second;
		}
		return (res);
	}

	iterator lower_bound( const Key& key )
	{
		iterator	end = this->end();
		iterator	res = this->begin();
		while (res != end && this->_compare((*res).first, key))
		{
			++res;
		}
		return (res);
	}

	const_iterator lower_bound( const Key& key ) const
	{
		const_iterator	end = this->end();
		const_iterator	res = this->begin();
		while (res != end && this->_compare((*res).first, key))
		{
			++res;
		}
		return (res);
	}

	iterator upper_bound( const Key& key )
	{
		iterator	end = this->end();
		iterator	res = this->begin();
		while (res != end && !this->_compare(key, (*res).first))
		{
			++res;
		}
		return (res);
	}

	const_iterator upper_bound( const Key& key ) const
	{
		const_iterator	end = this->end();
		const_iterator	res = this->begin();
		while (res != end && !this->_compare(key, (*res).first))
		{
			++res;
		}
		return (res);
	}

	key_compare key_comp() const
	{
		return (this->_compare);
	}

	value_compare value_comp() const
	{
		return (value_compare(this->_compare));
	}

};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	itl = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	itr = rhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	endl = lhs.end();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	endr = rhs.end();

	while (itl != endl && itr != endr)
	{
		if (*itl != *itr)
			return (false);
		++itl;
		++itr;
	}
	return (true);
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(rhs == lhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(rhs < lhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs < rhs));
}

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs )
{
	lhs.swap(rhs);
}

};

#endif