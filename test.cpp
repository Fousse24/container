#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "include/Vector.hpp"
#include "include/Iterator.hpp"

using std::cout;
using std::string;
using std::endl;

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

int main()
{
	ft::vector<int> vect;
	std::vector<int> std_vect;

	for (int i = 0; i < 51; i++)
		vect.push_back(i);

	for (int i = 0; i < 51; i++)
		std_vect.push_back(i + 50);

	std::for_each(vect.begin(), vect.end(), ft_cout_endl<int>);
	// std::for_each(std::begin(std_vect), std::end(std_vect), ft_cout_endl<int>);
	ft::vector<int>::iterator it = vect.begin();
	std::cout << *vect.begin();
	return 0;

	//cout << *it_empty;


}
