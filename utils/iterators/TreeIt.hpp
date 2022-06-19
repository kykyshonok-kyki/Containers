#ifndef TREEIT_HPP
# define TREEIT_HPP

#include "iterator_traits.hpp"
#include "../type_traits.hpp"
#include "../AVLTree.hpp"
#include "../utility.hpp"

namespace ft{

template<class rKeyType, class rT>
class TreeIt
{
private:
	typedef pair<rKeyType, rT>	rpair_type;

public:

	typedef typename std::bidirectional_iterator_tag				iterator_category;
	typedef typename iterator_traits<rpair_type *>::value_type		value_type;
	typedef typename iterator_traits<rpair_type *>::difference_type	difference_type;
	typedef typename iterator_traits<rpair_type *>::pointer			pointer;
	typedef typename iterator_traits<rpair_type *>::reference		reference;

private:
	typedef typename ft::remove_const<rKeyType>::type	KeyType;
	typedef typename ft::remove_const<rT>::type			T;

	typedef AVLTree<rKeyType, rT>*				tree_type;
	typedef AVLTNode<rKeyType, rT>*				iterator_type;

protected:
	iterator_type	c_node;
	tree_type		tree;

public:
	TreeIt() : c_node(), tree() {}
	TreeIt( AVLTNode<KeyType, T>* x, const AVLTree<KeyType, T>* tree )
	{
		this->c_node = reinterpret_cast<AVLTNode<rKeyType, rT>*>(x);
		this->tree = const_cast<AVLTree<rKeyType, rT>*>(reinterpret_cast<const AVLTree<rKeyType, rT>*>(tree));
	}
	~TreeIt( void ) {}
	

	TreeIt(const TreeIt<KeyType, T>& src)
	{
		typedef AVLTree<KeyType, T>*	src_tree_type;
		typedef AVLTNode<KeyType, T>*	src_it_type;

		pair<src_it_type, src_tree_type>	src_in = src.get();

		this->c_node = reinterpret_cast<iterator_type>(src_in.first);
		this->tree = reinterpret_cast<tree_type>(src_in.second);
	}

	pair<iterator_type, tree_type>	get() const
	{
		pair<iterator_type, tree_type>	res;

		res.first = this->c_node;
		res.second = this->tree;
		return (res);
	}

	TreeIt& operator=( const TreeIt<KeyType, T>& other )
	{
		typedef AVLTree<KeyType, T>*	src_tree_type;
		typedef AVLTNode<KeyType, T>*	src_it_type;

		pair<src_it_type, src_tree_type>	src_in = other.get();

		this->c_node = reinterpret_cast<iterator_type>(src_in.first);
		this->tree = reinterpret_cast<tree_type>(src_in.second);
		return (*this);
	}

	reference operator*() const
	{
		return (this->c_node->pair);
	}
	pointer operator->() const
	{
		return (std::addressof(operator*()));
	}

	TreeIt& operator++()
	{
		this->c_node = this->tree->next(this->c_node);
		return (*this);
	}
	TreeIt& operator--()
	{
		this->c_node = this->tree->prev(this->c_node);
		return (*this);
	}
	TreeIt operator++( int )
	{
		TreeIt<rKeyType, rT>	tmp(*this);
		
		this->c_node = this->tree->next(this->c_node);
		return (tmp);
	}
	TreeIt operator--( int )
	{
		TreeIt<rKeyType, rT>	tmp(*this);

		this->c_node = this->tree->prev(this->c_node);
		return (tmp);
	}
};

template< class Key1, class T1, class Key2, class T2 >
bool operator==( const TreeIt<Key1, T1>& lhs,
                 const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) == &(*rhs) ? true : false);
}

template< class Key1, class T1, class Key2, class T2 >
bool operator!=( const TreeIt<Key1, T1>& lhs,
                 const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) != &(*rhs) ? true : false);
}

template< class Key1, class T1, class Key2, class T2 >
bool operator<( const TreeIt<Key1, T1>& lhs,
                const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) < &(*rhs) ? true : false);
}

template< class Key1, class T1, class Key2, class T2 >
bool operator<=( const TreeIt<Key1, T1>& lhs,
                 const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) <= &(*rhs) ? true : false);
}

template< class Key1, class T1, class Key2, class T2 >
bool operator>( const TreeIt<Key1, T1>& lhs,
                const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) > &(*rhs) ? true : false);
}

template< class Key1, class T1, class Key2, class T2 >
bool operator>=( const TreeIt<Key1, T1>& lhs,
                 const TreeIt<Key2, T2>& rhs )
{
	return (&(*lhs) >= &(*rhs) ? true : false);
}

};

#endif