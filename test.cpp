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

class TestClass
{	
public:
	int _value;
	TestClass(){}
	TestClass(int v){ _value = v ;}

};

// std::ostream	&operator<<( std::ostream & o, TestClass const & fpn ) { cout << fpn._value << endl; };

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
	std::vector<TestClass*> std_vect_mem;

	// std_vect.reserve(10);
	for (int i = 0; i < 51; i++)
		vect.push_back(i);

	// for (int i = 0; i < 51; i++)
	// 	std_vect.push_back(i + 50);

	// std::for_each(vect.begin(), vect.end(), ft_cout_endl<int>);
	
	// ft::vector<int>::iterator it = vect.begin();
	// std::cout << *std_vect.begin();

	// std_vect.resize(5);
	std_vect.insert(std_vect.end(), 10, 1);
	std_vect.reserve(50);
	std_vect.resize(15);
	// std_vect.insert(std_vect.begin() + 2, 2);
	// std_vect.erase(std_vect.begin(), std_vect.begin() - 1);
	// std_vect.at(40);
	// std_vect.assign(std_vect.begin(), std_vect.begin() - 2);
	// std_vect.insert(std_vect.end(), 10, 1);
	// std_vect.begin() = std_vect.begin() + 2;
	// std_vect.resize(15);

	// std_vect_mem.assign(5, new TestClass(2));
	// std_vect_mem.erase(std_vect_mem.end() - 2);
	// std_vect.push_back(10);
	// std_vect.erase(std_vect.begin() + 2);
	// std_vect.assign(5, 2);

	std::for_each(std::begin(std_vect), std::begin(std_vect), ft_cout_endl<int>);
	// std::for_each(std_vect.begin(), std_vect.end(), ft_cout_endl<int>);
	//std::for_each(std_vect_mem.begin(), std_vect_mem.end(), ft_cout_endl<TestClass>);
	// cout << std_vect_mem.begin() - std_vect_mem.end() << endl;

	//cout << *it_empty;

	return 0;
}
