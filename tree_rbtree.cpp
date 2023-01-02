/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2022/09/13 11:43:57 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/Tree/rbtree.hpp"

using std::cout;
using std::endl;


int main() {
	ft::RBTree<int> bst;
	cout << "1 insert" << endl;
	bst.insert(55);
	cout << "2 insert" << endl;
	bst.insert(40);
	cout << "3 insert" << endl;
	bst.insert(65);
	cout << "4 insert" << endl;
	bst.insert(60);
	cout << "5 insert" << endl;
	bst.insert(75);
	cout << "6 insert" << endl;
	bst.insert(57);

	bst.print_tree();
	cout << endl << "1 deleting 40" << endl;
	bst.delete_node(40);
	bst.print_tree();
	cout << endl << "2 deleting something that isn't there" << endl;
	bst.delete_node(3);
	bst.print_tree();
	cout << endl << "3 deleting everything" << endl;
	cout << endl << "3-1 deleting 55" << endl;
	bst.delete_node(55);
	bst.print_tree();
	cout << endl << "3-2 deleting 65" << endl;
	bst.delete_node(65);
	bst.print_tree();
	cout << endl << "3-3 deleting 75" << endl;
	bst.delete_node(75);
	bst.print_tree();
	cout << endl << "3-4 deleting 57" << endl;
	bst.delete_node(57);
	bst.print_tree();
	cout << endl << "3-5 deleting 60" << endl;
	bst.delete_node(60);
	bst.print_tree();

	cout << "1 insert 55" << endl;
	bst.insert(55);
	cout << "2 insert 40" << endl;
	bst.insert(40);
	cout << "3 insert 65" << endl;
	bst.insert(65);
	cout << "4 insert 60" << endl;
	bst.insert(60);
	cout << "5 insert 75" << endl;
	bst.insert(75);
	cout << "6 insert 57" << endl;
	bst.insert(57);
	bst.print_tree();

	cout << endl << "After deleting 40" << endl;
  bst.delete_node(40);
  bst.print_tree();

}