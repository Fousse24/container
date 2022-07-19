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
	typedef T1	first_type;
	typedef T2	second_type;

	pair() {  };
	pair( const T1 & x, const T2 & y ) : first(x), second(y) {  };
	template <class U1, class U2>
	pair( const pair<U1, U2> & p ) : first(p.getFirst()), second(p.getSecond()) {  };
	~pair() {  };

	pair& operator=( const pair & other )
	{
		first = other.getFirst();
		second = other.getSecond();
		return *this;
	}

	const first_type & getFirst(void) const { return first; };
	const second_type & getSecond(void) const { return second; };

private:
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
{ return (lhs.getFirst() == rhs.getFirst() && lhs.getSecond() == rhs.getSecond()); }

template< class T1, class T2 >
bool operator!=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return !(lhs == rhs); }

template< class T1, class T2 >
bool operator>( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.getFirst() > rhs.getFirst() && lhs.getSecond() > rhs.getSecond()); }

template< class T1, class T2 >
bool operator<( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.getFirst() < rhs.getFirst() && lhs.getSecond() < rhs.getSecond()); }

template< class T1, class T2 >
bool operator>=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.getFirst() >= rhs.getFirst() && lhs.getSecond() >= rhs.getSecond()); }

template< class T1, class T2 >
bool operator<=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{ return (lhs.getFirst() <= rhs.getFirst() && lhs.getSecond() <= rhs.getSecond()); }

template< class T1, class T2 >
std::ostream & operator<<( std::ostream & os, const ft::pair<T1, T2>& rhs ) 
{ 
	os << "Pair || first = " << rhs.getFirst() << " | second = " << rhs.getSecond();
	return os;
}

}

#endif
