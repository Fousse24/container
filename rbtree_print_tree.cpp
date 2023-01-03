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
using std::cin;
using std::endl;


int main() {
	RBTree bst;
	int input = -1;

	while (input)
	{
		cout << "number: ";
		cin >> input;
		if (input) {
			bst.insert(input);
		}
	}

	// bst.insert(10);
	// bst.printTree();
	// bst.insert(18);
	// bst.printTree();
	// bst.insert(7);
	// bst.printTree();
	// bst.insert(15);
	// bst.printTree();
	// bst.insert(16);
	// bst.printTree();
	// bst.insert(30);
	// bst.printTree();
	// bst.insert(25);
	// bst.printTree();
	// bst.insert(40);
	// bst.printTree();
	// bst.insert(60);
	// bst.printTree();
	// bst.insert(2);
	// bst.printTree();
	// bst.insert(1);
	// bst.printTree();
	// bst.insert(70);
	// bst.insert(2);
	// bst.printTree();
	// bst.insert(85);
	// bst.printTree();
	// bst.insert(90);
	// bst.printTree();
	// bst.insert(95);
	// bst.printTree();
	// bst.insert(105);
	// bst.printTree();
	// bst.insert(100);
	// bst.printTree();
	// bst.insert(110);
	// bst.printTree();
	// bst.insert(120);
	// bst.printTree();
	// bst.insert(115);


	// bst.insert(50);
	// bst.printTree();
	// bst.insert(28);
	// bst.printTree();
	// bst.insert(19);
	// bst.printTree();
	// bst.insert(30);
	// bst.printTree();
	// bst.insert(29);
	// bst.insert(17);
	// bst.insert(42);
	// bst.insert(200);
	// bst.insert(160);
	// bst.insert(170);
	// bst.insert(180);
	// bst.insert(240);
	// bst.insert(44);
	// bst.insert(26);
	// bst.insert(27);

    bst.printTree();

}