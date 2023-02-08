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

#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>
#include <ostream>

namespace ft
{

template <class T1, class T2>
class pair
{
public:
	typedef T1 first_type;
	typedef T2 second_type;

	pair() : first(first_type()), second(second_type()) {  }
	pair( const first_type & x, const second_type & y ) : first(x), second(y) {  }
	template <class U1, class U2>
	pair( const pair<U1, U2> & p ) : first(p.first), second(p.second) {  }
	~pair() {  }

	pair& operator=( const pair & rhs )
	{
		first = rhs.first;
		second = rhs.second;
		return *this;
	}

	template<class U1, class U2>
	pair& operator=( const pair<U1, U2> & rhs )
	{
		first = rhs.first;
		second = rhs.second;
		return *this;
	}


	first_type	first;
	second_type	second;

	// friend bool operator==( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend bool operator!=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend bool operator>( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend bool operator<( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend bool operator>=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend bool operator<=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs);
	// friend std::ostream & operator<<( std::ostream & os, const ft::pair<T1, T2>& rhs );
};

template< class T1, class T2 >
bool operator==( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

template< class T1, class T2 >
bool operator!=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return !(lhs == rhs); }

template< class T1, class T2 >
bool operator<( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.first < rhs.first && lhs.second < rhs.second); }

template< class T1, class T2 >
bool operator<=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs < rhs | lhs == rhs); }

template< class T1, class T2 >
bool operator>( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (!(lhs <= rhs)); }

template< class T1, class T2 >
bool operator>=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (!(lhs < rhs)); }

template< class T1, class T2 >
std::ostream & operator<<( std::ostream & os, const ft::pair<T1, T2>& rhs ) 
{ 
	os << rhs.first << " | " << rhs.second;
	return os;
}

template<class T1, class T2>
pair<T1, T2>	make_pair(T1 t1, T2 t2)
{
	return pair<T1, T2>(t1, t2);
}

// template<class T1, class T2, class U1, class U2>
// pair<T1, T2>	make_pair(U1 u1, U2 u2)
// {
// 	return pair<T1, T2>(u1, u2);
// }

}

#endif
