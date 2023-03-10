/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2023/02/03 14:01:39 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "vector_iterator.hpp"
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "ft_lib.hpp"

#define TO_DIFF(T) (static_cast<difference_type>(T))
#define TO_SIZE(T) (static_cast<size_type>(T))

/*
	vector synopsis
*/
namespace ft
{
using std::allocator_traits;

template <class T, class Allocator = std::allocator<T> >
class vector
{	
public:	
	typedef Allocator                               		allocator_type;
	typedef typename allocator_type::value_type       		value_type;
	typedef typename allocator_type::reference      		reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer        		pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef ft::vector_iterator<vector<T> > 				iterator;
	typedef ft::vector_iterator<vector<const T> >			const_iterator;
	typedef typename allocator_type::size_type      		size_type;
	typedef typename allocator_type::difference_type		difference_type;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

private:
	pointer		_vector;
	size_type	_size;
	size_type	_capacity;
	Allocator	_allocator;

public:
	vector()
	{
		_allocator = Allocator();
		_init_vector();
	}

	explicit vector(const Allocator& alloc)
	{
		_allocator = alloc;
		_init_vector();
	}

	explicit vector( size_type count, const T value = value_type(),
                 	const Allocator& alloc = Allocator())
	{
		_test_max_size(count);
		_allocator = alloc;
		_init_vector();
		assign(count, value);
	}
	
	vector( const vector& vect )
	{ 
		_init_vector();
		*this = vect;
	}

	template <class Iter>
	 	vector<T>(Iter first, Iter last, const allocator_type& = allocator_type(),
				typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0)
	{
		_init_vector();
		assign(first, last);
	}

	~vector() { if (_vector) { _full_clear(); } }

	vector& operator=(const vector& v)
	{
		this->assign(v.begin(), v.end());
		return *this;
	}

	template <class Iter>
	void assign(Iter first, Iter last, typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0)
	{
		clear();
		insert(begin(), first, last);
	}

	void assign(size_type n, const value_type u)
	{
		if (n <= 0)
			return ;
		clear();
		insert(begin(), n, u);
	}
	
	allocator_type get_allocator() const { return Allocator(); }
	

	// iterator	
	iterator		begin() { return iterator(_vector);}
	const_iterator	begin() const { return const_iterator(_vector); }

	iterator		end() { return iterator(_vector + _size); }
	const_iterator	end() const { return const_iterator(_vector + _size);}
	
	reverse_iterator       rbegin() { return reverse_iterator(end() - 1); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end() - 1); }
	reverse_iterator       rend() { return reverse_iterator(begin() - 1); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin() - 1); }
	// iterator end


	/* Element access */
	reference       operator[](size_type n) // Must not check bounds
	{
		return this->_vector[n];
	}
	const_reference operator[](size_type n) const // Must not check bounds
	{
		return this->_vector[n];
	}

	reference       at(size_type n) // Should not check negative??
	{
		_is_in_bound(n, true);
		return _vector[n];
	}
	
	const_reference at(size_type n) const 
	{
		_is_in_bound(n, true);
		return _vector[n];
	}

	reference       front() { return *_vector; }
	const_reference front() const { return *_vector; }
	reference       back() { return _vector[_size - 1]; }
	const_reference back() const { return _vector[_size - 1]; }

	pointer       data() { return _vector; }
	const_pointer data() const { return _vector; }
	/* Element access end */


	/* Capacity */
	bool 		empty() const	{ return (_size <= 0 ? true : false); }
	size_type	size() const { return _size; }
	size_type	max_size() const { return std::min(TO_SIZE(std::numeric_limits<difference_type>::max()), _allocator.max_size()) ; }
	size_type	capacity() const { return _capacity; }

	void reserve(size_type n) // Not done
	{
		pointer		backup_;
		size_type	i = 0;

		_test_max_size(n);
		if (n > _capacity)
		{
			
			if (max_size() - n > n)
				n *= 2;
			else
				n = max_size();
			backup_ = _allocator.allocate(n);
			if (_vector)
			{
				for (; i < _size && i < n; i++)
					_allocator.construct(&backup_[i], _vector[i]);
				_full_clear();
			}
			_vector = backup_;
			_size = i;
			_capacity = n;
		}	
	}
	/* Capacity end */


	/* Modifier */
	void clear()
	{
		iterator end_ = end();
		iterator begin_ = begin();
		
		if (!_vector || begin_ == end_)
			return ;

		for (; begin_ < end_; begin_++)
		{
			_allocator.destroy(begin_.base());	
		}
		_size = 0;
	}

	iterator insert(iterator pos, const value_type& t)
	{
		size_type i = _get_iterator_i(pos);
		insert(pos, 1, t);

		return begin() + TO_DIFF(i);
		
	}

	void insert(iterator pos, size_type n, const value_type& t)
	{
		iterator end_;

		if (n <= 0)
			return;
		if (_size + n + 1 > _capacity)
			pos = _revalidate_iter(pos, _size + n + 1, &vector::reserve);
		if (!empty())
			_shift_to_end(pos, n);
		end_ = pos + TO_DIFF(n);
		for (; pos < end_; pos++)
		{
			_allocator.construct(pos.base(), t);
		}
		_size += n;
		return ;
	}
	
	template<class Iter>
	void insert(iterator pos, Iter first, Iter last, typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0) // change to input only
	{
		typedef typename ft::iterator_traits<Iter>::iterator_category category;

		_insert(pos, first, last, category());
		return ;
	}

	iterator erase(iterator pos)
	{
		_shift_to_left(pos + 1, 1);
		_size--;
		return pos;
	}
	
	iterator erase(iterator first, iterator last)
	{
		size_type	len;
		
		if (first == last)
			return first;
		len = _get_range_len(first, last);
		_shift_to_left(last, len);
		_size -= TO_SIZE(len);
		return last;
		
	}

	void push_back(const value_type& t)
	{
		insert(end(), t);
	}

	void pop_back()
	{
		if (empty())
			return ;
		_allocator.destroy((end() - 1).base());
		_size--;
	}	

	void resize(size_type sz, value_type value = value_type()) // Not done
	{
		// size_type	i;

		reserve(sz);
		// swap(_vector, _backup); // WARNING : TO-DO
		while (_size > sz)
			_allocator.destroy(&_vector[--_size]);
		if (_size < sz)
			insert(end(), sz - _size, value);
	}

	void swap(vector & other)
	{
		pointer		vector_;
		size_type	size_;
		size_type	capacity_;

		size_ = other.size();
		capacity_ = other.capacity();
		vector_ = other.data();

		other._size = _size;
		other._capacity = _capacity;
		other._vector = _vector;

		_size = size_;
		_capacity = capacity_;
		_vector = vector_;
	}
	
private:
	template<class Iter>
	void _insert(iterator pos, Iter first, Iter last, std::input_iterator_tag)
	{
		while (first != last)
		{
			if (_size + 2 > _capacity)
				pos = _revalidate_iter(pos, _size + 2, &vector::reserve);
			insert(pos++, 1, *first);
			++first;
		}
		return ;
	}

	template<class Iter>
	void _insert(iterator pos, Iter first, Iter last, std::forward_iterator_tag)
	{
		iterator	end_;
		size_type	len = _get_range_len(first, last);

		if (_size + len + 1 >= _capacity)
			pos = _revalidate_iter(pos, _size + len + 1, &vector::reserve);
		_shift_to_end(pos, len);
		end_ = pos + TO_DIFF(len);
		for (; pos < end_; _size++)
		{
			_allocator.construct((pos++).base(), *(first++));
		}
		return ;
	}

	bool	_is_in_bound(size_type n, bool ex = true) const
	{
		if (n < _size && n >= 0)
			return true;
		if (ex)
			throw std::out_of_range("out of bound");
		return false;
	}

	bool	_test_max_size(size_type n)
	{
		if (n > max_size())
			throw std::length_error("out of bound");
		return true;
	}

	void	_init_vector(void)
	{
		_size = 0;
		_capacity = 0;
		_vector = NULL;
	}

	void	_full_clear()
	{
		clear();
		_allocator.deallocate(_vector, _capacity);
		_vector = NULL;
		_capacity = 0;
	}

	void	_shift_to_end(iterator pos, size_type distance) // FIX THIS SHIT
	{
		iterator	end_ = end();
		iterator	rhs;
		iterator	lhs;
		size_type n_shift;

		if (pos == end_)
			return ;
		n_shift = _get_range_len(pos, end_);
		rhs = pos + TO_DIFF(n_shift  + distance) - 1;
		lhs = end_ - 1;
		for (; n_shift > 0 ; n_shift--)
		{
			_allocator.construct(rhs.base(), *(lhs.base()));
			_allocator.destroy(lhs.base());
			rhs--;
			lhs--;
		}
	}

	void	_shift_to_left(iterator pos, size_type distance)
	{
		iterator end_ = end();
		iterator lhs = pos - TO_DIFF(distance);

		for (; lhs < end_ - TO_DIFF(distance); lhs++)
		{
			_allocator.destroy(lhs.base());
			_allocator.construct(lhs.base(), *(lhs + TO_DIFF(distance)).base());
		}
		for (; lhs < end_; lhs++)
			_allocator.destroy(lhs.base());
	}

	void	_reallocate_if_not_null(size_type size, const void * hint = 0)
	{
		if (_vector)
		{
			if (_capacity > size)
				size = _capacity;
			_full_clear();
			_vector = _allocator.allocate(size, hint);	
			_capacity = size;
		}
	}

	size_type	_get_iterator_i(iterator pos)
	{
		if (empty())
			return (0);
		if (pos == end())
			return _size;
		return TO_SIZE(pos.base() - begin().base());
	}

	// Return the equivalent iterator of a re-allocator_type::allocated vector
	iterator	_revalidate_iter(iterator pos, size_type n, void (vector::*f)(size_type))
	{
		size_type i = _get_iterator_i(pos);
		(this->*f)(n);
		return begin() + TO_DIFF(i);
	}

	template <class Iter>
	size_type _get_range_len( const Iter & first, const Iter & last )
	{
		Iter it;

		it = first;
		size_type i = 0;
		for (; it != last; i++)
			it++;
		return i;
	}
};

template< class T, class Alloc >
bool operator==( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{ return !(lhs == rhs); }

template< class T, class Alloc >
bool operator>( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return !(lhs < rhs) && lhs != rhs; }

template< class T, class Alloc >
bool operator<( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class T, class Alloc >
bool operator>=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return !(lhs < rhs); }

template< class T, class Alloc >
bool operator<=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return !(lhs > rhs); }

template< class T, class Alloc>
void swap(vector<T, Alloc> & lhs, vector<T, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}
}  // std

	/*
	iterator invalidation
	swap();
	clear;
	operator=;
	assign;
	reserve;
	shrink_to_fit;
	erase;
	push_back;
	emplace_back;
	insert,emplace;
	resize;
	pop_back;
	*/


#endif
