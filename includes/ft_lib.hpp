/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:32:19 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/19 10:34:35 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIB_HPP
#define FT_LIB_HPP

namespace ft {

// compare the values of 2 range of iterators
template <class It1, class It2>
bool	lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2)
{
	while ((first1 != last1) && (first2 != last2))
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
		++first1;
		++first2;
	}
  return (first1 == last1) && (first2 != last2);
}

template <class It1, class It2, class Compare>
bool	lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2, Compare comp)
{
	while ((first1 != last1) && (first2 != last2))
	{
		if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
		*first1++;
		*first2++;
	}
  return (first1 == last1) && (first2 != last2);
}

template <class It1, class It2>
bool	equal(It1 first1, It1 last1, It2 first2)
{
	for (; first1 != last1; ++first1, ++first2) 
	{
        if (*first1 != *first2) 
            return false;
	}
    return true;
}

}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) 
	{
        if (!p(*first1, *first2)) 
		{
            return false;
        }
    }
    return true;
}

#endif
