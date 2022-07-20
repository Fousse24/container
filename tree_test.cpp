/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/20 17:49:16 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "rb_tree.hpp"

using std::cout;
using std::endl;


int main() {
	ft::rb_tree<int> bst;
	bst.insert(55);
	bst.insert(40);
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);

	bst.print_tree();
	cout << endl << "After deleting" << endl;
	bst.delete_node(40);
	bst.print_tree();
}