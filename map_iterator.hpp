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

namespace ft
{

template <class V>
class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, typename V::value_type
							,typename V::pointer, typename V::reference, typename V::difference_type>
{
public:
	typedef typename V::value_type						value_type;
	typedef typename V::pointer							pointer;
	typedef typename V::reference						reference;
	typedef typename std::random_access_iterator_tag	iterator_category;
	typedef typename V::difference_type 				difference_type;
	typedef typename V::size_type						size_type;

	map_iterator<V>() : _ptr(pointer()) {  };

	map_iterator<V>(pointer ptr) : _ptr(ptr) {};

	map_iterator<V>(const map_iterator<V>& it) { *this = it; };

	template <class T>
	map_iterator<V>( const map_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const V>, bool>::type = 0) 
	{ this->_ptr = it.base(); }
	
	~map_iterator<V>() {  };

	map_iterator<V>& operator=( const map_iterator<V>& it )
	{
		this->_ptr = it.base();
		return *this;
	}

	pointer		base() const			{ return this->_ptr; };
	reference	operator*() const		{ return *base(); };
	pointer		operator->() const		{ return base(); };

	map_iterator<V>& operator++()	{ _ptr++; return *this; };
	map_iterator<V>& operator--() { _ptr--; return *this;	};
	
	map_iterator<V> operator++( int )
	{
		map_iterator<V> ori = *this;
		++(*this);
		return ori;
	};

	map_iterator<V> operator--( int )
	{
		map_iterator<V> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const map_iterator<V>& it) const
	{
		if (base() == it.base())
			return true;  
		return false;
	};
	bool operator!=(const map_iterator<V>& it) const		{ return (!operator==(it)); };

	// const overloads

	template <class T>
	bool operator==(const map_iterator<T>& it) const
	{
		if (base() == it.base())
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const map_iterator<T>& it) const		{ return (!operator==(it)); };
	// end const

protected:
	pointer	_ptr;
};

}
#endif
