/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/07 15:32:12 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Iterator.hpp"
#include "IteratorTraits.hpp"

#define FT_VECT_BUFFER	10

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

	typedef typename ft::iterator_traits<vectorIterator<V> >	iterator_traits;
	vectorIterator<V>() {  };

	vectorIterator<V>(pointer ptr) { this->_ptr = ptr; }

	vectorIterator<V>(const vectorIterator<V>& it) { *this = it; };
	
	virtual ~vectorIterator<V>() {  };

	virtual vectorIterator<V>& operator=( const vectorIterator<V>& it )
	{
		this->_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
		return *this;
	}

	virtual pointer	base() const			{ return this->_ptr; };
	virtual value_type operator*() const	{ return *this->_ptr; };

	virtual vectorIterator<V>& operator++()	{ this->_ptr++; return *this; };
	virtual vectorIterator<V>& operator--() { this->_ptr--; return *this;	};

	virtual vectorIterator<V> operator+(difference_type n)	
	{ return vectorIterator<V>(this->_ptr + n); };
	
	virtual vectorIterator<V> operator-(difference_type n)	
	{ return vectorIterator<V>(this->_ptr - n); };

	difference_type operator-(const vectorIterator<V> & it)	
	{ return base() - it.base(); };

	virtual vectorIterator<V>& operator+=(difference_type n)
	{ this->_ptr += n; return *this; };
	
	virtual vectorIterator<V>& operator-=(difference_type n)
	{ this->_ptr -= n; return *this; };
	
	virtual vectorIterator<V> operator++( int )
	{
		vectorIterator<V> ori = *this;
		++(*this);
		return ori;
	};

	virtual vectorIterator<V> operator--( int )
	{
		vectorIterator<V> ori = *this;
		--(*this);
		return ori;
	};
	
	virtual bool operator==(const vectorIterator<V>& it) const
	{
		if (this->_ptr == it._ptr)
			return true;  
		return false;
	};
	virtual bool operator!=(const vectorIterator<V>& it) const	{ return (!operator==(it)); };
	virtual bool operator>(const vectorIterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); };
	virtual bool operator<(const vectorIterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); };
	virtual bool operator>=(const vectorIterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); };
	virtual bool operator<=(const vectorIterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); };

	virtual value_type operator[](size_type i)
	{
		return (base()[i]);
	};
protected:
	pointer	_ptr;

};
}

#endif
