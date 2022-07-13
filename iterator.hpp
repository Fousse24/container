/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/11 16:06:27 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include <memory>
#include <limits>
#include "iteratorTraits.hpp"

namespace ft
{

template <class Category, class T, class Pointer = T*
		, class Reference = T&, class Difference = std::ptrdiff_t>
struct iterator
{
	typedef T				value_type;
	typedef Pointer			pointer;
	typedef Reference		reference;
	typedef Difference	 	difference_type;
	typedef Category		iterator_category;
};


template <class Iter>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category
								, typename ft::iterator_traits<Iter>::value_type
								, typename ft::iterator_traits<Iter>::pointer
								, typename ft::iterator_traits<Iter>::reference
								, typename ft::iterator_traits<Iter>::difference_type>
{
public:
	typedef Iter													iterator_type;
	typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iter>::value_type			value_type;
	typedef typename ft::iterator_traits<Iter>::pointer				pointer;
	typedef typename ft::iterator_traits<Iter>::reference			reference;
	typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;

	reverse_iterator<Iter>() {  };

	reverse_iterator<Iter>(Iter type) { current = type; }

	template< class U >
	reverse_iterator<Iter>(const reverse_iterator<U>& it) { current = it; };
	
	~reverse_iterator<Iter>() {  };

	template< class U > 
	reverse_iterator<Iter>& operator=( const reverse_iterator<U>& it )
	{
		current.base() = it.base();
		return *this;
	}

	iterator_type	base() const	{ return current; };
	reference operator*() const		{ return *(current - 1); };
	pointer operator->() const		{ return &(operator*()); };

	value_type operator[](difference_type i)
	{
		return (base()[-i - 1]);
	};

	reverse_iterator<Iter>& operator++()	{ current--; return *this; };
	reverse_iterator<Iter>& operator--()	{ current++; return *this; };

	reverse_iterator<Iter> operator++( int )
	{
		reverse_iterator<Iter> ori = *this;
		++(*this);
		return ori;
	};

	reverse_iterator<Iter> operator--( int )
	{
		reverse_iterator<Iter> ori = *this;
		--(*this);
		return ori;
	};

	reverse_iterator<Iter> operator+(difference_type n)	
	{ return reverse_iterator<Iter>(base() - n); };
	
	 reverse_iterator<Iter> operator-(difference_type n)	
	{ return reverse_iterator<Iter>(base() + n); };

	difference_type operator-(const reverse_iterator<Iter> & it)	
	{ return base() - it.base(); };

	reverse_iterator<Iter>& operator+=(difference_type n)
	{ current -= n; return *this; };
	
	reverse_iterator<Iter>& operator-=(difference_type n)
	{ current += n; return *this; };

protected:
	iterator_type	current;
};

template< class Iter1, class Iter2 >
bool operator==( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() == rhs.base()); }

template< class Iter1, class Iter2 >
bool operator!=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() != rhs.base()); }

template< class Iter1, class Iter2 >
bool operator>( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() >= rhs.base()); }

template< class Iter1, class Iter2 >
bool operator<( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() < rhs.base()); }

template< class Iter1, class Iter2 >
bool operator>=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() >= rhs.base()); }

template< class Iter1, class Iter2 >
bool operator<=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (lhs.base() <= rhs.base()); }

template< class Iter >
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n
													,const reverse_iterator<Iter>& it )
{	
	return ( reverse_iterator<Iter>(it.base() - n) );
}

template< class Iter >
typename reverse_iterator<Iter>::difference_type operator-( const reverse_iterator<Iter>& lhs,
               												const reverse_iterator<Iter>& rhs )
{
	return (rhs.base() - lhs.base());
}

}

	// template <class Iter>
	// class RandomAccessIterator : public ft::iterator<std::random_access_iterator_tag, Iter::value_type
	// 									,Iter::pointer, Iter::reference, Iter::difference_type>
	// {
	// public:
	// 	// typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::value_type		value_type;
	// 	// typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::pointer			pointer;
	// 	// typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::reference			reference;
	// 	// typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::difference_type	difference_type;
	// 	// typedef typename Iter::size_type														size_type;
	// 	typedef typename Iter::value_type		value_type;
	// 	typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::pointer			pointer;
	// 	typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::reference			reference;
	// 	typedef typename ft::iterator<std::random_access_iterator_tag, Iter>::difference_type	difference_type;
	// 	typedef typename Iter::size_type														size_type;

	// 	RandomAccessIterator<Iter>() {  };

	// 	RandomAccessIterator<Iter>(pointer ptr) { this->_ptr = ptr; }

	// 	RandomAccessIterator<Iter>(const RandomAccessIterator<Iter>& it) { *this = it; };
		
	// 	virtual ~RandomAccessIterator<Iter>() {  };

	// 	virtual RandomAccessIterator<Iter>& operator=( const RandomAccessIterator<Iter>& it )
	// 	{
	// 		this->_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
	// 		return *this;
	// 	}

	// 	virtual pointer	base() 					{ return this->_ptr; };
	// 	virtual value_type operator*() const	{ return *this->_ptr; };

	// 	virtual RandomAccessIterator<Iter>& operator++()		{ this->_ptr++; return *this; }
	// 	virtual RandomAccessIterator<Iter>& operator--() 		{ this->_ptr--; return *this;	}

	// 	virtual RandomAccessIterator<Iter> operator+(size_type n)	{ return RandomAccessIterator<Iter>(this->_ptr + n); }
	// 	virtual RandomAccessIterator<Iter> operator-(size_type n)	{ return RandomAccessIterator<Iter>(this->_ptr - n); }

	// 	virtual RandomAccessIterator<Iter>& operator+=(size_type n)	{ this->_ptr += n; return *this; }
	// 	virtual RandomAccessIterator<Iter>& operator-=(size_type n)	{ this->_ptr -= n; return *this; }
		
	// 	virtual RandomAccessIterator<Iter> operator++( int )
	// 	{
	// 		RandomAccessIterator<Iter> ori = *this;
	// 		++(*this);
	// 		return ori;
	// 	}
	// 	virtual RandomAccessIterator<Iter> operator--( int )
	// 	{
	// 		RandomAccessIterator<Iter> ori = *this;
	// 		--(*this);
	// 		return ori;
	// 	}
		
	// 	virtual bool operator==(const RandomAccessIterator<Iter>& it) const
	// 	{
	// 		if (this->_ptr == it._ptr)
	// 			return true;  
	// 		return false;
	// 	}
	// 	virtual bool operator!=(const RandomAccessIterator<Iter>& it) const	{ return (!operator==(it)); }
	// 	virtual bool operator>(const RandomAccessIterator<Iter>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); }
	// 	virtual bool operator<(const RandomAccessIterator<Iter>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); }
	// 	virtual bool operator>=(const RandomAccessIterator<Iter>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); }
	// 	virtual bool operator<=(const RandomAccessIterator<Iter>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); }

	// 	virtual value_type operator[](int i)
	// 	{
	// 		return (*(base() + i));
	// 	}

	// 	iterator<T>(const iterator<T>& it) { *this = it; };
	// 	~iterator<T>() {  };

	// 	virtual iterator<T>& operator=( const iterator<T>& it )
	// 	{
	// 		_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
	// 		iterator_category = it.iterator_category;
	// 		return *this;
	// 	}

	// 	virtual value_type operator*() const
	// 	{
	// 		return *_ptr;
	// 	}

	// 	virtual iterator<T>& operator++()
	// 	{
	// 		_ptr++;
	// 		return *this;
	// 	}

	// 	virtual pointer	base()
	// 	{
	// 		return _ptr;
	// 	}
	
	// protected:
	// 	pointer	_ptr;
	// 	iterator<T>() {  };
	// };

	// template <typename T>
	// class input_iterator : public iterator<T>
	// {	
	// public:
	// 	input_iterator<T>(const input_iterator<T>& it) : iterator<T>(it)
	// 	{  
	// 		iterator<T>::iterator_category = ft::input_iterator_tag();
	// 	};

	// 	virtual const input_iterator<T>& operator++( int )
	// 	{
	// 		input_iterator<T> ori = *this;
	// 		this->_ptr++;
	// 		return ori;
	// 	}

	// 	virtual bool operator==(const input_iterator<T>& it) const
	// 	{
	// 		if (this->_ptr == it._ptr)
	// 			return true;  
	// 		return false;
	// 	}

	// 	virtual bool operator!=(const input_iterator<T>& it) const
	// 	{
	// 		return (!operator==(it));
	// 	}
	// protected:
	// 	input_iterator<T>() {  };
	// };

	// template <typename T>
	// class output_iterator : public input_iterator<T>
	// {	
	// public:
	// 	output_iterator<T>(const output_iterator<T>& it) : iterator<T>(it)
	// 	{  
	// 		iterator<T>::iterator_category = ft::output_iterator_tag();
	// 	};

	// 	virtual const input_iterator<T>& operator++( int )
	// 	{
	// 		input_iterator<T> ori = *this;
	// 		++(*this);
	// 		return ori;
	// 	}

	// 	virtual bool operator==(const input_iterator<T>& it) const
	// 	{
	// 		if (this->_ptr == it._ptr)
	// 			return true;  
	// 		return false;
	// 	}

	// 	virtual bool operator!=(const input_iterator<T>& it) const
	// 	{
	// 		return (!operator==(it));
	// 	}
	// protected:
	// 	output_iterator<T>() {  };

	// };

	// template <typename T>
	// class forward_iterator : public input_iterator<T>
	// {	
	// public:
	// 	forward_iterator<T>()
	// 	{
	// 		iterator<T>::iterator_category = ft::forward_iterator_tag();
	// 	};
	// };

	// template <typename T>
	// class bidirectional_iterator : public forward_iterator<T>
	// {	
	// public:
	// 	bidirectional_iterator<T>()
	// 	{
	// 		iterator<T>::iterator_category = ft::bidirectional_iterator_tag();
	// 	};
	// 	virtual bidirectional_iterator<T>& operator--()
	// 	{
	// 		this->_ptr--;
	// 		return *this;
	// 	}

	// 	virtual const bidirectional_iterator<T>& operator--( int )
	// 	{
	// 		bidirectional_iterator<T> ori = *this;
	// 		--(*this);
	// 		return ori;
	// 	}
	// };

	// template <typename T>
	// class random_access_iterator : public bidirectional_iterator<T>
	// {	
	// public:
	// 	random_access_iterator<T>() 
	// 	{
	// 		iterator<T>::iterator_category = std::random_access_iterator_tag();
	// 	};
	// 	// random_access_iterator<T> operator+(int n)
	// 	// {
	// 	// 	this->_ptr += n;
	// 	// 	return random_access_iterator<T>();
	// 	// }
	// 	virtual random_access_iterator<T>& operator+=(int n)
	// 	{
	// 		this->_ptr += n;
	// 		return *this;
	// 	}

	// 	virtual random_access_iterator<T>& operator-=(int n)
	// 	{
	// 		this->_ptr -= n;
	// 		return *this;
	// 	}

	// 	virtual bool operator>(const random_access_iterator<T>& rhs)
	// 	{
	// 		return (this->_ptr > rhs._ptr ? true : false);
	// 	}

	// 	virtual bool operator<(const random_access_iterator<T>& rhs)
	// 	{
	// 		return (this->_ptr < rhs._ptr ? true : false);
	// 	}

	// 	virtual bool operator>=(const random_access_iterator<T>& rhs)
	// 	{
	// 		return (this->_ptr >= rhs._ptr ? true : false);
	// 	}

	// 	virtual bool operator<=(const random_access_iterator<T>& rhs)
	// 	{
	// 		return (this->_ptr <= rhs._ptr ? true : false);
	// 	}

	// 	virtual bool operator[](const random_access_iterator<T>& rhs)
	// 	{
	// 		return (this->_ptr < rhs._ptr ? true : false);
	// 	}
	// };

#endif
