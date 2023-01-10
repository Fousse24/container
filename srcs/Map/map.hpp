/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/09/01 16:36:25 by sfournie         ###   ########.fr       */
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
#include "iterator_traits.hpp"
// #include "map_iterator.hpp"
#include "rbtreeIterator.hpp"
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
	typedef typename allocator_type::reference      		reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer        		pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef ft::rbtreeIterator<map<Key, T> > 				iterator;
	typedef ft::rbtreeIterator<map<Key, T> >				const_iterator;
	typedef typename allocator_type::size_type      		size_type;
	typedef typename allocator_type::difference_type		difference_type;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	typedef RBTree<value_type >			t_tree;
	typedef typename t_tree::Node		t_node;

public: // WARNING private
	t_tree								_tree;
	size_type							_size;
	Allocator							_allocator;

public: 

	class value_compare // À REVOIR
	{
	public:
		bool operator()( const reference lhs, const reference rhs ) const 
		{  
			return _comp(lhs < rhs);
		};

		bool operator()( const value_type lhs, const value_type rhs ) const 
		{  
			return _comp(lhs.first < rhs.second);
		};
		~value_compare() {  };
	protected:
		Compare	_comp;
		value_compare( Compare c ) : _comp(c) {  };
	};

	map()
	{
		_init_map();
		_allocator = Allocator();
	};

	explicit map(const Allocator& alloc)
	{
		_init_map();
		_allocator = alloc;
	};

	explicit map( size_type count, const T value = value_type(),
                 	const Allocator& alloc = Allocator())
	{
		_test_max_size(count);
		_allocator = alloc;
		_init_map();
		assign(count, value);
	};
	
	map( const map& other )
	{ 
		// _init_map();
		*this = other;
	};

	template <class Iter>
	 	map<T>(Iter first, Iter last, const allocator_type& = allocator_type(),
				typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0)
	{
		_init_map();
		assign(first, last);
	};

	~map() { clear(); };

	map& operator=(const map& rhs)
	{
		this->clear();
		// for (map::iterator it = rhs.begin(); it != rhs.end(); it++)
		this->insert(rhs.begin(), rhs.end());
		return *this;
	};
	
	allocator_type get_allocator() const { return Allocator(); };
	

	// iterator	
	iterator		begin()			{ return iterator(&_tree).begin(&_tree); };
	const_iterator	begin() const	{ return const_iterator(&_tree).begin(&_tree); };

	iterator		end() 			{ return iterator(&_tree).end(&_tree); };
	const_iterator	end() const 	{ return const_iterator(&_tree).end(&_tree);};
	
	reverse_iterator       rbegin()			{ return reverse_iterator(end() - 1); };
	const_reverse_iterator rbegin() const 	{ return const_reverse_iterator(end() - 1); };
	reverse_iterator       rend() 			{ return reverse_iterator(begin() - 1); };
	const_reverse_iterator rend() const 	{ return const_reverse_iterator(begin() - 1); };
	// iterator end


	/* Element access */
	reference       operator[](const Key& key) // Must not check bounds
	{
		return _tree.find_node(_tree.getRoot(), key)->key;
	};
	
	const_reference operator[](const Key& key) const // Must not check bounds
	{
		return _tree.find_node(_tree.getRoot(), key)->key;
	};

	reference       at(const Key& key) // Should not check negative??
	{
		t_node*	node;

		node = _tree.find_node(_tree.getRoot(), key);
		if (!node)
			throw std::out_of_range("is not in map");
		return node->key;
	};
	
	const_reference at(const Key& key) const 
	{
		t_node*	node;

		node = _tree.find_node(_tree.getRoot(), key);
		if (!node)
			throw std::out_of_range("is not in map");
		return node->key;
	};

	/* Element access end */


	/* Capacity */
	bool 		empty() const	{ return (_size <= 0 ? true : false); };
	size_type	size() const { return _size; };
	size_type	max_size() const { return std::min(TO_SIZE(std::numeric_limits<difference_type>::max()), _allocator.max_size()) ; };

	/* Capacity end */


	/* Modifier */
	void clear()
	{
		// iterator end_ = end();
		// iterator begin_ = begin();
		
		// if (!_tree || begin_ == end_)
		// 	return ;

		// for (; begin_ < end_; begin_++)
		// {
		// 	_allocator.destroy(begin_.base());	
		// }
		// _size = 0;
	};

	ft::pair<iterator, bool> insert(const value_type& t)
	{
		t_node*	node;
		
		node = _tree.find_node(_tree.getRoot(), t);
		if (node)
			return ft::make_pair(iterator(&_tree, node), false);
			
		node = _tree.insert(t);
		if (!node)
			return ft::make_pair(iterator(&_tree, node), false);
		_size++;
		return ft::make_pair(iterator(&_tree, node), true);
		
	};

	iterator insert( iterator, const value_type& value ) // WARNING
	{
		return (insert(value).first);
	
	}

	template<class Iter>
	void insert(Iter first, Iter last) // change to input only
	{
		while (first != last)
		{
			insert(*first);
			++first;
		}
		return ;
	};
	
	void erase(iterator pos)
	{
		erase((*pos).first);
	};

	size_type	erase(const key_type& key)
	{
		int	deleted;

		deleted = _tree.deleteNode(ft::make_pair(key, mapped_type()));
		_size -= deleted;
		return (size_type)deleted;
	}

	void erase(iterator first, iterator last)
	{
		while (first != last)
		{
			erase((*first).first);
			++first;
		}
	};

	void swap(map & other)
	{
		t_node*		save;
		size_type	size_;

		save = other._tree.getRoot();
		size_ = other.size();

		other._size = _size;
		other._tree._setRoot(_tree.getRoot());

		_size = size_;
		_tree._setRoot(save);
	}
	
private:

	bool	_test_max_size(size_type n)
	{
		if (n > max_size())
			throw std::length_error("out of bound");
		return true;
	};

	void	_init_map(void)
	{
		_size = 0;
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
