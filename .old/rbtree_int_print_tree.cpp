/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_int_print_tree.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2023/02/03 14:10:53 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "rbtree.hpp"

using std::cout;
using std::cin;
using std::endl;


int main() {
	rbtree bst;
	int input = -1;

	while (input)
	{
		cout << "insert number: ";
		cin >> input;
		if (input) {
			bst.insert(input);
			bst.printTree();
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
	// bst.printTree();
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


	// bst.insert(40);
	// bst.insert(20);
	// bst.insert(10);
	// bst.insert(30);
	// bst.insert(25);
	// bst.insert(5);
	// bst.insert(35);
	// bst.insert(55);
	// bst.insert(45);
	// bst.insert(50);
	// bst.insert(52);
	// bst.insert(60);
	// bst.insert(37);
	// bst.insert(15);
	// bst.insert(17);
	// bst.printTree();

	// bst.insert(11);
	// bst.insert(6);
	// bst.insert(8);
	// bst.insert(19);
	// bst.insert(4);
	// bst.insert(10);
	// bst.insert(5);
	// bst.insert(17);
	// bst.insert(43);
	// bst.insert(49);
	// bst.insert(31);
	// bst.printTree();

	bst.insert(50);
	bst.insert(15);
	bst.insert(20);
	
	bst.insert(35);
	bst.insert(65);
	bst.insert(70);
	bst.insert(80);
	bst.insert(68);
	bst.insert(90);
	bst.printTree();

	input = -1;
	while (input)
	{
		cout << "delete number: ";
		cin >> input;
		if (input) {
			bst.erase(input);
			bst.printTree();
		}
	}

    bst.printTree();

}