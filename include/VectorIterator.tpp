/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.tpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/05 19:09:30 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_TPP
#define VECTOR_ITERATOR_TPP

#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "IteratorTraits.hpp"

#define FT_VECT_BUFFER	10

namespace ft
{

template <class V>
class VectorIterator
{
public:
	typedef typename V::value_type						value_type;
	typedef typename V::pointer							pointer;
	typedef typename V::reference						reference;
	typedef typename std::random_access_iterator_tag	iterator_category;
	typedef typename V::difference_type 				difference_type;
	typedef typename V::size_type						size_type;

	VectorIterator<V>() {  };

	VectorIterator<V>(pointer ptr) { this->_ptr = ptr; }

	VectorIterator<V>(const VectorIterator<V>& it) { *this = it; };
	
	virtual ~VectorIterator<V>() {  };

	virtual VectorIterator<V>& operator=( const VectorIterator<V>& it )
	{
		this->_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
		return *this;
	}

	virtual pointer	base() 					{ return this->_ptr; };
	virtual value_type operator*() const	{ return *this->_ptr; };

	virtual VectorIterator<V>& operator++()		{ this->_ptr++; return *this; };
	virtual VectorIterator<V>& operator--() 		{ this->_ptr--; return *this;	};

	virtual VectorIterator<V> operator+(difference_type n)	{ return VectorIterator<V>(this->_ptr + n); };
	virtual VectorIterator<V> operator-(difference_type n)	{ return VectorIterator<V>(this->_ptr - n); };

	virtual VectorIterator<V>& operator+=(difference_type n)	{ this->_ptr += n; return *this; };
	virtual VectorIterator<V>& operator-=(difference_type n)	{ this->_ptr -= n; return *this; };
	
	virtual VectorIterator<V> operator++( int )
	{
		VectorIterator<V> ori = *this;
		++(*this);
		return ori;
	};

	virtual VectorIterator<V> operator--( int )
	{
		VectorIterator<V> ori = *this;
		--(*this);
		return ori;
	};
	
	virtual bool operator==(const VectorIterator<V>& it) const
	{
		if (this->_ptr == it._ptr)
			return true;  
		return false;
	};
	virtual bool operator!=(const VectorIterator<V>& it) const	{ return (!operator==(it)); };
	virtual bool operator>(const VectorIterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); };
	virtual bool operator<(const VectorIterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); };
	virtual bool operator>=(const VectorIterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); };
	virtual bool operator<=(const VectorIterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); };

	virtual value_type operator[](int i)
	{
		return (*(base() + i));
	};
protected:
	pointer	_ptr;

};
}

#endif
