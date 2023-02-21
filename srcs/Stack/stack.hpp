/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2023/02/03 14:01:39 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "ft_lib.hpp"

#define TO_DIFF(T) (static_cast<difference_type>(T))
#define TO_SIZE(T) (static_cast<size_type>(T))

/*
	stack synopsis
*/
namespace ft
{
using std::allocator_traits;

template <class T, class Container = ft::vector<T> >
class stack
{	
public:	
	typedef Container										container_type;
	typedef typename container_type::value_type       		value_type;
	typedef typename container_type::reference      		reference;
	typedef typename container_type::const_reference		const_reference;
	typedef typename container_type::pointer        		pointer;
	typedef typename container_type::const_pointer			const_pointer;
	typedef typename container_type::size_type      		size_type;
	typedef typename container_type::difference_type		difference_type;

protected:
	container_type	_stack;

public:
	

	explicit stack( const container_type& cont = container_type() )
	{
		_stack = cont;
	}
	
	stack( const stack & other )
	{ 
		*this = other;
	}

	~stack() {  }

	stack& operator=(const stack& rhs)
	{
		_stack = rhs._stack;
		return *this;
	}

	reference top() { return _stack.back(); }
	const_reference top() const { return _stack.back(); }
	
	bool empty() const { return _stack.empty(); }
	size_type size() const { return _stack.size(); }
	
	void push( const value_type& value ) { _stack.push_back(value); }
	void pop() { _stack.pop_back(); }

	friend bool operator==( const stack& lhs, const stack& rhs) { return lhs._stack == rhs._stack; };
	friend bool operator<( const stack& lhs, const stack& rhs) { return (lhs._stack < rhs._stack); };
};

template< class T, class Container >
bool operator==( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return lhs._stack == rhs._stack; }

template< class T, class Container>
bool operator<( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>&rhs)
{ return (lhs._stack < rhs._stack); }

template< class T, class Container >
bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return !(lhs == rhs); }

template< class T, class Container>
bool operator>( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>&rhs)
{ return !(lhs < rhs) && lhs != rhs; }

template< class T, class Container>
bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>&rhs)
{ return !(lhs < rhs); }

template< class T, class Container>
bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>&rhs)
{ return !(lhs > rhs); }

template< class T, class Container>
void swap(stack<T, Container> & lhs, stack<T, Container> & rhs)
	{
		lhs._stack.swap(rhs._stack);
	}
} 

#endif
