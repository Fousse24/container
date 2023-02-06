/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iter_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2023/02/03 14:10:53 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "srcs/Tree/rbtree_iterator.hpp"
#include "srcs/Tree/rbtree.hpp"

using std::cout;
using std::endl;

template<class T> 
struct	comp_pair
{
	bool operator()(const T &lhs, const T &rhs) const 
	{
		if (lhs.first < rhs.first)
			return true;
		return false;
	}
};

template<class T>
void print(const T & value)
{
	cout << value << endl;
}

int main() {
	ft::rbtree<int> bst;
	ft::rbtree<int>::iterator	iter;
	


	bst.insert(4);
	bst.insert(7);
	bst.insert(3);
	iter = bst.begin();
	// for (; iter != bst.end(); iter++)
	// {
	// 	cout << *iter << endl;
	// }
	std::for_each(bst.begin(), bst.end(), print<int> );

	ft::rbtree<ft::pair<string, int>, comp_pair<ft::pair<string, int> > > bst_pair;
	ft::rbtree<ft::pair<string, int>, comp_pair<ft::pair<string, int> > >::iterator	iter_pair;
	


	bst_pair.insert(ft::make_pair(string("c"), 2));
	// bst_pair.printTree();
	bst_pair.insert(ft::make_pair(string("e"), 3));
	// bst_pair.printTree();
	bst_pair.insert(ft::make_pair(string("a"), 1));
	// bst_pair.printTree();
	bst_pair.erase(ft::make_pair(string("c"), 2));
	std::for_each(bst_pair.begin(), bst_pair.end(), print<ft::pair<string, int> > );
}

// int main() {
// 	ft::rbtree<ft::pair<string, int> > bst;
// 	ft::rbtree<ft::pair<string, int> >::iterator	iter;
	


// 	bst.insert(ft::make_pair(string("hello"), 2));
// 	bst.insert(ft::make_pair(string("ello"), 3));
// 	bst.insert(ft::make_pair(string("llo"), 1));
// 	iter = bst.begin();
// 	for (; iter != bst.end(); iter++)
// 	{
// 		cout << *iter << endl;
// 	}
// 	std::for_each(bst.begin(), bst.end(), print<ft::pair<string, int> > );
// }
