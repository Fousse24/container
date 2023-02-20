 
#pragma once
#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>

#include "rbtree_iterator.hpp"
#include "rbnode.hpp"
#include "pair.hpp"

using std::cout;
using std::string;
using std::endl;
using std::setw;

/*
 * ATTRIBUTES
 *
 * CONSTRUCTORS
 *
 * PRIVATE FUNCTIONS
 *		_createNode
 *		_setRoot
 *		_deleteRoot
 *		_insertRight
 *		_insertLeft
 *		_rotateRight
 *		_rotateLeft
 *		_unlinkFromParent
 *		_insert
 *		_rbInsertFix
 *		_delete
 *		_rbDeleteFix
 *		_deleteLeaf
 *		_transplantData
 *		_recolor
 *		_swapColor
 *		_giveParent
 *		_getFarNiece
 *		_getCloseNiece
 *		_getSibling
 *
 * PUBLIC FUNCTIONS
 *		getRoot
 *		insert
 *		erase
 *		findNode
 *		inorderPre
 *		inorderSucc
 *		isNil
 *		min
 *		max
 *		begin
 *		end
 *		getHeight
 *		printTree
 *		printSuccessor
 *		printPredecessor
 *		printLevel
 *		displayLevel
 */

namespace ft {

template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class rbtree {

public:
	typedef Allocator                               	allocator_type;
	typedef Compare										key_compare;
	typedef T											value_type;
	typedef typename allocator_type::reference      	reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer        	pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type      	size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef ft::RBNode<T, key_compare, allocator_type>				Node;
	typedef typename allocator_type::template rebind<Node>::other 	node_allocator;

	typedef ft::rbtree_iterator<Node> 					iterator;
	typedef ft::rbtree_const_iterator<Node>				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	

/* ATTRIBUTES */
private:
	node_allocator	_alloc;
	Node*			_root;
	Node*			_end;
	Node*			_NIL;
	key_compare		_comp;
	size_type		_size;

/*************************************************/


/* CONSTRUCTORS & DESTRUCTOR */
public:
	rbtree() : _comp(key_compare())
	{
		_size = 0;
		_alloc = node_allocator();
		_end = _createNode(false);
		_NIL = _createNode(false);
		_setRoot(_end);
	}

	~rbtree()
	{
		_deleteTree(_root);
		_destroyNode(_end);
		_destroyNode(_NIL);
		// delete _end;
		// delete _NIL;
	}

/*************************************************/


/* PRIVATE FUNCTIONS */
private:
	Node* _createNode(const T & data, bool red)
	{
		Node* node;
		node = _alloc.allocate(1);
		_alloc.construct(node, Node(data));
		// node->change_data(data);
		// _alloc.construct(node, Node(data));
		// Node* node = new Node(data);
		// node->data = 
		node->left = _NIL;
		node->right = _NIL;
		node->red = red;
		return node;
	}

	Node* _createNode(bool red)
	{
		Node* node;
		node = _alloc.allocate(1);
		_alloc.construct(node, Node());
		// Node* node = new Node();
		node->left = _NIL;
		node->right = _NIL;
		node->red = red;
		return node;
	}

	void _destroyNode(Node * node)
	{
		try
		{
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
		catch(const std::bad_alloc & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void _setRoot( Node* node )
	{
		_root = node;
		if (_root)
		{
			_end->left = _root;
			_root->parent = _end;
			_root->red = false;
		}
	}

	void _deleteRoot(  )
	{
		_destroyNode(_root);
		// delete _root;
		_end->left = _end;
	}

	void _deleteTree(Node* root)
	{
		if (isNil(root))
			return;
		if (!isNil(root->right))
			_deleteTree(root->right);
		if (!isNil(root->left))
			_deleteTree(root->left);
		_destroyNode(root);
		// delete root;
	}

	void _insertRight( Node* parent, Node* child)
	{
		if (isNil(parent) || isNil(child))
			return;

		_size++;
		parent->right = child;
		child->parent = parent;
	}

	void _insertLeft( Node* parent, Node* child)
	{
		if (isNil(parent) || isNil(child))
			return;

		_size++;
		parent->left = child;
		child->parent = parent;
	}

	void _rotateRight( Node* node )
	{
		Node* child;

		child = node->left;
		if (node == _root)
			_setRoot(child);
		else
			_giveParent(node, child);

		node->parent = child;
		node->left = child->right;
		node->left->parent = node;
		child->right = node;
	}

	void _rotateLeft( Node* node )
	{
		Node* child;

		child = node->right;
		if (node == _root)
			_setRoot(child);
		else
			_giveParent(node, child);

		node->parent = child;
		node->right = child->left;
		node->right->parent = node;
		child->left = node;
	}

	void _unlinkFromParent( Node* node )
	{
		if (isNil(node) || isNil(node->parent))
			return;

		if (node->parent->left == node)
			node->parent->left = _NIL;
		else if (node->parent->right == node)
			node->parent->right = _NIL;

		return;		
	}


	Node* _insert( Node* root, Node* node )
	{
		if (isNil(_root) || _root == _end) 
		{
			_setRoot(node);
			_size++;
			return node;
		}

		if (value_comp()(*node->data, *root->data))
		{
			if (isNil(root->left))
			{
				_insertLeft(root, node);
			}
			else
			{
				return _insert(root->left, node);
			}
		}
		else if (value_comp()(*root->data, *node->data))
		{
			if (isNil(root->right))
			{
				_insertRight(root, node);
			}
			else
			{
				return _insert(root->right, node);
			}
		}
		else
			return root;
		_rbInsertFix(node);
		return node;
	}

	void _rbInsertFix( Node* node )
	{
		Node* grandP = NULL;
		Node* aunt = NULL;
		Node* save = NULL;

		// Exit if parent is black
		if (isNil(node) || !node->parent->red)
		{
			return ;
		}
	
		if (!isNil(node->parent))
			grandP = node->parent->parent;
		aunt = _getSibling(node->parent);
		
		// aunt is nil or black
		if (isNil(aunt) || !aunt->red)
		{
			save = node->parent;
			if (node->parent == grandP->left)
			{
				// left right
				if (node->parent->right == node)
				{
					_rotateLeft(node->parent);
					save = node;
				}
				// left left
				_rotateRight(grandP);
			}
			else
			{
				// right left
				if (node->parent->left == node)
				{
					_rotateRight(node->parent);
					save = node;
				}
				// right right
				_rotateLeft(grandP);
			}
			_recolor(grandP);
			_recolor(save);
		}
		else
		{
			_recolor(node->parent);
			_recolor(aunt);
			if (!isNil(grandP) && grandP != _root)
			{
				_recolor(grandP);
				// Recheck with grand parent as critical node
				_rbInsertFix(grandP);
			}
		}
		_root->red = false;
	}

	// BST deletion, FIX if deleted node was black
	void _delete( Node* node )
	{
		Node* replacement = _NIL;

		if (isNil(node))
			return ;
 
		if (!isNil(node->right) || !isNil(node->left))
		{
			if (isNil(node->right) || isNil(node->left))
			{
				/* 1 child */
				if (isNil(node->right))
					replacement = node->left;
				else if (isNil(node->left))
					replacement = node->right;
				_swapPos(replacement, node);
				/**/
			}
			else
			{ 
				/* 2 children */
				replacement = inorderSucc(node);				
				_swapPos(replacement, node);
				/**/
			}
			return _delete(node);
		}

		/* 0 child */
		// If node to be deleted is red, we need to fix the rbtree
		if (!node->red)
			_rbDeleteFix(node);
		_deleteLeaf(node);
		_size--;
		return ;
		/**/
	}

	void _rbDeleteFix( Node* node )
	{	
		Node* sibling;
		Node* closeNiece;
		Node* farNiece;
		bool doubleBlack = false;

		if (!node->red)
		{
			/* DOUBLE BLACK */
			if (node == _root)
				return;
			
			sibling = _getSibling(node);
			if (!sibling->red)
			{
				if (!sibling->left->red && !sibling->right->red)
				{
					if (node->parent->red)
						_recolor(node->parent);
					else
						doubleBlack = true;

					_recolor(sibling);
					if (doubleBlack)
						return _rbDeleteFix(node->parent);
				}
				else
				{
					closeNiece = _getCloseNiece(node);
					farNiece = _getFarNiece(node);
					if (!farNiece->red && closeNiece->red)
					{
						_swapColor(sibling, closeNiece);
						if (node == node->parent->left)
							_rotateRight(sibling);
						else
							_rotateLeft(sibling);
						sibling = _getSibling(node);
						
					}

					farNiece = _getFarNiece(node);
					if (farNiece->red)
					{
						_swapColor(node->parent, sibling);
						if (node == node->parent->left)
							_rotateLeft(node->parent);
						else
							_rotateRight(node->parent);
						_recolor(farNiece);
					}
				}
			}
			else
			{
				_swapColor(node->parent, sibling);

				if (node == node->parent->left)
					_rotateLeft(node->parent);
				else
					_rotateRight(node->parent);

				return _rbDeleteFix(node);
			}
		}
		return ;
	}

	bool _deleteLeaf(Node* leaf)
	{
		bool wasRed = false;

		if (!isNil(leaf)) 
		{
			wasRed = leaf->red;
			_unlinkFromParent(leaf);
			if (_root == leaf)
				_root = _end;
			// delete leaf;
			_destroyNode(leaf);
		}
		return wasRed;	
	}

	void _fixTree( )
	{
		_NIL->parent = _end;
		_end->right = _NIL;
	}

	// Replace <dst>'s data with <src>'s
	Node* _transplantData( Node* src, Node* dst )
	{
		// TODO delete dst->data somehow

		dst->data = src->data;
		return dst;
	}

	void _swapParent( Node* node1, Node* node2 )
	{
		Node* save;

		save = node1->parent;
		node1->parent = node2->parent;
		if (!isNil(node1->parent))
		{
			if (node1->parent->left == node2)
				node1->parent->left = node1;
			else
				node1->parent->right = node1;
		}

		node2->parent = save;
		if (!isNil(node2->parent))
		{
			if (node2->parent->left == node1)
				node2->parent->left = node2;
			else
				node2->parent->right = node2;
		}
	}

	void _swapChildren( Node* node1, Node* node2 )
	{
		Node* save;

		save = node1->left;
		node1->left = node2->left;
		if (!isNil(node1->left))
			node1->left->parent = node1;

		node2->left = save;
		if (!isNil(node2->left))
			node2->left->parent = node2;

		save = node1->right;
		node1->right = node2->right;
		if (!isNil(node1->right))
			node1->right->parent = node1;
			
		node2->right = save;
		if (!isNil(node2->right))
			node2->right->parent = node2;
	}

	void _swapPos( Node* src, Node* dst )
	{
		_swapColor(src, dst);
		_swapParent(src, dst);
		_swapChildren(src, dst);

		if (dst == _root)
			_setRoot(src);
		else if (src == _root)
			_setRoot(dst);
		
	}

	Node* _swapData( Node* src, Node* dst )
	{

		// TODO delete dst->data somehow
		T* save;

		save = dst->data;
		dst->data = src->data;
		src->data = save;
		return dst;
	}

	void _recolor( Node* node )
	{
		if (isNil(node) || node == _root)
			return;
		node->red = !node->red;
	}

	void _swapColor( Node* node1, Node* node2)
	{
		bool tempRed;

		tempRed = node1->red;
		node1->red = node2->red;
		node2->red = tempRed;

	}

	// Orphan <current> and assign its parent to <newChild> (if not NIL)
	void _giveParent( Node* current, Node* newChild )
	{
		if (current->parent->left == current)
			current->parent->left = newChild;
		else if (current->parent->right == current)
			current->parent->right = newChild;
		else
			return;
		
		newChild->parent = current->parent;
	}

	Node* _getFarNiece( Node* node )
	{
		if (isNil(node))
			return _NIL;
		
		if (node == node->parent->left)
			return node->parent->right->right;
		else
			return node->parent->left->left;
	}

	Node* _getCloseNiece( Node* node )
	{
		if (isNil(node))
			return _NIL;
		
		if (node == node->parent->left)
			return node->parent->right->left;
		else
			return node->parent->left->right;
	}

	Node* _getSibling( Node* node )
	{
		// if (isNil(node) || isNil(node->parent))
		// {
		// 	return _NIL;
		// }
		if (node->parent->right == node)
		{
			return node->parent->left;
		}
		return node->parent->right;
	}

	Node* _getBoundBase( const T & data )
	{
		Node* 		node = _root;

		while (!isNil(node))
		{
			if (value_comp()(data, *node->data))
			{
				if (isNil(node->left))
					return node;
				node = node->left;
			}
				
			else if (value_comp()(*node->data, data))
			{
				if (isNil(node->right))
					return node;
				node = node->right;
			}
			else
				return node;
		}

		return _end;
	}

	Node* _getBoundBase( const T & data ) const
	{
		Node* 		node = _root;

		while (!isNil(node))
		{
			if (value_comp()(data, *node->data))
			{
				if (isNil(node->left))
					return node;
				node = node->left;
			}
				
			else if (value_comp()(*node->data, data))
			{
				if (isNil(node->right))
					return node;
				node = node->right;
			}
			else
				return node;
		}

		return _end;
	}

/*************************************************/


/* PUBLIC FUNCTIONS */
public:

	Node* getRoot( )
	{
		return _root;
	}

	Node* getRoot( ) const
	{
		return _root;
	}

	key_compare& value_comp()
    {
        return _comp;
    }

    const key_compare& value_comp() const
    {
        return _comp;
    }

	Node* findNode(Node* root, const T & data ) {
		if (isNil(root))
			return NULL;
		if (!value_comp()(*root->data, data) && !value_comp()(data, *root->data))
			return root;
		if (value_comp()(*root->data, data))
			return findNode(root->right, data);
		else
			return findNode(root->left, data);
	}

	template<class value>
	Node* findNode(Node* root, const value & data ) {
		if (isNil(root))
			return NULL;
		if (value_comp()(*root->data, data))
			return findNode(root->right, data);
		else if (value_comp()(data, *root->data))
			return findNode(root->left, data);
		else
			return root;
	}

	Node* findNode(Node* root, const T & data ) const {
		if (isNil(root))
			return NULL;
		if (!value_comp()(*root->data, data) && !value_comp()(data, *root->data))
			return root;
		if (value_comp()(*root->data, data))
			return findNode(root->right, data);
		else
			return findNode(root->left, data);
	}

	template<class value>
	Node* findNode(Node* root, const value & data ) const {
		if (isNil(root))
			return NULL;
		if (value_comp()(*root->data, data))
			return findNode(root->right, data);
		else if (value_comp()(data, *root->data))
			return findNode(root->left, data);
		else
			return root;
	}
	

	// TODO
	Node* inorderPre( Node* node )
	{
		Node* save;

		if (node->left && node->left->parent == node)
		{
			save = node->left;
			while (save->right && save->right->parent == save)
				save = save->left;
			return save;
		}
		else
		{
			// while you are a left child, iterate on the parent
			save = node;
			while (save->parent && save->parent->left == save)
				save = save->parent;
			return save->parent;
		}
	}

	Node* inorderSucc( Node* node )
	{
		Node* save;

		if (node->right && node->right->parent == node)
		{
			save = node->right;
			while (save->left && save->left->parent == save)
				save = save->left;
			return save;
		}
		else
		{
			// while you are a right child, iterate on the parent
			save = node;
			while (save->parent && save->parent->right == save)
				save = save->parent;
			return save->parent;
		}
	}

	Node* inorderPre( Node* node ) const
	{
		Node* save;

		if (node->left && node->left->parent == node)
		{
			save = node->left;
			while (save->right && save->right->parent == save)
				save = save->left;
			return save;
		}
		else
		{
			// while you are a left child, iterate on the parent
			save = node;
			while (save->parent && save->parent->left == save)
				save = save->parent;
			return save->parent;
		}
	}

	Node* inorderSucc( Node* node ) const
	{
		Node* save;

		if (node->right && node->right->parent == node)
		{
			save = node->right;
			while (save->left && save->left->parent == save)
				save = save->left;
			return save;
		}
		else
		{
			// while you are a right child, iterate on the parent
			save = node;
			while (save->parent && save->parent->right == save)
				save = save->parent;
			return save->parent;
		}
	}

	bool isNil( const Node* node ) const
	{
		if (node == NULL || node == _NIL || node == _end)
			return true;
		return false;
	}

	Node* min( Node* root)
	{
		while (!isNil(root) && !isNil(root->left))
		{
			root = root->left;
		}
		return root;
	}

	Node* min( Node* root) const
	{
		while (!isNil(root) && !isNil(root->left))
		{
			root = root->left;
		}
		return root;
	}

	Node* max( Node* root)
	{
		while (!isNil(root) && !isNil(root->right))
		{
			root = root->right;
		}
		return root;
	}

	Node* max( Node* root) const
	{
		while (!isNil(root) && !isNil(root->right))
		{
			root = root->right;
		}
		return root;
	}

	allocator_type get_allocator() const { return Allocator(); }
	
	// iterator	
	iterator		begin()			{ return iterator(min(_root)); }
	const_iterator	begin() const	{ return const_iterator(min(_root)); }

	iterator		end() 			{ return iterator(_end); }
	const_iterator	end() const 	{ return const_iterator(_end);}
	
	reverse_iterator       rbegin()			{ return reverse_iterator(max(_root)); }
	const_reverse_iterator rbegin() const 	{ return const_reverse_iterator(max(_root)); }
	reverse_iterator       rend() 			{ return reverse_iterator(_end); }
	const_reverse_iterator rend() const 	{ return const_reverse_iterator(_end); }
	// iterator end

	/* Capacity */
	bool 		empty() const	{ return (_size <= 0 ? true : false); }
	size_type	size() const { return _size; }
	size_type	max_size() const { return std::min(TO_SIZE(std::numeric_limits<difference_type>::max()), _alloc.max_size()) ; }

	/* Capacity end */


	/* Modifier */
	void clear()
	{
		Node*		save;
		iterator	end_ = end();
		iterator	begin_ = begin();
		
		if (begin_ == end_)
			return ;

		for (; begin_ != end_;)
		{
			save = begin_.get_node();
			begin_++;
			erase(save);
			// delete (save);
		}
		_setRoot(_end);
		_size = 0;
	}

	ft::pair<iterator, bool> insert( const T & data )
	{
		Node* node = _createNode(data, true);
		Node* save;
		
		save = node;
		node = _insert(_root, node);
		if (save != node)
		{
			// delete save;
			_destroyNode(save);
			return ft::make_pair(iterator(node), false);
		}
			
		_fixTree();
		return ft::make_pair(iterator(node), true);
	}

	ft::pair<iterator, bool> erase( const T & data )
	{
		Node* node = findNode(_root, data);
		return erase(node);
	}

	ft::pair<iterator, bool> erase( Node* node )
	{
		ft::pair<iterator, bool> result;
		
		if (isNil(node))
			return ft::make_pair(end(), false);

		result = ft::make_pair(inorderSucc(node), true);
		_delete(node);
		_fixTree();
		return result;
	}

	void swap(rbtree & other)
	{
		Node*		save_end;
		Node*		save_nil;
		Node*		save_root;
		size_type	save_size;

		save_end = other._end;
		save_nil = other._NIL;
		save_root = other.getRoot();
		save_size = other.size();

		other._end = _end;
		other._NIL = _NIL;
		other._setRoot(getRoot());
		other._size = _size;

		_end = save_end;
		_NIL = save_nil;
		_setRoot(save_root);
		_size = save_size;
		
	}

	size_type count( const T & data )
	{
		if (find(data) != end())
			return 1;
		return 0;
	}


	iterator find( const T & data )
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
			return end();
		return iterator(node);
	}

	const_iterator find( const T & data ) const 
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
			return end();
		return const_iterator(node);
	}

	ft::pair<iterator, iterator> equal_range( const T & data ) 
	{
		Node*		node;
		iterator	lower;
		iterator	upper;

		node = _getBoundBase(data);

		if (isNil(node))
			return ft::make_pair<iterator, iterator>(end(), end());
		else
		{
			if (!value_comp()(data, *node->data) && !value_comp()(data, *node->data))
				upper = iterator(inorderSucc(node));
			else
				upper = iterator(node);

			if (value_comp()(*node->data, data))
				lower = iterator(inorderSucc(node));
			else
				lower = iterator(node);

		}
		return ft::make_pair<iterator, iterator>(lower, upper);		
	}

	ft::pair<const_iterator, const_iterator> equal_range( const T & data ) const
	{
		Node*		node;
		const_iterator	lower;
		const_iterator	upper;

		node = _getBoundBase(data);

		if (isNil(node))
			return ft::make_pair<const_iterator, const_iterator>(end(), end());
		else
		{
			if (!value_comp()(data, *node->data) && !value_comp()(data, *node->data))
				upper = const_iterator(inorderSucc(node));
			else
				upper = const_iterator(node);

			if (value_comp()(*node->data, data))
				lower = const_iterator(inorderSucc(node));
			else
				lower = const_iterator(node);

		}
		return ft::make_pair<const_iterator, const_iterator>(lower, upper);		
	}

	iterator lower_bound( const T & data ) 
	{
		Node* 		node = _getBoundBase(data);

		if (value_comp()(*node->data, data))
			return iterator(inorderSucc(node));
		return iterator(_getBoundBase(data));			
	}

	const_iterator lower_bound( const T & data ) const 
	{
		Node* 		node = _getBoundBase(data);

		if (value_comp()(*node->data, data))
			return const_iterator(inorderSucc(node));
		return const_iterator(_getBoundBase(data));
	}

	iterator upper_bound( const T & data ) 
	{
		Node* 		node = _getBoundBase(data);
		
		// if it's equal, return successor
		if (!value_comp()(data, *node->data) && !value_comp()(data, *node->data))
			return iterator(inorderSucc(node));
		return iterator(node);
	}

	const_iterator upper_bound( const T & data ) const 
	{
		Node* 		node = _getBoundBase(data);
		
		// if it's equal, return successor
		if (!value_comp()(data, *node->data) && !value_comp()(data, *node->data))
			return const_iterator(inorderSucc(node));
		return const_iterator(node);		
	}

	// iterator insert( iterator, const value_type& value ) // WARNING
	// {
	// 	return (insert(value).first);
	
	// }

	// template<class Iter>
	// void insert(Iter first, Iter last) // change to input only
	// {
	// 	while (first != last)
	// 	{
	// 		insert(*first);
	// 		++first;
	// 	}
	// 	return ;
	// }
	
	// void erase(iterator pos)
	// {
	// 	erase((*pos).first);
	// }

	// size_type	erase(const key_type& key)
	// {
	// 	int	deleted;

	// 	deleted = _tree.deleteNode(ft::make_pair(key, mapped_type()));
	// 	_size -= deleted;
	// 	return (size_type)deleted;
	// }

	// void erase(iterator first, iterator last)
	// {
	// 	while (first != last)
	// 	{
	// 		erase((*first).first);
	// 		++first;
	// 	}
	// }

	

	void printTree()
	{
		// Node*	node;
		cout << "Printing tree in order" << endl;
		// node = _sentinel->left;
		// while (!isNil(node))
		// {
		// 	cout << *node->data << endl;
		// 	node = inorderSucc(node);
		// }

		iterator	it;
		for(it = this->begin(); it != this->end(); it++)
			cout << *it << endl;
	}

	void printSuccessor( value_type & data )
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
		{
			cout << "Couldn't find node of data " << data << endl;
		}
		else
		{
			node = inorderSucc(node);
			if (node == _end)
			{
				cout << "Successor is the end" << endl;
			}
			else
			{
				cout << "Successor is node " << *node->data << endl;
			}
		}
	}

	void printPredecessor( value_type & data )
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
		{
			cout << "Couldn't find node of data " << data << endl;
		}
		else
		{
			node = inorderPre(node);
			if (node == _end)
			{
				cout << "Predecessor is the end" << endl;
			}
			else
			{
				cout << "Predecessor is node " << *node->data << endl;
			}
		}
	}

	/*************************************************/

};

template< class T, class Compare, class Alloc >
bool operator==( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class T, class Compare, class Alloc >
bool operator!=( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>& rhs)
{ return !(lhs == rhs); }

template< class T, class Compare, class Alloc >
bool operator>( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>&rhs)
{ return !(lhs < rhs) && lhs != rhs; }

template< class T, class Compare, class Alloc >
bool operator<( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>&rhs)
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class T, class Compare, class Alloc >
bool operator>=( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>&rhs)
{ return !(lhs < rhs); }

template< class T, class Compare, class Alloc >
bool operator<=( const ft::rbtree<T, Compare, Alloc>& lhs, const ft::rbtree<T, Compare, Alloc>&rhs)
{ return !(lhs > rhs); }

template< class T, class Compare, class Alloc >
void swap(ft::rbtree<T, Compare, Alloc> & lhs, ft::rbtree<T, Compare, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}

}  

// template< class T, class Alloc>
// void swap(vector<T, Alloc> & lhs, vector<T, Alloc> & rhs)
// 	{
// 		lhs.swap(rhs);
// 	}
// }  // std


#endif
