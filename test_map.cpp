/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:47:33 by sfournie          #+#    #+#             */
/*   Updated: 2022/09/01 17:19:40 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <map>

#include "includes/pair.hpp"
#include "srcs/Map/map.hpp"
#include "includes/test.hpp"

using std::cout;
using std::endl;
using std::string;


int main() {
	ft::map<string, int> map;
	// std::map<string, int> map_std;
	cout << "1 insert" << endl;
	// map.insert(ft::make_pair(string("first"), 1));
	// cout << "2 insert" << endl;
	// map.insert(ft::make_pair(string("second"), 2));
	// cout << "3 insert" << endl;
	// map.insert(ft::make_pair(string("third"), 3));
	// cout << "4 insert" << endl;
	// map.insert(ft::make_pair(string("fourth"), 4));
	// cout << "5 insert" << endl;
	// map.insert(ft::make_pair(string("fifth"), 5));
	// cout << "6 insert" << endl;
	// map.insert(ft::make_pair(string("sixth"), 6));

	map.insert(ft::make_pair(string("1"), 21));
	cout << "2 insert" << endl;
	map.insert(ft::make_pair(string("2"), 12));
	cout << "3 insert" << endl;
	map.insert(ft::make_pair(string("3"), 43));
	cout << "4 insert" << endl;
	map.insert(ft::make_pair(string("4"), 34));
	cout << "5 insert" << endl;
	map.insert(ft::make_pair(string("5"), 15));
	cout << "6 insert" << endl;
	map.insert(ft::make_pair(string("6"), 26));
	cout << "7 insert" << endl;
	map.insert(ft::make_pair(string("7"), 1));
	cout << "8 insert" << endl;
	map.insert(ft::make_pair(string("8"), 2));
	cout << "9 insert" << endl;
	map.insert(ft::make_pair(string("9"), 4));
	cout << "10 insert" << endl;
	map.insert(ft::make_pair(string("10"), 3));
	cout << "11 insert" << endl;
	map.insert(ft::make_pair(string("11"), 441));
	cout << "12 insert" << endl;
	map.insert(ft::make_pair(string("12"), 36));

// print_map(map);

	map.insert(ft::make_pair(string("13"), 21));
	cout << "2 insert" << endl;
	map.insert(ft::make_pair(string("21"), 12));
	cout << "3 insert" << endl;
	map.insert(ft::make_pair(string("32"), 43));
	cout << "4 insert" << endl;
	map.insert(ft::make_pair(string("43"), 34));
	cout << "5 insert" << endl;
	map.insert(ft::make_pair(string("54"), 15));
	cout << "6 insert" << endl;
	map.insert(ft::make_pair(string("135"), 26));
	cout << "7 insert" << endl;
	map.insert(ft::make_pair(string("76"), 1));
	cout << "8 insert" << endl;
	map.insert(ft::make_pair(string("87"), 2));
	cout << "9 insert" << endl;
	map.insert(ft::make_pair(string("98"), 4));
	cout << "10 insert" << endl;
	map.insert(ft::make_pair(string("109"), 3));
	cout << "11 insert" << endl;
	map.insert(ft::make_pair(string("118"), 441));
	cout << "12 insert" << endl;
	map.insert(ft::make_pair(string("162"), 36));

// print_map(map);

	map.insert(ft::make_pair(string("113"), 21));
	cout << "2 insert" << endl;
	map.insert(ft::make_pair(string("251"), 12));
	cout << "3 insert" << endl;
	map.insert(ft::make_pair(string("342"), 43));
	cout << "4 insert" << endl;
	map.insert(ft::make_pair(string("433"), 34));
	cout << "5 insert" << endl;
	map.insert(ft::make_pair(string("544"), 15));
	cout << "6 insert" << endl;
	map.insert(ft::make_pair(string("1335"), 26));
	cout << "7 insert" << endl;
	map.insert(ft::make_pair(string("726"), 1));
	cout << "8 insert" << endl;
	map.insert(ft::make_pair(string("847"), 2));
	cout << "9 insert" << endl;
	map.insert(ft::make_pair(string("938"), 4));
	cout << "10 insert" << endl;
	map.insert(ft::make_pair(string("1059"), 3));
	cout << "11 insert" << endl;
	map.insert(ft::make_pair(string("1318"), 441));
	cout << "12 insert" << endl;
	map.insert(ft::make_pair(string("1562"), 36));

	// map_std.insert(std::pair<string, int>(string("first"), 1));
	// map.insert(ft::pair<string, int>(string("first"), 1));
	// cout << "2 insert" << endl;
	// map.insert(ft::pair<string, int>(string("second"), 2));
	// cout << "3 insert" << endl;
	// map.insert(ft::pair<string, int>(string("third"), 3));
	// cout << "4 insert" << endl;
	// map.insert(ft::pair<string, int>(string("fourth"), 4));
	// cout << "5 insert" << endl;
	// map.insert(ft::pair<string, int>(string("fifth"), 5));
	// cout << "6 insert" << endl;
	// map.insert(ft::pair<string, int>(string("sixth"), 6));

	print_map(map);
	cout << endl << "1 deleting" << endl;
	// map.delete_node(40);
	// cout << endl << "2 deleting something that isn't there" << endl;
	// map.delete_node(3);
	// cout << endl << "3 deleting everything" << endl;
	// cout << endl << "3-1 deleting 55" << endl;
	// map.delete_node(55);
	// map.print_tree();
	// cout << endl << "3-2 deleting 65" << endl;
	// map.delete_node(65);
	// map.print_tree();
	// cout << endl << "3-3 deleting 75" << endl;
	// map.delete_node(75);
	// map.print_tree();
	// cout << endl << "3-4 deleting 57" << endl;
	// map.delete_node(57);
	// map.print_tree();
	// cout << endl << "3-5 deleting 60" << endl;
	// map.delete_node(60);
	// map.print_tree();

	// cout << "1 insert 5" << endl;
	// map.insert(5);
	// cout << "2 insert 2" << endl;
	// map.insert(2);
	// cout << "3 insert 3" << endl;
	// map.insert(3);
	// cout << "4 insert 7" << endl;
	// map.insert(7);
	// cout << "5 insert 6" << endl;
	// map.insert(6);
	// cout << "6 insert 29" << endl;
	// map.insert(29);
	// map.print_tree();
}
