/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/05 14:54:31 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include <memory>
#include <limits>

namespace ft
{
	struct iterator_tag {  };
	struct input_iterator_tag : public iterator_tag {  };
	struct output_iterator_tag : public iterator_tag {  };
	struct forward_iterator_tag : public input_iterator_tag {  };
	struct bidirectional_iterator_tag : public forward_iterator_tag {  };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {  };
	
	template< class T>
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::difference_type 	difference_type;
	};

	template< class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	// template< class Iter >
	// struct iterator_traits
	// {
	// 	typedef typename Iter::difference_type		difference_type;
	// 	typedef typename Iter::value_type			value_type;
	// 	typedef typename Iter::pointer				pointer;
	// 	typedef typename Iter::reference			reference;
	// 	typedef typename Iter::iterator_category	iterator_category;
	// };

	// template< class Iter >
	// struct iterator_traits< const Iter >
	// {
	// 	typedef typename Iter::difference_type		difference_type;
	// 	typedef typename Iter::value_type			value_type;
	// 	typedef typename Iter::pointer				pointer;
	// 	typedef typename Iter::reference			reference;
	// 	typedef typename Iter::iterator_category	iterator_category;
	// };

	// template< class T>
	// struct iterator_traits<T*>
	// {
	// 	typedef std::ptrdiff_t					difference_type;
	// 	typedef T								value_type;
	// 	typedef T*								pointer;
	// 	typedef T&								reference;
	// 	typedef ft::random_access_iterator_tag	iterator_category;
	// };

	//template< typename T >
	template <class Category, class T>
	class iterator
	{
	public:
		typedef typename T::value_type			value_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
		typedef Category						iterator_category;
		typedef typename T::difference_type 	difference_type;

	protected:
		pointer	_ptr;
	};

	template <class V>
	class RandomAccessIterator : public ft::iterator<ft::random_access_iterator_tag, V>
	{
	public:
		// typedef typename ft::iterator<ft::random_access_iterator_tag, V>::value_type		value_type;
		// typedef typename ft::iterator<ft::random_access_iterator_tag, V>::pointer			pointer;
		// typedef typename ft::iterator<ft::random_access_iterator_tag, V>::reference			reference;
		// typedef typename ft::iterator<ft::random_access_iterator_tag, V>::difference_type	difference_type;
		// typedef typename V::size_type														size_type;
		typedef typename V::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, V>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, V>::reference			reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, V>::difference_type	difference_type;
		typedef typename V::size_type														size_type;

		RandomAccessIterator<V>() {  };

		RandomAccessIterator<V>(pointer ptr) { this->_ptr = ptr; }

		RandomAccessIterator<V>(const RandomAccessIterator<V>& it) { *this = it; };
		
		virtual ~RandomAccessIterator<V>() {  };

		virtual RandomAccessIterator<V>& operator=( const RandomAccessIterator<V>& it )
		{
			this->_ptr = it._ptr; // WARNING : Might need a change https://cplusplus.com/reference/iterator/
			return *this;
		}

		virtual pointer	base() 					{ return this->_ptr; };
		virtual value_type operator*() const	{ return *this->_ptr; };

		virtual RandomAccessIterator<V>& operator++()		{ this->_ptr++; return *this; }
		virtual RandomAccessIterator<V>& operator--() 		{ this->_ptr--; return *this;	}

		virtual RandomAccessIterator<V> operator+(size_type n)	{ return RandomAccessIterator<V>(this->_ptr + n); }
		virtual RandomAccessIterator<V> operator-(size_type n)	{ return RandomAccessIterator<V>(this->_ptr - n); }

		virtual RandomAccessIterator<V>& operator+=(size_type n)	{ this->_ptr += n; return *this; }
		virtual RandomAccessIterator<V>& operator-=(size_type n)	{ this->_ptr -= n; return *this; }
		
		virtual RandomAccessIterator<V> operator++( int )
		{
			RandomAccessIterator<V> ori = *this;
			++(*this);
			return ori;
		}
		virtual RandomAccessIterator<V> operator--( int )
		{
			RandomAccessIterator<V> ori = *this;
			--(*this);
			return ori;
		}
		
		virtual bool operator==(const RandomAccessIterator<V>& it) const
		{
			if (this->_ptr == it._ptr)
				return true;  
			return false;
		}
		virtual bool operator!=(const RandomAccessIterator<V>& it) const	{ return (!operator==(it)); }
		virtual bool operator>(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr > rhs._ptr ? true : false); }
		virtual bool operator<(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr < rhs._ptr ? true : false); }
		virtual bool operator>=(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr >= rhs._ptr ? true : false); }
		virtual bool operator<=(const RandomAccessIterator<V>& rhs) const	{ return (this->_ptr <= rhs._ptr ? true : false); }

		virtual value_type operator[](int i)
		{
			return (*(base() + i));
		}
	};
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
	// 		iterator<T>::iterator_category = ft::random_access_iterator_tag();
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
}
#endif
