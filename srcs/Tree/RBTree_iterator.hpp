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

#ifndef RBTree_iterator_HPP
#define RBTree_iterator_HPP

#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "rbnode.hpp"

namespace ft
{

template <class N>
class RBTree_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename N::value_type
							,typename N::pointer, typename N::reference, typename N::difference_type>
{
public:
	typedef typename N::value_type						value_type;
	typedef typename N::pointer							pointer;
	typedef typename N::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename N::difference_type 				difference_type;
	typedef typename N::size_type						size_type;
	// typedef typename N::value_compare					key_compare;
	
	typedef N*			node_pointer;
	typedef const N*	const_node_pointer;

protected:
	

public:
	node_pointer	_node;

	RBTree_iterator() : _node(node_pointer()) {  };

	RBTree_iterator( node_pointer n ) { _node = n; };

	RBTree_iterator( const_node_pointer n ) { _node = n; };

	RBTree_iterator(const RBTree_iterator<N>& it) { *this = it; };

	template <class T>
	RBTree_iterator( const RBTree_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const N>, bool>::type = 0) 
	{ 
		// TODO ?
		*this = it;
		// this->_node = it.get_node(); 
	};

	~RBTree_iterator() {  };

	RBTree_iterator& operator=( const RBTree_iterator<N>& it )
	{
		this->_node = it._node;
		return *this;
	}

	pointer			base() const			{ return &_node->data; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };

	RBTree_iterator<N>& operator++()
	{ 
		_node = _node->next();	
		// _increment();
		return *this;
	};

	RBTree_iterator<N>& operator--()
	{ 
		_node = _node->prev();
		// _decrement();
		return *this;
	};
	
	RBTree_iterator<N> operator++( int )
	{
		RBTree_iterator<N> ori = *this;
		++(*this);
		return ori;
	};

	RBTree_iterator<N> operator--( int )
	{
		RBTree_iterator<N> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const RBTree_iterator<N>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const RBTree_iterator<N>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const RBTree_iterator<T>& it) const
	{
		if (_node == it._node) // TODO
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const RBTree_iterator<T>& it) const { return (!operator==(it)); };
	// end const

protected:

	// void _increment( void )
	// {
	// 	_node = _node->next();		
	// }

	// void _decrement( void )
	// {
	// 	_node = _node->prev();
	// }
};

template <class N>
class RBTree_const_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename N::value_type
							,typename N::pointer, typename N::reference, typename N::difference_type>
{
public:
	typedef typename N::value_type						value_type;
	typedef typename N::pointer							pointer;
	typedef typename N::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename N::difference_type 				difference_type;
	typedef typename N::size_type						size_type;
	// typedef typename N::value_compare					key_compare;
	
	typedef N*			node_pointer;
	typedef const N*	const_node_pointer;

protected:
	node_pointer	_node;

public:
	RBTree_const_iterator() : _node(node_pointer()) {  };

	RBTree_const_iterator( node_pointer n ) { _node = n; };

	RBTree_const_iterator( const_node_pointer n ) { _node = n; };

	RBTree_const_iterator(const RBTree_const_iterator<N>& it) { *this = it; };

	template <class T>
	RBTree_const_iterator( const RBTree_const_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const N>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = it->get_node(); 
	};

	~RBTree_const_iterator() {  };

	RBTree_const_iterator& operator=( const RBTree_const_iterator<N>& it )
	{
		this->_node = it._node;
		return *this;
	}

	pointer			base() const			{ return &_node->data; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };


	RBTree_const_iterator<N>& operator++()
	{ 
		_node = _node->next();	
		// _increment();
		return *this;
	};

	RBTree_const_iterator<N>& operator--()
	{ 
		_node = _node->prev();
		// _decrement();
		return *this;
	};
	
	RBTree_const_iterator<N> operator++( int )
	{
		RBTree_const_iterator<N> ori = *this;
		++(*this);
		return ori;
	};

	RBTree_const_iterator<N> operator--( int )
	{
		RBTree_const_iterator<N> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const RBTree_const_iterator<N>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const RBTree_const_iterator<N>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const RBTree_const_iterator<N>& it) const
	{
		if (_node == it._node) // TODO
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const RBTree_const_iterator<N>& it) const { return (!operator==(it)); };
	// end const

protected:

	// void _increment( void )
	// {
	// 	_node = _node->next();		
	// }

	// void _decrement( void )
	// {
	// 	_node = _node->prev();
	// }
};

}
#endif
