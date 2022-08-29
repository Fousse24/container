/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/08/29 13:58:52 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include <memory>
#include <limits>
#include "iterator_traits.hpp"

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
class reverse_iterator
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
	reverse_iterator<Iter>(const reverse_iterator<U>& it) { *this = it; };
	
	~reverse_iterator<Iter>() {  };

	template< class U > 
	reverse_iterator<Iter>& operator=( const reverse_iterator<U>& it )
	{
		current = it.base();
		return *this;
	}

	iterator_type	base() const	{ return current; };
	reference operator*() const		{ return *current; };
	pointer operator->() const		{ return &(operator*()); };

	value_type operator[](difference_type i)
	{
		return (base()[-i]);
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
	{ return it.base() - base(); };

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
{ return (rhs.base() > lhs.base()); }

template< class Iter1, class Iter2 >
bool operator<( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (rhs.base() < lhs.base()); }

template< class Iter1, class Iter2 >
bool operator>=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (rhs.base() >= lhs.base()); }

template< class Iter1, class Iter2 >
bool operator<=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
{ return (rhs.base() <= lhs.base()); }

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

#endif
