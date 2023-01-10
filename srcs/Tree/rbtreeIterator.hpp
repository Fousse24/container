/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtreeIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/15 16:53:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef rbtreeIterator_HPP
#define rbtreeIterator_HPP

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
class rbtreeIterator : public ft::iterator<std::bidirectional_iterator_tag, typename M::value_type
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
	
	typedef RBTree<value_type, key_compare>			t_rbtree;
	typedef typename t_rbtree::Node		node_type;
	typedef typename t_rbtree::Node*	node_pointer;

	friend class rbtreeIterator<M>;

protected:
	t_rbtree*		_rbtree;
	node_pointer	_node;

public:
	rbtreeIterator<M>() : _rbtree(NULL), _node(node_pointer()) {  };

	rbtreeIterator<M>( t_rbtree* t) { _rbtree = t; };
	rbtreeIterator<M>( t_rbtree* t, node_pointer n ) { _rbtree = t; _node = n; };

	rbtreeIterator<M>(const rbtreeIterator<M>& it) { *this = it; };

	template <class T>
	rbtreeIterator<M>( const rbtreeIterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = it->get_node(); 
		this->_rbtree = &it->_rbtree;
	}

	template <class T>
	rbtreeIterator<M>( const rbtreeIterator<T>& it, node_pointer n, typename ft::enable_if<ft::is_not_same<T, const M>, bool>::type = 0) 
	{ 
		// TODO ?
		this->_node = n; 
		this->_rbtree = &it->_rbtree;
	}
	
	~rbtreeIterator<M>() {  };

	rbtreeIterator<M>& operator=( const rbtreeIterator<M>& it )
	{
		this->_node = it._node;
		this->_rbtree = it._rbtree;
		return *this;
	}

	pointer			base() const			{ return &_node->data; };
	node_pointer	get_node() const		{ return _node; };
	reference		operator*() const		{ return *base(); };
	pointer			operator->() const		{ return base(); };

	rbtreeIterator<M>	begin(t_rbtree* t)
	{
		_rbtree = t;
		_node = _rbtree->begin();
		return (*this);
	}

	rbtreeIterator<M>	end(t_rbtree* t)
	{
		_rbtree = t;
		_node = _rbtree->end();
		return (*this);
	}

	rbtreeIterator<M>& operator++()
	{ 
		_increment();
		return *this;
	};

	rbtreeIterator<M>& operator--()
	{ 
		_decrement();
		return *this;
	};
	
	rbtreeIterator<M> operator++( int )
	{
		rbtreeIterator<M> ori = *this;
		++(*this);
		return ori;
	};

	rbtreeIterator<M> operator--( int )
	{
		rbtreeIterator<M> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const rbtreeIterator<M>& it) const
	{
		if (_node == it._node)
			return true;  
		return false;
	};
	bool operator!=(const rbtreeIterator<M>& it) const { return (!operator==(it)); };

	// const overloads
	template <class T>
	bool operator==(const rbtreeIterator<M>& it) const
	{
		if (_node == it._node) // TODO
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const rbtreeIterator<M>& it) const { return (!operator==(it)); };
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
