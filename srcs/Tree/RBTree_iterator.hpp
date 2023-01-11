/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                 :+:      :+:    :+:   */
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
#include "rbtree.hpp"

namespace ft
{

template <class M>
class RBTree_const_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename M::value_type
							,typename M::pointer, typename M::reference, typename M::difference_type>
{
public:
	typedef typename M::value_type						value_type;
	typedef typename M::pointer							pointer;
	typedef typename M::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename M::difference_type 				difference_type;
	typedef typename M::size_type						size_type;
	typedef typename M::value_compare					key_compare;
	
	typedef RBTree<value_type, key_compare>				rbtree_type;
	typedef RBTree<const value_type, key_compare>		const_rbtree_type;
	typedef typename rbtree_type::Node					node_type;
	typedef typename rbtree_type::Node*					node_pointer;
	typedef typename const_rbtree_type::Node			const_node_type;
	typedef typename const_rbtree_type::Node*			const_node_pointer;

protected:
	rbtree_type*	_rbtree;
	node_pointer	_node;

public:
	RBTree_const_iterator<M>() : _rbtree(NULL), _node(node_pointer()) {  };

	RBTree_const_iterator<M>( rbtree_type* t) { _rbtree = t; };
	RBTree_const_iterator<M>( rbtree_type* t, node_pointer n ) { _rbtree = t; _node = n; };

	RBTree_const_iterator<M>( const_rbtree_type* t, const_node_pointer n ) { _rbtree = t; _node = n; };

	RBTree_const_iterator<M>(const RBTree_const_iterator<M>& it) { *this = it; };

	template <class T>
	RBTree_const_iterator<M>( const RBTree_const_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = it->get_node(); 
		this->_rbtree = &it->_rbtree;
	}

	template <class T>
	RBTree_const_iterator<M>( const RBTree_const_iterator<T>& it, node_pointer n, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = n; 
		this->_rbtree = &it->_rbtree;
	}
	
	~RBTree_const_iterator<M>() {  };

	RBTree_const_iterator<M>& operator=( const RBTree_const_iterator<M>& it )
	{
		this->_node = it._node;
		this->_rbtree = it._rbtree;
		return *this;
	}

	pointer			base() const			{ return &_node->data; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };

	RBTree_const_iterator<M>	begin(rbtree_type* t)
	{
		_rbtree = t;
		_node = _rbtree->begin();
		return (*this);
	}

	RBTree_const_iterator<M>	end(rbtree_type* t)
	{
		_rbtree = t;
		_node = _rbtree->end();
		return (*this);
	}

	RBTree_const_iterator<M>& operator++()
	{ 
		_increment();
		return *this;
	};

	RBTree_const_iterator<M>& operator--()
	{ 
		_decrement();
		return *this;
	};
	
	RBTree_const_iterator<M> operator++( int )
	{
		RBTree_const_iterator<M> ori = *this;
		++(*this);
		return ori;
	};

	RBTree_const_iterator<M> operator--( int )
	{
		RBTree_const_iterator<M> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const RBTree_const_iterator<M>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const RBTree_const_iterator<M>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const RBTree_const_iterator<M>& it) const
	{
		if (_node == it._node) // TODO
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const RBTree_const_iterator<M>& it) const { return (!operator==(it)); };
	// end const

protected:

	void _increment( void )
	{
		_node = _rbtree->inorderSucc(_node);
	}

	void _decrement( void )
	{
		_node = _rbtree->inorderPre(_node);
	}
};

template <class M>
class RBTree_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename M::value_type
							,typename M::pointer, typename M::reference, typename M::difference_type>
{
public:
	typedef typename M::value_type						value_type;
	typedef typename M::pointer							pointer;
	typedef typename M::reference						reference;
	typedef typename std::bidirectional_iterator_tag	iterator_category;
	typedef typename M::difference_type 				difference_type;
	typedef typename M::size_type						size_type;
	typedef typename M::value_compare					key_compare;
	
	typedef RBTree<value_type, key_compare>				rbtree_type;
	typedef RBTree<const value_type, key_compare>		const_rbtree_type;
	typedef typename rbtree_type::Node					node_type;
	typedef typename rbtree_type::Node*					node_pointer;
	typedef typename const_rbtree_type::Node			const_node_type;
	typedef typename const_rbtree_type::Node*			const_node_pointer;

protected:
	rbtree_type*	_rbtree;
	node_pointer	_node;

public:
	RBTree_iterator<M>() : _rbtree(NULL), _node(node_pointer()) {  };

	RBTree_iterator<M>( rbtree_type* t) { _rbtree = t; };
	RBTree_iterator<M>( rbtree_type* t, node_pointer n ) { _rbtree = t; _node = n; };

	RBTree_iterator<M>( const_rbtree_type* t, const_node_pointer n ) { _rbtree = t; _node = n; };

	RBTree_iterator<M>(const RBTree_iterator<M>& it) { *this = it; };

	template <class T>
	RBTree_iterator<M>( const RBTree_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = it->get_node(); 
		this->_rbtree = &it->_rbtree;
	}

	template <class T>
	RBTree_iterator<M>( const RBTree_iterator<T>& it, node_pointer n, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = n; 
		this->_rbtree = &it->_rbtree;
	}
	
	~RBTree_iterator<M>() {  };

	RBTree_iterator<M>& operator=( const RBTree_iterator<M>& it )
	{
		this->_node = it._node;
		this->_rbtree = it._rbtree;
		return *this;
	}

	pointer			base() const			{ return &_node->data; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };

	RBTree_iterator<M>	begin(rbtree_type* t)
	{
		_rbtree = t;
		_node = _rbtree->begin();
		return (*this);
	}

	RBTree_iterator<M>	end(rbtree_type* t)
	{
		_rbtree = t;
		_node = _rbtree->end();
		return (*this);
	}

	RBTree_iterator<M>& operator++()
	{ 
		_increment();
		return *this;
	};

	RBTree_iterator<M>& operator--()
	{ 
		_decrement();
		return *this;
	};
	
	RBTree_iterator<M> operator++( int )
	{
		RBTree_iterator<M> ori = *this;
		++(*this);
		return ori;
	};

	RBTree_iterator<M> operator--( int )
	{
		RBTree_iterator<M> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const RBTree_iterator<M>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const RBTree_iterator<M>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const RBTree_iterator<M>& it) const
	{
		if (_node == it._node) // TODO
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const RBTree_iterator<M>& it) const { return (!operator==(it)); };
	// end const

protected:

	void _increment( void )
	{
		_node = _rbtree->inorderSucc(_node);
	}

	void _decrement( void )
	{
		_node = _rbtree->inorderPre(_node);
	}
};

}
#endif
