 
#pragma once
#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "ft_lib.hpp"

namespace ft {

template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RBNode {
public:
	typedef Allocator                               		allocator_type;
	typedef Compare											key_compare;
	typedef typename allocator_type::value_type       		value_type;
	typedef typename allocator_type::size_type      		size_type;
	typedef typename allocator_type::difference_type		difference_type;
	typedef typename allocator_type::reference      		reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer        		pointer;
	typedef typename allocator_type::const_pointer			const_pointer;

private:
	allocator_type	_alloc;
	key_compare comp_;
public:
	T data;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	RBNode* sentinel;
	bool red;

	RBNode()
	{
		_alloc.construct(&data);
		left = NULL;
		right = NULL;
		parent = NULL;
		sentinel = NULL;
		red = true;
	}

	RBNode(const T & data): data(data)
	{
		// this->data = data;
		left = NULL;
		right = NULL;
		parent = NULL;
		sentinel = NULL;
		red = true;
	}

	RBNode( const RBNode& rhs )
	{
		*this = rhs;
	}

	~RBNode()
	{
		_alloc.destroy(&data);
	}

	RBNode& operator=( const RBNode& rhs )
	{
		data = rhs.data;
		left = rhs.left;
		right = rhs.right;
		parent = rhs.parent;
		sentinel = rhs.sentinel;
		red = rhs.red;
		return *this;
	}

	RBNode* next( void )
	{
		RBNode* save;

		// if (this == this->sentinel->right) // sentinel's right is the max
		// 	return this->sentinel->parent;
		// else if (this == this->sentinel->parent) // sentinel's parent is the end
		// 	return this;
		// else
		// {
			// if you have a right child, return right child
			if (this->right && this->right->parent == this)
			{
				return this->right;
			}
			else
			{
				// while you are a right child, iterate on the parent
				save = this;
				while (save->parent && save->parent->right == save)
					save = save->parent;
				return save->parent;
			}
		// }
		
	}

	RBNode* prev( void )
	{
		RBNode* save;

		if (this == this->sentinel->left) // sentinel's left is the max
			return this->sentinel->parent;
		else if (this == this->sentinel->parent) // sentinel's parent is the end
			return this;
		else
		{
			// if you have a left child, return left child
			if (this->left && this->left->parent == this)
			{
				return this->left;
			}
			else
			{
				// while you are a left child, iterate on the parent
				save = this;
				while (save->parent && save->parent->left == save)
					save = save->parent;
				return save->parent;
			}
		}
	}
};

template< class T, class Compare, class Alloc >
bool operator==( const ft::RBNode<T, Compare, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return (!comp_(lhs.data, rhs.data) && !comp_(rhs.data, lhs.data)); }

// template< class T, class Compare, class Alloc >
// bool operator==( const ft::RBNode<T, Compare, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
// { return (lhs.data == rhs.data); }

template< class T, class Compare, class Alloc >
bool operator<( const ft::RBNode<T, Compare, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return (comp_(lhs.data, rhs.data)); }

template< class T, class Compare, class Alloc >
bool operator!=( const ft::RBNode<T, Compare, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return !(lhs == rhs); }

template< class T, class Compare, class Alloc >
bool operator>( const ft::RBNode<T, Compare, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return !(lhs < rhs) && lhs != rhs; }

template< class T, class Compare, Compare, class Alloc >
bool operator>=( const ft::RBNode<T, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return !(lhs < rhs); }

template< class T, class Compare, Compare, class Alloc >
bool operator<=( const ft::RBNode<T, Alloc>& lhs, const ft::RBNode<T, Compare, Alloc>& rhs )
{ return !(lhs > rhs); }

template< class T >
std::ostream & operator<<( std::ostream & os, const ft::RBNode<T>& rhs ) 
{ 
	os << rhs.data;
	return os;
}

}

#endif
