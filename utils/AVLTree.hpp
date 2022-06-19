#ifndef	AVLTREE_HPP
# define AVLTREE_HPP

#include <memory>
#include "../utils/utility.hpp"
#include "../utils/iterators/reverse_iterator.hpp"

template<class KeyType, class T>
struct  AVLTNode
{
	typedef ft::pair<KeyType, T>	node_type;

	size_t					height;
	node_type				pair;
	AVLTNode<KeyType, T>	*parent;
	AVLTNode<KeyType, T>	*left;
	AVLTNode<KeyType, T>	*right;

	AVLTNode(node_type pair = node_type()) : height(0), pair(pair), parent(0), left(0), right(0) {}

	AVLTNode(const AVLTNode &other) : height(other.height), pair(other.pair), parent(0), left(0), right(0) {}
	template <class U1, class U2>
	AVLTNode(const AVLTNode<U1, U2> &other) : height(other.height), pair(other.pair), parent(0), left(0), right(0) {}

	AVLTNode	&operator=(const AVLTNode &other)
	{
		this->pair = other.pair;
		this->height = other.height;
		this->parent = other.parent;
		this->left = other.left;
		this->right = other.right;
		return (*this);
	}
};


template<class Key, class T, class Comp = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class AVLTree
{
public:
	typedef Key								key_type;
	typedef T								value_type;
	typedef Comp							value_compare;
	typedef Alloc							allocator_type;
	typedef	AVLTNode<key_type, value_type>	TNode;
	typedef TNode*							node_pointer;
	typedef typename ft::pair<Key, T>		pair_type;

	typedef typename Alloc::template rebind<TNode>::other	allocator_node;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef std::ptrdiff_t									difference_type;
	typedef std::size_t										size_type;


public:
	allocator_node	node_alloc;
	size_type		size;
	size_type		max_size;
	node_pointer	root_alloc;
	node_pointer	root;
	node_pointer	_end;
	node_pointer	_begin;
	value_compare	compare;

private:
	size_t	height(TNode *cur)
	{
		return (cur ? cur->height : 0);
	}

	int	bFactor(TNode *cur)
	{
		return (this->height(cur->right) - this->height(cur->left));
	}

	void	fixHeight(TNode *cur)
	{
		size_t	hl = this->height(cur->left);
		size_t	hr = this->height(cur->right);

		if (hl > hr)
			cur->height = hl + 1;
		else
			cur->height = hr + 1;
	}

	TNode	*rotateRight(TNode *top)
	{
		TNode	*newTop = top->left;

		top->left = newTop->right;
		newTop->right = top;
		newTop->parent = top->parent;
		if (!top->parent)
			this->root = newTop;
		if (newTop->left)
			newTop->left->parent = newTop;
		if (newTop->right)
			newTop->right->parent = newTop;
		this->fixHeight(top);
		this->fixHeight(newTop);
		return (newTop);
	}

	TNode	*rotateLeft(TNode *top)
	{
		TNode	*newTop = top->right;

		top->right = newTop->left;
		newTop->left = top;
		newTop->parent = top->parent;
		if (!top->parent)
			this->root = newTop;
		if (newTop->left)
			newTop->left->parent = newTop;
		if (newTop->right)
			newTop->right->parent = newTop;
		this->fixHeight(top);
		this->fixHeight(newTop);
		return (newTop);
	}

	TNode	*rebalance(TNode *cur)
	{
		this->fixHeight(cur);
		if (this->bFactor(cur) == 2)
		{
			if (this->bFactor(cur->right) < 0)
				cur->right = this->rotateRight(cur->right);
			return (this->rotateLeft(cur));
		}
		else if (this->bFactor(cur) == -2)
		{
			if (this->bFactor(cur->left) > 0)
				cur->left = this->rotateLeft(cur->left);
			return (this->rotateRight(cur));
		}
		return (cur);
	}

	TNode	*findMin(TNode *cur) const
	{
		return (cur->left ? this->findMin(cur->left) : cur);
	}

	TNode	*findMax(TNode *cur) const
	{
		return (cur->right ? this->findMax(cur->right) : cur);
	}

	TNode	*findKey(TNode *cur, key_type key) const
	{
		if (!cur)
			return (0);
		return (key > cur->pair.first ? findKey(cur->right, key) : (key == cur->pair.first ? cur : findKey(cur->left, key)));
	}

	TNode	*removeMin(TNode *cur)
	{
		if (cur->left == 0)
			return (cur->right);
		cur->left = this->removeMin(cur->left);
		return (this->rebalance(cur));
	}

	TNode	*remove(TNode *cur, key_type key)
	{
		if (!cur)
			return (0);
		if (this->compare(key, cur->pair.first))
			cur->left = this->remove(cur->left, key);
		else if (this->compare(cur->pair.first, key))
			cur->right = this->remove(cur->right, key);
		else
		{
			TNode	*l = cur->left;
			TNode	*r = cur->right;
			TNode	*parent = cur->parent;

			this->node_alloc.destroy(cur);
			--this->size;
			if (!this->size)
			{
				this->root = 0;
				return (0);
			}
			if (!r)
			{
				if (l)
					l->parent = parent;
				return (l);
			}
			TNode	*min = this->findMin(r);
			if (!parent)
			{
				this->root = r;
				r->parent = 0;
			}
			min->right = this->removeMin(r);
			if (min->right)
				min->right->parent = min;
			min->left = l;
			if (l)
				l->parent = min;
			return (this->rebalance(min));
		}
		return (this->rebalance(cur));
	}

	node_pointer	insert(node_pointer cur, node_pointer newNode, node_pointer parent = 0)
	{
		if (!cur)
		{
			newNode->parent = parent;
			++(this->size);
			return (newNode);
		}
		if (this->compare(newNode->pair.first, cur->pair.first))
		{
			node_pointer	res = this->insert(cur->left, newNode, cur);
			if (res)
				cur->left = res;
			else
				return (0);
		}
		else if (this->compare(cur->pair.first, newNode->pair.first))
		{
			node_pointer	res = this->insert(cur->right, newNode, cur);
			if (res)
				cur->right = res;
			else
				return (0);
		}
		else
			return (0);
		return (this->rebalance(cur));
	}

	node_pointer	hint_insert(node_pointer cur, node_pointer newNode, node_pointer parent = 0)
	{
		return (this->insert(cur, newNode, parent));
	}

	void	clear(TNode *cur)
	{
		if (cur)
		{
			if (cur->left)
				clear(cur->left);
			if (cur->right)
				clear(cur->right);
			this->node_alloc.destroy(cur);
			cur = 0;
		}
	}

	ft::pair<node_pointer, node_pointer>	dup_nodes(node_pointer node_space, node_pointer src, node_pointer parent)
	{
		ft::pair<node_pointer, node_pointer>	res;		// новый нод + указатель на свободное место
		node_pointer							dest;

		if (!src)
		{
			res.first = 0;
			res.second = node_space;
			return (res);
		}
		this->node_alloc.construct(node_space, *src);
		dest = node_space;
		dest->parent = parent;
		res = dup_nodes(node_space + 1, src->left, dest);
		dest->left = res.first;
		node_space = res.second;
		res = dup_nodes(node_space, src->right, dest);
		dest->right = res.first;
		res.first = dest;
		return (res);
	}

	node_pointer	add_node(pair_type pair, node_pointer hint = 0)
	{
		if (this->size < this->max_size)
		{
			this->node_alloc.construct(this->root_alloc + this->size, pair);
			if (this->size)
			{
				node_pointer	res;

				if (hint)
				 	res = this->hint_insert(hint, this->root_alloc + this->size);
				else
					res = this->insert(this->root, this->root_alloc + this->size);
				if (!res)
					this->node_alloc.destroy(this->root + this->size);
				return (res);
			}
			else
				++(this->size);
			return (this->root);
		}
		else
		{
			node_pointer	new_alloc_root;
			new_alloc_root = this->node_alloc.allocate((1 + this->size) * 2);
			try
			{
				this->dup_nodes(new_alloc_root, this->root, 0);
			}
			catch(...)
			{
				this->clear(new_alloc_root);
				this->node_alloc.deallocate(new_alloc_root, (1 + this->size) * 2);
				throw;
			}
			this->clear(this->root);
			this->node_alloc.deallocate(this->root_alloc, this->max_size);
			this->root_alloc = new_alloc_root;
			this->root = new_alloc_root;
			while (this->root->parent)
			{
				this->root = this->root->parent;
			}
			this->max_size = (1 + this->size) * 2;
			this->node_alloc.construct(this->root_alloc + this->size, pair);
			if (this->size)
			{
				node_pointer	res;

				if (hint)
				 	res = this->hint_insert(hint, this->root_alloc + this->size);
				else
					res = this->insert(this->root, this->root_alloc + this->size);
				if (!res)
					this->node_alloc.destroy(this->root + this->size);
				return (res);
			}
			else
				++(this->size);
			return (this->root);
		}
	}

	void	dup_tree(const AVLTree &other)
	{
		node_pointer	new_alloc_root;

		new_alloc_root = this->node_alloc.allocate(other.max_size);
		try
		{
			this->dup_nodes(new_alloc_root, other.root, 0);
		}
		catch(...)
		{
			this->clear(new_alloc_root);
			this->node_alloc.deallocate(new_alloc_root, other.max_size);
			throw;
		}
		if (this->root_alloc)
			this->node_alloc.deallocate(this->root_alloc, this->max_size);
		this->root_alloc = new_alloc_root;
		this->root = new_alloc_root;
		while (this->root->parent)
			this->root = this->root->parent;
		this->max_size = other.max_size;
		this->size = other.size;
	}


public:
	AVLTree() : size(0), max_size(0), root_alloc(0), root(0), compare() {
		this->_begin = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_begin, pair_type());
		this->_end = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_end, pair_type());
	}

	AVLTree(const AVLTree<typename ft::remove_const<Key>::type, typename ft::remove_const<T>::type> &other) : compare() {
		this->_begin = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_begin, pair_type());
		this->_end = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_end, pair_type());
		this->root = 0;
		this->root_alloc = 0;
		this->size = 0;
		this->max_size = 0;
		if (other.size)
			this->dup_tree(other);
	}

	AVLTree(size_type max) : size(0), max_size(max), root_alloc(0), root(0), compare() {
		this->_begin = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_begin, pair_type());
		this->_end = this->node_alloc.allocate(1);
		this->node_alloc.construct(this->_end, pair_type());
		this->root_alloc = this->node_alloc.allocate(max);
	}

	~AVLTree()
	{
		if (this->root)
			clear();
		this->node_alloc.destroy(this->_begin);
		this->node_alloc.deallocate(this->_begin, 1);
		this->node_alloc.destroy(this->_end);
		this->node_alloc.deallocate(this->_end, 1);
		this->node_alloc.deallocate(this->root_alloc, this->max_size);
	}

	AVLTree& operator=( const AVLTree& other )
	{
		if (this->root)
			clear();
		if (other.size)
			this->dup_tree(other);
		return (*this);
	}

	void	clear()
	{
		clear(this->root);
		this->size = 0;
	}

	bool	findKey(key_type key) const
	{
		return (this->findKey(this->root, key) != 0);
	}

	node_pointer	find(key_type key) const
	{
		return (this->findKey(this->root, key));
	}

	node_pointer	findMin() const
	{
		return (this->findMin(this->root));
	}

	node_pointer	findMax() const
	{
		return (this->findMax(this->root));
	}

	size_type	remove(key_type key)
	{
		size_type	prev_size = this->size;

		remove(this->root, key);
		return (this->size != prev_size);
	}

	node_pointer	insert(pair_type pair, node_pointer hint = 0)
	{
		if (!this->root)
		{
			if (!this->max_size)
			{
				TNode	*newNode = node_alloc.allocate(1);
				node_alloc.construct(newNode, pair);
				this->root = newNode;
				this->root_alloc = newNode;
				this->size = 1;
				this->max_size = 1;
			}
			else
			{
				node_alloc.construct(this->root_alloc, pair);
				this->root = this->root_alloc;
				this->size = 1;
			}
			return (this->root);
		}
		else
			return (this->add_node(pair, hint));
	}

	TNode	*prev(TNode *cur) const
	{
		if (cur == this->_end)
			return (findMax(this->root));
		if (!cur || cur == this->_begin)
			return (this->_end);
		if (cur->left)
			return (this->findMax(cur->left));
		node_pointer	parent = cur->parent;
		for (; parent && this->compare(cur->pair.first, parent->pair.first);
			parent = parent->parent) {}
		if (!parent)
			return (this->_begin);
		return (parent);
	}

	TNode	*next(TNode *cur) const
	{
		if (cur == this->_begin)
			return (findMin(this->root));
		if (!cur || cur == this->_end)
			return (this->_begin);
		if (cur->right)
			return (this->findMin(cur->right));
		node_pointer	parent = cur->parent;
		for (; parent && this->compare(parent->pair.first, cur->pair.first);
			parent = parent->parent) {}
		if (!parent)
			return (this->_end);
		return (parent);
	}

	const TNode	&at(key_type key) const
	{
		TNode	*res = 0;

		if (this->root)
			res = this->findKey(this->root, key);
		if (!res)
			throw std::out_of_range("map: at: No such element exists");
		return (*res);
	}

	TNode	&at(key_type key)
	{
		TNode	*res = 0;

		if (this->root)
			res = this->findKey(this->root, key);
		if (!res)
			throw std::out_of_range("map: at: No such element exists");
		return (*res);
	}

	TNode	&operator[](key_type key)
	{
		TNode	*res;

		if (this->root)
		{
			res = this->findKey(this->root, key);
			if (!res)
			{
				res = this->insert(ft::make_pair(key, value_type()));
				return (*(this->findKey(this->root, key)));
			}
		}
		else
			res = this->insert(ft::make_pair(key, value_type()));
		return (*res);
	}

	size_type	get_size() const
	{
		return (this->size);
	}

	size_type	gmax_size() const
	{
		return (this->node_alloc.max_size());
	}

	node_pointer	get_end() const
	{
		return (this->_end);
	}

	node_pointer	get_begin() const
	{
		return (this->_begin);
	}
};

#endif