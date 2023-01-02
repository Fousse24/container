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

    bst.printTree();

}