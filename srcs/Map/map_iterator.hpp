/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/15 16:53:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "rb_tree.hpp"

namespace ft
{

template <class M>
class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename M::value_type
							,typename M::pointer, typename M::reference, typename M::difference_type>
{
public:
	typedef typename M::value_type						value_type;
	typedef typename M::pointer							pointer;
	typedef typename M::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename M::difference_type 				difference_type;
	typedef typename M::size_type						size_type;
	typedef typename rb_tree<value_type>::node			node_type;
	typedef typename rb_tree<value_type>::node*			node_pointer;

protected:
	node_pointer	_node;

public:
	map_iterator<M>() : _node(node_type()) {  };

	map_iterator<M>(const map_iterator<M>& it) { *this = it; };

	template <class T>
	map_iterator<M>( const map_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ this->_node = it.base(); }
	
	~map_iterator<M>() {  };

	map_iterator<M>& operator=( const map_iterator<M>& it )
	{
		this->_node = it.base();
		return *this;
	}

	pointer		base() const			{ return &this->_node->key; };
	reference	operator*() const		{ return *base(); };
	pointer		operator->() const		{ return base(); };

	map_iterator<M>& operator++()
	{ 
		_increment();
		return *this;
	};

	map_iterator<M>& operator--()
	{ 
		_decrement();
		return *this;
	};
	
	map_iterator<M> operator++( int )
	{
		map_iterator<M> ori = *this;
		++(*this);
		return ori;
	};

	map_iterator<M> operator--( int )
	{
		map_iterator<M> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const map_iterator<M>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const map_iterator<M>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const map_iterator<T>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const map_iterator<T>& it) const { return (!operator==(it)); };
	// end const

protected:

	void _increment( void )
	{
		node_pointer	temp;

		// If there is a right, get the left-most element from the right node
		if (_node->right && !_node->right->is_empty())
		{
			temp = _node->right;
			while (temp->left && !temp->left->is_empty())
				temp = temp->left;
			_node = temp;
		}
		else 
		{
			temp = _node->parent;
			// Get parent as long as node is a right node
			while (_node == temp->right && !temp->right->is_empty())
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

		if (!_node->left->is_empty())
		{
			_node = _node->left;
			while (!_node->right->is_empty())
				_node = _node->right;
		}
		else // Get parent as long as node is a left node
		{
			parent = _node->parent;
			while (parent->left == _node)
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
