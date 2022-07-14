/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/14 17:50:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "iteratorTraits.hpp"
#include "iterator.hpp"
#include "iteratorTraits.hpp"

namespace ft
{

template <class V>
class vectorIterator : public ft::iterator<std::random_access_iterator_tag, typename V::value_type
							,typename V::pointer, typename V::reference, typename V::difference_type>
{
public:
	typedef typename V::value_type						value_type;
	typedef typename V::pointer							pointer;
	typedef typename V::reference						reference;
	typedef typename std::random_access_iterator_tag	iterator_category;
	typedef typename V::difference_type 				difference_type;
	typedef typename V::size_type						size_type;

	vectorIterator<V>() : _ptr(pointer()) {  };

	vectorIterator<V>(pointer ptr) : _ptr(ptr) {};

	vectorIterator<V>(vectorIterator<V>& it) { *this = it; };
	
	~vectorIterator<V>() {  };

	vectorIterator<V>& operator=( const vectorIterator<V>& it )
	{
		this->_ptr = it.base(); // WARNING : Might need a change https://cplusplus.com/reference/iterator/
		return *this;
	}

	pointer		base() const			{ return this->_ptr; };
	value_type	operator*() const		{ return *base(); };
	pointer		operator->() const		{ return base(); };
	value_type	operator[](size_type i)	{ return base()[i]; };

	vectorIterator<V>& operator++()	{ _ptr++; return *this; };
	vectorIterator<V>& operator--() { _ptr--; return *this;	};

	vectorIterator<V> operator+(difference_type n)	
	{ return vectorIterator<V>(_ptr + n); };

	difference_type operator+(const vectorIterator<V> & it)	
	{ return base() + it.base(); };
	
	vectorIterator<V> operator-(difference_type n)	
	{ return vectorIterator<V>(base() - n); };

	difference_type operator-(const vectorIterator<V> & it)	
	{ return base() - it.base(); };

	vectorIterator<V>& operator+=(difference_type n)
	{ _ptr += n; return *this; };
	
	vectorIterator<V>& operator-=(difference_type n)
	{ _ptr -= n; return *this; };
	
	vectorIterator<V> operator++( int )
	{
		vectorIterator<V> ori = *this;
		++(*this);
		return ori;
	};

	vectorIterator<V> operator--( int )
	{
		vectorIterator<V> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const vectorIterator<V>& it) const
	{
		if (base() == it.base())
			return true;  
		return false;
	};
	bool operator!=(const vectorIterator<V>& it) const	{ return (!operator==(it)); };
	bool operator>(const vectorIterator<V>& rhs) const	{ return (base() > rhs.base() ? true : false); };
	bool operator<(const vectorIterator<V>& rhs) const	{ return (base() < rhs.base() ? true : false); };
	bool operator>=(const vectorIterator<V>& rhs) const	{ return (base() >= rhs.base() ? true : false); };
	bool operator<=(const vectorIterator<V>& rhs) const	{ return (base() <= rhs.base() ? true : false); };
protected:
	pointer	_ptr;
};

}

#endif
