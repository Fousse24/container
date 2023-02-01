/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2022/09/01 11:10:57 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "srcs/Tree/rbtree_iterator.hpp"
#include "srcs/Tree/rbtree.hpp"

using std::cout;
using std::endl;

template<class T>
void print(const T & value)
{
	cout << value << endl;
}

int main() {
	ft::RBTree<int> bst;
	ft::RBTree<int>::iterator	iter;
	


	bst.insert(4);
	bst.insert(7);
	bst.insert(3);
	iter = bst.begin();
	// for (; iter != bst.end(); iter++)
	// {
	// 	cout << *iter << endl;
	// }
	std::for_each(bst.begin(), bst.end(), print<int> );

	ft::RBTree<ft::pair<string, int> > bst_pair;
	ft::RBTree<ft::pair<string, int> >::iterator	iter_pair;
	


	bst_pair.insert(ft::make_pair(string("hello"), 2));
	bst_pair.printTree();
	bst_pair.insert(ft::make_pair(string("ello"), 3));
	bst_pair.printTree();
	bst_pair.insert(ft::make_pair(string("llo"), 1));
	bst_pair.printTree();
	iter_pair = bst_pair.begin();
	for (; iter_pair != bst_pair.end(); iter_pair++)
	{
		cout << *iter_pair << endl;
	}
	std::for_each(bst_pair.begin(), bst_pair.end(), print<ft::pair<string, int> > );
}

// int main() {
// 	ft::RBTree<ft::pair<string, int> > bst;
// 	ft::RBTree<ft::pair<string, int> >::iterator	iter;
	


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
