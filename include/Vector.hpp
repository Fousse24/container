/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/06/27 17:25:52 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "headers.hpp"
#include "Iterator.hpp"
#include <initializer_list>
#include <limits>

#define FT_VECT_BUFFER	10

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
	template <class V>
	class Iterator;
	
	typedef T                                       	value_type;
	typedef Allocator                               	allocator_type;
	typedef typename allocator_type::reference      	reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef Iterator<vector<T> > 				        iterator;
	typedef const Iterator<vector<T> >					const_iterator;
	typedef typename allocator_type::size_type      	size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::pointer        	pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	// typedef ft::reverse_iterator<iterator>				reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	
	template <class V>
	class Iterator : ft::iterator<ft::random_access_iterator_tag, V>
	{
	protected:
		pointer	_ptr;
		
	public:
		Iterator<V>() {  };

		Iterator<V>(pointer ptr) { this->_ptr = ptr; }

		Iterator<V>(const Iterator<V>& it) { *this = it; };
		
		~Iterator<V>() {  };

		Iterator<V>& operator=( const Iterator<V>& it )
		{
			_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
			return *this;
		}

		pointer	base() 					{ return _ptr; };
		value_type operator*() const	{ return *_ptr; };

		Iterator<V>& operator++()		{ _ptr++; return *this; }
		Iterator<V>& operator--() 		{ _ptr--; return *this;	}

		Iterator<V> operator+(int n)	{ return Iterator<V>(this->_ptr + n); }
		Iterator<V> operator-(int n)	{ return Iterator<V>(this->_ptr - n); }

		Iterator<V>& operator+=(int n)	{ this->_ptr += n; return *this; }
		Iterator<V>& operator-=(int n)	{ this->_ptr -= n; return *this; }
		
		const Iterator<V>& operator++( int )
		{
			Iterator<V> ori = *this;
			++(*this);
			return ori;
		}
		const Iterator<V>& operator--( int )
		{
			Iterator<V> ori = *this;
			--(*this);
			return ori;
		}
		
		bool operator==(const Iterator<V>& it) const
		{
			if (this->_ptr == it._ptr)
				return true;  
			return false;
		}
		bool operator!=(const Iterator<V>& it) const	{ return (!operator==(it)); }
		bool operator>(const Iterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); }
		bool operator<(const Iterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); }
		bool operator>=(const Iterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); }
		bool operator<=(const Iterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); }

		value_type operator[](size_type i)
		{
			return (base() + i);
		}
	};

	vector<T>()
	{
		this->_size = 0;
		this->_capacity = 0;
		// allocator_type = Allocator();
	};

	explicit vector<T>(const Allocator& alloc)
	{
		this->size = 0;
		this->_capacity = 0;
		this->allocator_type = alloc;
		//this->value_type = allocator_type::value_type;
	};

	// explicit vector<T>(size_type n)   //c++11
	// {
	// 	_vector = new value_type[n];
	// 	_size = 0;
	// 	_capacity = n;
	// }
	
	vector<T>( const vector& vect ){  };

	// template <class Iterator>
	//  	vector<T>(Iterator first, Iterator last, const allocator_type& = allocator_type()){};

	// explicit vector<T>( size_type count, const T& value = T(), const Allocator& alloc = Allocator()){};
		

	~vector<T>() {};

	// vector& operator=(const vector& x);


	template <class Input_It>
	void assign(Input_It first, Input_It last)
	{
		while (first <= last && last
			first
	};

	void assign(size_type n, const value_type& u)
	{
		for (int i = 0; i < n; i++)
			this->_vector[i] = u;
	};
	
	allocator_type get_allocator() const { return Allocator(); };
	

	// iterator	
	iterator		begin() { return iterator(_vector);};
	const_iterator	begin() const { return const_iterator(_vector); };

	iterator		end() { return iterator(_vector) + _size; };
	const_iterator	end() const { return iterator(_vector) + _size;};
	
	// reverse_iterator       rbegin() noexcept;
	// const_reverse_iterator rbegin()  const noexcept;
	// reverse_iterator       rend() noexcept;
	// const_reverse_iterator rend()    const noexcept;
	
	const_iterator	cbegin() const { return const_iterator(_vector); };
	const_iterator	cend() const { return const_iterator(_vector) + _size; };
	// const_reverse_iterator crbegin() const noexcept;
	// const_reverse_iterator crend()   const noexcept;
	// iterator end


	/* Element access */
	reference       operator[](size_type n)
	{
		return this->_vector[n];
	};
	const_reference operator[](size_type n) const
	{
		return this->_vector[n];
	};

	reference       at(size_type n);
	const_reference at(size_type n) const;

	reference       front() { return _vector[0]; };
	const_reference front() const { return _vector[0]; };
	reference       back() { return _vector[_size - 1]; };
	const_reference back() const { return _vector[_size - 1]; };

	value_type*       data();
	const value_type* data() const;
	/* Element access end */


	/* Capacity */
	bool empty() const	{ return (_size <= 0 ? true : false); };

	size_type size() const
	{
		return _size;
	};

	size_type max_size() const
	{
		return std::numeric_limits<size_type>::max();
	};

	size_type capacity() const
	{
		return _capacity;
	};
	
	void reserve(size_type n)
	{
		if (n > this->max_size())
			throw std::length_error("asked size if above the maximum possible");
		
	};

	void shrink_to_fit();
	/* Capacity end */


	/* Modifier */
	void push_back(const value_type& x)
	{
		if (_capacity <= _size)
		{
			this->resize(_capacity + FT_VECT_BUFFER);
		}
		_vector[_size++] = x;
	};

	void pop_back();

	iterator insert(const_iterator position, const value_type& x);
	iterator insert(const_iterator position, size_type n, const value_type& x);
	template <class Iterator>
		iterator insert(const_iterator position, Iterator first, Iterator last);
	//iterator insert(const_iterator position, std::initializer_list<value_type> il);

	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);

	void clear();

	void resize(size_type sz)
	{
		value_type	*_backup = _vector;
		size_type i;

		_backup = _vector;
		_vector = new value_type[sz];
		for (i = 0; i < _size && i < sz; i++)
			_vector[i] = _backup[i];
		_size = i;
		_capacity = sz;
		delete [] _backup;
	};
	
	void resize(size_type sz, const value_type& c);

	void swap(vector&);
private:
	value_type	*_vector;
	size_type	_size;
	size_type	_capacity;
	//bool __invariants() const;
	/* Modifier end */
};

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
