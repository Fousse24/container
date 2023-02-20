
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"

using std::cout;
using std::string;
using std::endl;
using std::cin;

void	print_text(string text, bool nl)
{
	cout << text;
	if (nl)
		cout << endl;
}

string	title(string title, int level)
{
	switch (level)
	{
		case 1:
			return YELLOW + string("---- ") + title + RESET;
		case 2:
			return BLUE + string("-- ") + title + RESET;
		case 3:
			return CYAN + string(" ") + title + RESET;
		default:
			return title;
	}
	return title;
}

template<class T>
void print_container(T & cont, int type)
{
	
	typedef typename T::iterator iterator;
	switch (type)
	{
		case 1:
			print_text(title("FT_VECTOR", 3), true);
			break;
		case 2:
			print_text(title("STD_VECTOR", 3), true);
			break;
	}
	cout << "- Size : " << cont.size() << endl;
	cout << "- Capacity : " << cont.capacity() << endl;
	cout << "- Content" << endl;
	for (iterator it = cont.begin(); it < cont.end(); it++)
	{
		cout << *it << " ";
	} 
	cout << endl;
}

template<class T>
void ft_cout_endl(const T&  msg)
{
	cout << msg << endl;
}

template<class I>
void print_it(I it)
{
	ft_cout_endl<I>(*it);
}
