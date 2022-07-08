/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/08 17:08:25 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include "vectorIterator.hpp"
#include "IteratorTraits.hpp"
#include "utils.hpp"

#define FT_VECT_BUFFER	10

#define TO_TYPE(X, T) (static_cast<T>(X))

/*
	vector synopsis
*/
namespace ft
{
//using std::initializer_list;
using std::allocator_traits;

template <class T, class Allocator = std::allocator<T> >
class vector
{	
public:	
	typedef Allocator                               		allocator_type;
	typedef typename allocator_type::value_type       		value_type;
	typedef typename allocator_type::reference      		reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef ft::vectorIterator<vector<T> > 				iterator;
	typedef const ft::vectorIterator<vector<T> >			const_iterator;
	typedef typename allocator_type::size_type      		size_type;
	typedef typename allocator_type::difference_type		difference_type;
	typedef typename allocator_type::pointer        		pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	vector()
	{
		_allocator = Allocator();
		_size = 0;
		_capacity = 0;
		_vector = NULL;
	};

	explicit vector(const Allocator& alloc)
	{
		_size = 0;
		_capacity = 0;
		_allocator = alloc;
		_vector = NULL;
	};
	
	vector( const vector& vect )
	{ 
		*this = vect;
	};

	// template <class Iterator>
	//  	vector<T>(Iterator first, Iterator last, const allocator_type& = allocator_type()){};

	// explicit vector<T>( size_type count, const T& value = T(), const Allocator& alloc = Allocator()){};
		

	~vector() { clear(); };

	vector& operator=(const vector& v)
	{
		if (_vector)
			_full_clear();
		this->assign(v.begin(), v.end());
		return *this;
	};

	


	// template <class Input_It>
	void assign(iterator first, iterator last)
	{
		clear();
		reserve(_get_range_len(first, last));
		_pure_insert(begin(), end(), first, last);
	};

	void assign(size_type n, const value_type& u)
	{
		clear();
		for (size_type i = 0; i < n; i++)
			this->_vector[i] = u;
		_size = n;
	};
	
	allocator_type get_allocator() const { return Allocator(); };
	

	// iterator	
	iterator		begin() { return iterator(_vector);};
	const_iterator	begin() const { return const_iterator(_vector); };

	iterator		end() { return iterator(_vector + _size); };
	const_iterator	end() const { return iterator(_vector + _size);};
	
	reverse_iterator       rbegin() { return reverse_iterator(end() - 1); };
	const_reverse_iterator rbegin() const { return reverse_iterator(end() - 1); };
	reverse_iterator       rend() { return reverse_iterator(begin() - 1); };
	const_reverse_iterator rend() const { return reverse_iterator(begin() - 1); };
	// iterator end


	/* Element access */
	reference       operator[](size_type n) // Must not check bounds
	{
		return this->_vector[n];
	};
	const_reference operator[](size_type n) const // Must not check bounds
	{
		return this->_vector[n];
	};

	reference       at(size_type n) // Should not check negative??
	{
		_is_in_bound(n);
		return _vector[n];
	};
	const_reference at(size_type n) const 
	{
		_is_in_bound(n);
		return _vector[n];
	};

	reference       front() { return *begin(); };
	const_reference front() const { return *begin(); };
	reference       back() { return *(end() - 1); };
	const_reference back() const { return *(end() - 1); };

	value_type*       data() { return _vector; };
	const value_type* data() const { return _vector; };
	/* Element access end */


	/* Capacity */
	bool 		empty() const	{ return (_size <= 0 ? true : false); };
	size_type	size() const { return _size; };
	size_type	max_size() const { return std::numeric_limits<size_type>::max(); };
	size_type	capacity() const { return _capacity; };

	void reserve(size_type n) // Not done
	{
		pointer		backup_;
		size_type	i;

		_test_max_size(n);
		if (n > _capacity)
		{
			backup_ = _allocator.allocate(n);
			// swap(_vector, _backup); // WARNING : TO-DO
			// std::swap(backup_, _vector);
			
			for (i = 0; i < _size && i < n; i++)
				backup_[i] = _vector[i];
			_full_clear();
			_vector = backup_;
			_size = i;
			_capacity = n;
		}		
	};
	/* Capacity end */


	/* Modifier */
	void clear()
	{
		if (!_vector)
			return ;
		iterator end_ = end();
		iterator begin_ = begin();
		for (; begin_ < end_; begin_++)
			_allocator.destroy(begin_.base());
		_size = 0;
	};

	iterator insert(iterator pos, const value_type& t)
	{
		size_type i = _get_iterator_i(pos);
		insert(pos, TO_TYPE(1, size_type), t);
		return begin() + TO_TYPE(i, difference_type);
		
	};

	void insert(iterator pos, size_type n, const value_type& t)
	{
		iterator end_;
		iterator begin_;

		if (_size + n > _capacity)
			pos = _revalidate_iter(pos, _size + n + FT_VECT_BUFFER, &vector::reserve);
		if (begin() != end())
			_shift_to_end(pos, TO_TYPE(n, difference_type));
		end_ = pos + TO_TYPE(n, difference_type);
		begin_ = pos;
		for (; pos < end_; pos++)
			_allocator.construct(pos.base(), t);
		_size += n;
		return ;
	};
	
	template<class Iter>
	void insert(iterator pos, Iter first, Iter last, typename ft::enable_if<ft::is_not_integral<Iter>, bool>::type = 0) // change to input only
	{
		iterator		end_;
		difference_type	len = _get_range_len(first, last);

		if (_size + TO_TYPE(len, size_type) >= _capacity)
			pos = _revalidate_iter(pos, _size + TO_TYPE(len, size_type) + FT_VECT_BUFFER, &vector::reserve);
		_shift_to_end(pos, len);
		end_ = pos + len;
		// std::copy(first, last, pos);
		for (; pos < end_; _size++)	
			_allocator.construct((pos++).base(), *(first++));
		return ;
	};

	iterator erase(iterator pos)
	{
		iterator	it;
		iterator	end_;

		_shift_to_left(pos, pos);
		_size--;
		return pos;
	};
	
	iterator erase(iterator first, iterator last)
	{
		// iterator		end_ = end();
		difference_type	len = _get_range_len(first, last);
		
		_shift_to_left(last, len);
		_size -= TO_TYPE(len, size_type);
		return last;
		
	};

	void push_back(const value_type& t)
	{
		insert(end(), t);
	};

	void pop_back()
	{
		_allocator.destroy((end() - 1).base());
		_size--;
	};	

	void resize(size_type sz, value_type value = value_type()) // Not done
	{
		// size_type	i;

		reserve(sz);
		// swap(_vector, _backup); // WARNING : TO-DO
		while (_size > sz)
			_allocator.destroy(&_vector[--_size]);
		if (_size < sz)
			insert(end(), sz - _size, value);
	};

	void swap(vector & other)
	{
		pointer temp = _vector;
		_vector = other.data();
		other.data() = temp;
	}
	
private:
	pointer		_vector;
	size_type	_size;
	size_type	_capacity;
	Allocator	_allocator;

	void	_pure_insert(iterator dst_first, iterator dst_last, iterator src_first, iterator src_last)
	{
		while (dst_first < dst_last || src_first < src_last)
			*(dst_first++).base() = *(src_first++).base();
	};

	bool	_is_in_bound(size_type n, bool ex)
	{
		if (n < _size)
			return true;
		if (ex)
			throw std::length_error("out of bound");
		return false;
	};

	bool	_test_max_size(size_type n)
	{
		if (n > max_size())
			throw std::length_error("out of bound");
		return true;
	};

	void	_move_to(iterator dst, iterator src_first, iterator src_last)
	{
		while (src_first <= src_last)
			*(dst++) = *(src_first++);
	};

	void	_full_clear()
	{
		clear();
		_allocator.deallocate(_vector, _capacity);
		_vector = NULL;
		_capacity = 0;
	};

	void	_shift_to_end(iterator pos, difference_type distance)
	{
		iterator end_ = end();
		iterator rhs;

		// std::uninitialized_copy(rhs - distance, rhs, rhs);
		// std::uninitialized_copy(rhs - distance, rhs, rhs);
		for (rhs = end_ + distance - 1; rhs >= end(); rhs--)
			_allocator.construct(rhs.base(), *(rhs - distance).base()); 
		for (; rhs >= pos + distance; rhs--)
		{
			_allocator.destroy(rhs.base());
			_allocator.construct(rhs.base(), *(rhs - distance).base()); 
		}
	};

	void	_shift_to_left(iterator pos, difference_type distance)
	{
		iterator end_ = end();
		iterator lhs = pos - distance;

		std::cout << "lhs : " << *lhs << " distance : " << distance << " begin : " << *(pos).base() << std::endl;
		for (; lhs < end_ - distance; lhs++)
		{
			_allocator.destroy(lhs.base());
			_allocator.construct(lhs.base(), *(lhs + distance).base());
		}
		for (; lhs < end_; lhs++)
			_allocator.destroy(lhs.base());
	};

	void	_reallocate_if_not_null(size_type size, const void * hint = 0)
	{
		if (_vector)
		{
			size += FT_VECT_BUFFER;
			if (_capacity > size)
				size = _capacity;
			_full_clear();
			_vector = _allocator.allocate(size, hint);	
			_capacity = size;
		}
	};

	size_type	_get_iterator_i(iterator pos)
	{
		if (empty())
			return (0);
		return static_cast<size_type>(pos.base() - begin().base());
	};

	// Return the equivalent iterator of a re-allocator_type::allocated vector
	iterator	_revalidate_iter(iterator pos, size_type n, void (vector::*f)(size_type))
	{
		size_type i = _get_iterator_i(pos);
		(this->*f)(n);
		return begin() + TO_TYPE(i, difference_type);
	};

	template <class Iter>
	difference_type _get_range_len( const Iter & first, const Iter & last )
	{
		Iter it;

		it = first;
		difference_type i = 0;
		for (; it != last; i++)
			it++;
		return i;
	};
	// void	_pure_insert(iterator pos, iterator dst_last, iterator src_first, iterator src_last)
	// {
	// 	while (dst_first < dst_last || src_first < src_last)
	// 		*(dst_first++).base() = *(src_first++).base();
	// }
	//bool __invariants() const;
	/* Modifier end */
};

template< class T, class Alloc >
bool operator==( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (std::equal(lhs.begin(), lhs.end(), rhs.begin));
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{ return !(lhs == rhs); }

template< class T, class Alloc >
bool operator>( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return !(lhs < rhs); }

template< class T, class Alloc >
bool operator<( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return (std::lexicographical_compare(lhs.base(), lhs.end(). rhs.base(), rhs.end())); }

template< class T, class Alloc >
bool operator>=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return (lhs > rhs || lhs == rhs); }

template< class T, class Alloc >
bool operator<=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>&rhs)
{ return !(lhs > rhs); }


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
// template <class V>
// 	class Iterator : ft::iterator<ft::random_access_iterator_tag, V>
// 	{
// 	protected:
// 		pointer	_ptr;
		
// 	public:
// 		Iterator<V>() {  };

// 		Iterator<V>(pointer ptr) { this->_ptr = ptr; }

// 		Iterator<V>(const Iterator<V>& it) { *this = it; };
		
// 		~Iterator<V>() {  };

// 		Iterator<V>& operator=( const Iterator<V>& it )
// 		{
// 			_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
// 			return *this;
// 		}

// 		pointer	base() 					{ return _ptr; };
// 		value_type operator*() const	{ return *_ptr; };

// 		Iterator<V>& operator++()		{ _ptr++; return *this; }
// 		Iterator<V>& operator--() 		{ _ptr--; return *this;	}

// 		Iterator<V> operator+(int n)	{ return Iterator<V>(this->_ptr + n); }
// 		Iterator<V> operator-(int n)	{ return Iterator<V>(this->_ptr - n); }

// 		Iterator<V>& operator+=(int n)	{ this->_ptr += n; return *this; }
// 		Iterator<V>& operator-=(int n)	{ this->_ptr -= n; return *this; }
		
// 		const Iterator<V>& operator++( int )
// 		{
// 			Iterator<V> ori = *this;
// 			++(*this);
// 			return ori;
// 		}
// 		const Iterator<V>& operator--( int )
// 		{
// 			Iterator<V> ori = *this;
// 			--(*this);
// 			return ori;
// 		}
		
// 		bool operator==(const Iterator<V>& it) const
// 		{
// 			if (this->_ptr == it._ptr)
// 				return true;  
// 			return false;
// 		}
// 		bool operator!=(const Iterator<V>& it) const	{ return (!operator==(it)); }
// 		bool operator>(const Iterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); }
// 		bool operator<(const Iterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); }
// 		bool operator>=(const Iterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); }
// 		bool operator<=(const Iterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); }

// 		value_type operator[](size_type i)
// 		{
// 			return (base() + i);
// 		}

// template <class V>
// 	class RandomAccessIterator : 
// 	{
// 	public:
// 		// typedef typename ft::iterator<std::random_access_iterator_tag, V>::value_type		value_type;
// 		// typedef typename ft::iterator<std::random_access_iterator_tag, V>::pointer			pointer;
// 		// typedef typename ft::iterator<std::random_access_iterator_tag, V>::reference			reference;
// 		// typedef typename ft::iterator<std::random_access_iterator_tag, V>::difference_type	difference_type;
// 		// typedef typename V::size_type														size_type;
// 		typedef typename V::value_type		value_type;
// 		typedef typename ft::iterator<std::random_access_iterator_tag, V>::pointer			pointer;
// 		typedef typename ft::iterator<std::random_access_iterator_tag, V>::reference			reference;
// 		typedef typename ft::iterator<std::random_access_iterator_tag, V>::difference_type	difference_type;
// 		typedef typename V::size_type														size_type;

// 		RandomAccessIterator<V>() {  };

// 		RandomAccessIterator<V>(pointer ptr) { this->_ptr = ptr; }

// 		RandomAccessIterator<V>(const RandomAccessIterator<V>& it) { *this = it; };
		
// 		virtual ~RandomAccessIterator<V>() {  };

// 		virtual RandomAccessIterator<V>& operator=( const RandomAccessIterator<V>& it )
// 		{
// 			this->_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
// 			return *this;
// 		}

// 		virtual pointer	base() 					{ return this->_ptr; };
// 		virtual value_type operator*() const	{ return *this->_ptr; };

// 		virtual RandomAccessIterator<V>& operator++()		{ this->_ptr++; return *this; }
// 		virtual RandomAccessIterator<V>& operator--() 		{ this->_ptr--; return *this;	}

// 		virtual RandomAccessIterator<V> operator+(size_type n)	{ return RandomAccessIterator<V>(this->_ptr + n); }
// 		virtual RandomAccessIterator<V> operator-(size_type n)	{ return RandomAccessIterator<V>(this->_ptr - n); }

// 		virtual RandomAccessIterator<V>& operator+=(size_type n)	{ this->_ptr += n; return *this; }
// 		virtual RandomAccessIterator<V>& operator-=(size_type n)	{ this->_ptr -= n; return *this; }
		
// 		virtual RandomAccessIterator<V> operator++( int )
// 		{
// 			RandomAccessIterator<V> ori = *this;
// 			++(*this);
// 			return ori;
// 		}
// 		virtual RandomAccessIterator<V> operator--( int )
// 		{
// 			RandomAccessIterator<V> ori = *this;
// 			--(*this);
// 			return ori;
// 		}
		
// 		virtual bool operator==(const RandomAccessIterator<V>& it) const
// 		{
// 			if (this->_ptr == it._ptr)
// 				return true;  
// 			return false;
// 		}
// 		virtual bool operator!=(const RandomAccessIterator<V>& it) const	{ return (!operator==(it)); }
// 		virtual bool operator>(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); }
// 		virtual bool operator<(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); }
// 		virtual bool operator>=(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); }
// 		virtual bool operator<=(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); }

// 		virtual value_type operator[](int i)
// 		{
// 			return (*(base() + i));
// 		}
