/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/15 16:53:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

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
class vector_iterator : public ft::iterator<std::random_access_iterator_tag, typename V::value_type
							,typename V::pointer, typename V::reference, typename V::difference_type>
{
public:
	typedef typename V::value_type						value_type;
	typedef typename V::pointer							pointer;
	typedef typename V::reference						reference;
	typedef typename std::random_access_iterator_tag	iterator_category;
	typedef typename V::difference_type 				difference_type;
	typedef typename V::size_type						size_type;

	vector_iterator<V>() : _ptr(pointer()) {  };

	vector_iterator<V>(pointer ptr) : _ptr(ptr) {};

	vector_iterator<V>(const vector_iterator<V>& it) { *this = it; };

	template <class T>
	vector_iterator<V>( const vector_iterator<T>& it, typename ft::enable_if<ft::is_not_same<T, const V>, bool>::type = 0) 
	{ this->_ptr = it.base(); }
	
	~vector_iterator<V>() {  };

	vector_iterator<V>& operator=( const vector_iterator<V>& it )
	{
		this->_ptr = it.base();
		return *this;
	}

	pointer		base() const			{ return this->_ptr; };
	reference	operator*() const		{ return *base(); };
	pointer		operator->() const		{ return base(); };
	reference	operator[](size_type i)	{ return base()[i]; };

	vector_iterator<V>& operator++()	{ _ptr++; return *this; };
	vector_iterator<V>& operator--() { _ptr--; return *this;	};

	vector_iterator<V> operator+(difference_type n)	
	{ return vector_iterator<V>(_ptr + n); };
	
	vector_iterator<V> operator-(difference_type n)	
	{ return vector_iterator<V>(_ptr - n); };

	difference_type operator-(const vector_iterator<V> & it)	
	{ return base() - it.base(); };

	vector_iterator<V>& operator+=(difference_type n)
	{ _ptr += n; return *this; };
	
	vector_iterator<V>& operator-=(difference_type n)
	{ _ptr -= n; return *this; };
	
	vector_iterator<V> operator++( int )
	{
		vector_iterator<V> ori = *this;
		++(*this);
		return ori;
	};

	vector_iterator<V> operator--( int )
	{
		vector_iterator<V> ori = *this;
		--(*this);
		return ori;
	};


	bool operator==(const vector_iterator<V>& it) const
	{
		if (base() == it.base())
			return true;  
		return false;
	};
	bool operator!=(const vector_iterator<V>& it) const		{ return (!operator==(it)); };
	bool operator>(const vector_iterator<V>& rhs) const		{ return (base() > rhs.base() ? true : false); };
	bool operator<(const vector_iterator<V>& rhs) const		{ return (base() < rhs.base() ? true : false); };
	bool operator>=(const vector_iterator<V>& rhs) const	{ return (base() >= rhs.base() ? true : false); };
	bool operator<=(const vector_iterator<V>& rhs) const	{ return (base() <= rhs.base() ? true : false); };


	// const overloads
	template <class T>
	difference_type operator-(const vector_iterator<T> & it)	
	{ return base() - it.base(); };

	template <class T>
	bool operator==(const vector_iterator<T>& it) const
	{
		if (base() == it.base())
			return true;  
		return false;
	};
	template <class T>
	bool operator!=(const vector_iterator<T>& it) const		{ return (!operator==(it)); };
	template <class T>
	bool operator>(const vector_iterator<T>& rhs) const		{ return (base() > rhs.base() ? true : false); };
	template <class T>
	bool operator<(const vector_iterator<T>& rhs) const		{ return (base() < rhs.base() ? true : false); };
	template <class T>
	bool operator>=(const vector_iterator<T>& rhs) const	{ return (base() >= rhs.base() ? true : false); };
	template <class T>
	bool operator<=(const vector_iterator<T>& rhs) const	{ return (base() <= rhs.base() ? true : false); };
	// end const

protected:
	pointer	_ptr;
};

template <class T>
typename vector_iterator<T>::pointer operator+(const typename vector_iterator<T>::difference_type & n
														, const vector_iterator<T> & it)	
	{ return it.base() + n; }

}

#endif
