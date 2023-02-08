/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2023/02/07 16:18:25 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "iterator_traits.hpp"
// #include "map_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbnode.hpp"
#include "enable_if.hpp"
#include "pair.hpp"
#include "ft_lib.hpp"
#include "rbtree.hpp"

#define TO_DIFF(T) (static_cast<difference_type>(T))
#define TO_SIZE(T) (static_cast<size_type>(T))

/*
	map synopsis
*/
namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{	
public:	
	typedef Allocator                               		allocator_type;
	typedef Key												key_type;
	typedef Compare											key_compare;
	typedef T												mapped_type;
	typedef ft::pair<const key_type, mapped_type>       	value_type;
	typedef typename allocator_type::size_type      		size_type;
	typedef typename allocator_type::difference_type		difference_type;
	typedef typename allocator_type::reference      		reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer        		pointer;
	typedef typename allocator_type::const_pointer			const_pointer;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{   
		friend class map;
	public:
		Compare comp_;
		value_compare () {}
		// value_compare (Compare c) : comp_(c) {}  // constructed with map's comparison object
		
		typedef bool		result_type;
		typedef key_type	first_arg_type;
		typedef mapped_type	second_arg_type;

		const Compare& key_comp() const
		{
			return comp_;
		}

		bool operator()(const value_type& x, const value_type& y) const
		{
			return key_comp()(x.first, y.first);
		}

		bool operator()(const key_type& x, const value_type& y) const
		{
			return key_comp()(x, y.first);
		}

		bool operator()(const value_type& x, const key_type& y) const
		{
			return key_comp()(x.first, y);
		}
	};

	typedef rbtree<value_type, value_compare, Allocator>	tree_type;
	typedef typename tree_type::Node						node_type;
	typedef node_type*										node_ptr;
	typedef typename tree_type::iterator 					iterator;
	typedef typename tree_type::const_iterator				const_iterator;
	typedef typename tree_type::reverse_iterator			reverse_iterator;
	typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

private: // WARNING private
	tree_type		_tree;
	Allocator		_allocator;

public:
	map()
	{
		_init_map();
		_allocator = Allocator();
	}

	explicit map(const Allocator& alloc)
	{
		_init_map();
		_allocator = alloc;
	}

	explicit map( size_type count, const T value = value_type(),
                 	const Allocator& alloc = Allocator())
	{
		_test_max_size(count);
		_allocator = alloc;
		_init_map();
		assign(count, value);
	}
	
	map( const map& other )
	{ 
		// _init_map();
		*this = other;
	}

	template <class Iter>
	map(Iter first, Iter last, const allocator_type& = allocator_type(),
				typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0)
	{
		_init_map();
		assign(first, last);
	}

	~map() { clear(); }

	map& operator=(const map& rhs)
	{
		this->clear();
		// for (map::iterator it = rhs.begin(); it != rhs.end(); it++)
		this->insert(rhs.begin(), rhs.end());
		return *this;
	}
	
	allocator_type get_allocator() const { return Allocator(); }
	

	// iterator	
	iterator		begin()			{ return _tree.begin(); }
	const_iterator	begin() const	{ return const_iterator(_tree.begin()); }

	iterator		end() 			{ return _tree.end(); }
	const_iterator	end() const 	{ return const_iterator(_tree.end());}
	
	reverse_iterator       rbegin()			{ return _tree.rbegin(); }
	const_reverse_iterator rbegin() const 	{ return _tree.rbegin(); }
	reverse_iterator       rend() 			{ return _tree.rend(); }
	const_reverse_iterator rend() const 	{ return _tree.rend(); }
	// iterator end


	/* Element access */
	reference       operator[](const Key& key) // Must not check bounds
	{
		node_ptr node = _tree.findNode(_tree.getRoot(), ft::make_pair(key, mapped_type()));

		if (_tree.isNil(node))
		{
			node = _tree.insert(value_type(key, mapped_type()));
		}
		return *node->data;
	};
	
	const_reference operator[](const Key& key) const // Must not check bounds
	{
		node_ptr node = _tree.findNode(_tree.getRoot(), ft::make_pair(key, mapped_type()));

		if (_tree.isNil(node))
		{
			node = _tree.insert(value_type(key, mapped_type()));
		}
		return *node->data;
	}

	reference       at(const Key& key) // Should not check negative??
	{
		node_ptr	node;

		node = _tree.findNode(_tree.getRoot(), key);
		if (!node)
			throw std::out_of_range("is not in map");
		return *node->data;
	}
	
	const_reference at(const Key& key) const 
	{
		node_ptr	node;

		node = _tree.findNode(_tree.getRoot(), key);
		if (!node)
			throw std::out_of_range("is not in map");
		return *node->data;
	}

	/* Element access end */


	/* Capacity */
	bool 		empty() const	{ return (_tree.empty()); }
	size_type	size() const { return _tree.size(); }
	size_type	max_size() const { return std::min(TO_SIZE(std::numeric_limits<difference_type>::max()), _allocator.max_size()) ; }

	/* Capacity end */


	/* Modifier */
	void clear()
	{
		_tree.clear();
	}

	ft::pair<iterator, bool> insert(const value_type& t)
	{
		node_ptr	node;
		
		node = _tree.findNode(_tree.getRoot(), t);
		if (node)
			return ft::make_pair(iterator(node), false);
			
		node = _tree.insert(t);
		if (!node)
			return ft::make_pair(iterator(node), false);

		return ft::make_pair(iterator(node), true);
		
	}

	iterator insert( iterator, const value_type& value ) // WARNING
	{
		return (insert(value).first);
	
	}

	// template<class Iter>
	// void insert(Iter first, Iter last) // change to input only
	// {
	// 	while (first != last)
	// 	{
	// 		insert(*first);
	// 		++first;
	// 	}
	// 	return ;
	// }
	
	void erase(iterator pos)
	{
		erase((*pos).first);
	}

	size_type	erase(const key_type& key)
	{
		bool	deleted;

		deleted = _tree.erase(ft::make_pair(key, mapped_type()));
		return deleted ? 1 : 0;
	}

	void erase(iterator first, iterator last)
	{
		while (first != last)
		{
			erase((*first).first);
			++first;
		}
	}

	// void swap(map & other)
	// {
	// 	node_ptr		save;
	// 	size_type	size_;

	// 	save = other._tree.getRoot();
	// 	size_ = other.size();

	// 	other._size = _size;
	// 	other._tree._setRoot(_tree.getRoot());

	// 	_size = size_;
	// 	_tree._setRoot(save);
	// }
	
	ft::pair<iterator, iterator> equal_range( const T & data ) 
	{
		return (_tree.equal_range(value_type(ft::make_pair(data, mapped_type()))));		
	}

	ft::pair<const_iterator, const_iterator> equal_range( const T & data ) const 
	{
		return (_tree.equal_range(value_type(ft::make_pair(data, mapped_type()))));	
	}

	iterator lower_bound( const T & data ) 
	{
		return (_tree.lower_bound(value_type(ft::make_pair(data, mapped_type()))));	
	}

	const_iterator lower_bound( const T & data ) const 
	{
		return (_tree.lower_bound(value_type(ft::make_pair(data, mapped_type()))));
	}

	iterator upper_bound( const Key & data ) 
	{
		return (_tree.upper_bound(value_type(ft::make_pair(data, mapped_type()))));
	}

	const_iterator upper_bound( const Key & data ) const 
	{
		return (_tree.upper_bound(value_type(ft::make_pair(data, mapped_type()))));
	}

	key_compare		key_comp() const { return value_compare().key_comp(); }
	value_compare	value_comp() const { return value_compare(); }

private:

	bool	_test_max_size(size_type n)
	{
		if (n > max_size())
			throw std::length_error("out of bound");
		return true;
	}

	void	_init_map(void)
	{
		// _size = 0;
		// _tree = t_tree();
	}
};

template< class T, class Alloc >
bool operator==( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class T, class Alloc >
bool operator!=( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>& rhs)
{ return !(lhs == rhs); }

template< class T, class Alloc >
bool operator>( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>&rhs)
{ return !(lhs < rhs) && lhs != rhs; }

template< class T, class Alloc >
bool operator<( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>&rhs)
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class T, class Alloc >
bool operator>=( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>&rhs)
{ return !(lhs < rhs); }

template< class T, class Alloc >
bool operator<=( const ft::map<T, Alloc>& lhs, const ft::map<T, Alloc>&rhs)
{ return !(lhs > rhs); }

template< class T, class Alloc>
void swap(map<T, Alloc> & lhs, map<T, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}
}  


#endif
