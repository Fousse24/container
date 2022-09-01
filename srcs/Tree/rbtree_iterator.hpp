/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/15 16:53:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "rbtree.hpp"

namespace ft
{

template <class M>
class rbtree_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename M::value_type
							,typename M::pointer, typename M::reference, typename M::difference_type>
{
public:
	typedef typename M::value_type						value_type;
	typedef typename M::pointer							pointer;
	typedef typename M::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename M::difference_type 				difference_type;
	typedef typename M::size_type						size_type;
	
	typedef rbtree<value_type>			t_rbtree;
	typedef typename t_rbtree::node		node_type;
	typedef typename t_rbtree::node*	node_pointer;

protected:
	t_rbtree*		rbtree;
	node_pointer	_node;

public:
	rbtree_iterator<M>() : rbtree(NULL), _node(node_pointer()) {  };

	rbtree_iterator<M>( t_rbtree* t) { rbtree = t; };
	rbtree_iterator<M>( t_rbtree* t, node_pointer n ) { rbtree = t; _node = n; };

	rbtree_iterator<M>(const rbtree_iterator<M>& it) { *this = it; };

	template <class T>
	rbtree_iterator<M>( const rbtree_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		this->_node = it.get_node(); 
		this->rbtree = it.rbtree;
	}
	
	~rbtree_iterator<M>() {  };

	rbtree_iterator<M>& operator=( const rbtree_iterator<M>& it )
	{
		this->_node = it._node;
		this->rbtree = it.rbtree;
		return *this;
	}

	pointer			base() const			{ return &_node->key; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };

	rbtree_iterator	begin(t_rbtree* t)
	{
		rbtree = t;
		_node = t->min(t->getRoot());
		return (*this);
	}

	rbtree_iterator	end(t_rbtree* t)
	{
		rbtree = t;
		_node = t->getEnd();
		return (*this);
	}

	rbtree_iterator<M>& operator++()
	{ 
		_increment();
		return *this;
	};

	rbtree_iterator<M>& operator--()
	{ 
		_decrement();
		return *this;
	};
	
	rbtree_iterator<M> operator++( int )
	{
		rbtree_iterator<M> ori = *this;
		++(*this);
		return ori;
	};

	rbtree_iterator<M> operator--( int )
	{
		rbtree_iterator<M> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const rbtree_iterator<M>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const rbtree_iterator<M>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const rbtree_iterator<T>& it) const
	{
		// if (_node == it._node) // WARNING
		// 	return true;  
		return false;
	};
	template <class T>
	bool operator!=(const rbtree_iterator<T>& it) const { return (!operator==(it)); };
	// end const

protected:

	void _increment( void )
	{
		node_pointer	temp;

		if (rbtree->is_end(_node))
		{
			std::cout << "this is the end for you!!" << std::endl;
			return ;
		}
		// If there is a right, get the left-most element from the right node
		if (_node->right && !rbtree->is_empty(_node->right))
		{
			_node = rbtree->min(_node->right);
			// temp = _node->right;
			// while (temp->left && !rbtree->is_empty(temp->left))
			// 	temp = temp->left;
			// _node = temp;
		}
		else 
		{
			temp = _node->parent;
			if (!temp)
				return;
			// Get parent as long as node is a right node
			while (temp && _node != temp->left)
			{
				_node = temp;
				temp = temp->parent;
			}
			if (_node != temp)
				_node = temp;
		}
	}

	void _decrement( void ) // WARNING missing something..?
	{
		node_pointer parent;

		if (rbtree->is_end(_node))
		{
			_node = rbtree->max(_node->left);
			return ;
		}
		if (!rbtree->is_empty(_node->left))
		{
			_node = _node->left;
			while (!rbtree->is_empty(_node->right))
				_node = _node->right;
		}
		else // Get parent as long as node is a left node
		{
			parent = _node->parent;
			while (!rbtree->is_end(parent) && parent->left == _node) // forced segfault on begin()--
			{
				_node = parent;
				parent = parent->parent;
			}
			_node = parent;
		}
	}
};

}
#endif
