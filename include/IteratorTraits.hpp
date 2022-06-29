/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:30 by sfournie          #+#    #+#             */
/*   Updated: 2022/06/24 14:45:51 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include "headers.hpp"


namespace ft
{
	struct input_iterator_tag {  };
	struct output_iterator_tag {  };
	struct forward_iterator_tag : public input_iterator_tag {  };
	struct bidirectional_iterator_tag : public forward_iterator_tag {  };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {  };
	
	template< class T>
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::pointer_type		pointer_type;
		typedef typename T::reference_type		reference_type;
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
}
#endif
