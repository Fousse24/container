#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "include/Vector.hpp"
#include "include/Iterator.hpp"
#include "include/VectorIterator.tpp"

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
void print_container(T & cont)
{
	typedef typename T::iterator iterator;
	cout << "Size : " << cont.size() << endl;
	cout << "Capacity : " << cont.capacity() << endl;
	cout << "Content" << endl;
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

int main()
{
	int i = 0;
	ft::vector<int> vect;
	std::vector<int> std_vect;
	std::vector<TestClass*> std_vect_mem;


	for (i = 0; i < 51; i++)
	{
		std_vect.push_back(i * 2);
	}
	// std_vect.reserve(10);
	cout << endl << "PUSH_BACK" << endl;
	for (i = 0; i < 51; i++)
	{
		vect.push_back(i * 2);
	}
	print_container(vect);
	print_container(std_vect);

	cout << endl << "CLEARING" << endl;
	vect.clear();
	std_vect.clear();
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	cout << endl << "[] OPERATOR" << endl;
	cout << vect[2] << endl;
	cout << std_vect[2] << endl;
	vect[2] = 30;
	std_vect[2] = 30;
	cout << vect[2] << endl;
	cout << std_vect[2] << endl;

	cout << endl << "ASSIGN" << endl;
	vect.assign(20, 42);
	std_vect.assign(20, 42);
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	cout << endl << "RESIZE SMALLER 10" << endl;
	vect.resize(10);
	std_vect.resize(10);
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	cout << endl << "RESIZE BIGGER 15" << endl;
	vect.resize(15);
	std_vect.resize(15);
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	// ft::iterator_traits<std::vector<int>::iterator>::value_type hey = 0;
	// std::iterator_traits<std::vector<int>::iterator>::value_type go = 1;
	// ft::iterator_traits<ft::vector<int>::iterator>::value_type hello = 2;
	// std::iterator_traits<ft::vector<int>::iterator>::value_type allo = 3;
	ft::vector<int> vect_buff;
	// vect_buff.assign(1, 1); // ERROR
	vect_buff.push_back(2);
	vect_buff.push_back(3);
	vect_buff.push_back(4);
	vect_buff.push_back(5);
	vect_buff.push_back(6);
	vect_buff.push_back(7);
	vect_buff.push_back(8);
	vect_buff.push_back(9);
	vect_buff.push_back(10);
	vect_buff.push_back(11);
	vect_buff.push_back(12);
	vect_buff.push_back(13);
	cout << endl << "INSERT RANGE 5-12 WITH THE RANGE FROM ANOTHER VECTOR" << endl;
		vect.insert(vect.begin() + 4, vect.begin() + 2, vect.begin() + 9);
	vect.insert(vect.begin() + 4, vect_buff.begin() + 2, vect_buff.begin() + 9);
	std_vect.insert(std_vect.begin() + 4, vect_buff.begin() + 2, vect_buff.begin() + 9);
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	// cout << ft::iterator_traits<ft::vector<int>::Iterator<ft::vector<int> > >::iterator_category(ft::ran
	
	cout << endl << "POP_BACK" << endl;
	vect.pop_back();
	std_vect.pop_back();
	print_container(vect);
	cout << endl;
	print_container(std_vect);

	cout << endl << "ERASE RANGE 2-5" << endl;
	vect.erase(vect.begin() + 2, vect.begin() + 5);
	std_vect.erase(std_vect.begin() + 2, std_vect.begin() + 5);
	print_container(vect);
	cout << endl;
	print_container(std_vect);
	

	// vect.push_back(i);
	// std_vect.push_back(i * i);
	// for (i = 0; i < 1; i++)
	// 	vect.push_back(i);

	// std::for_each(vect.begin(), vect.end(), ft_cout_endl<int>);
	
	// ft::vector<int>::iterator it = vect.begin();
	// std::cout << *std_vect.begin();

	// std_vect.resize(5);
	// std_vect.insert(std_vect.end(), 10, 1);
	// std_vect.reserve(50);
	// std_vect.resize(15);
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

	cout << endl << "STD::FOR_EACH" << endl;
	std::for_each(std::begin(vect), std::end(vect), ft_cout_endl<int>);
	// print_container(vect);
	// print_container(std_vect);
	// std::for_each(std::begin(std_vect), std::end(std_vect), ft_cout_endl<int>);
	// std::for_each(std::begin(std_vect), std::begin(std_vect), ft_cout_endl<int>);
	// std::for_each(std_vect.begin(), std_vect.end(), ft_cout_endl<int>);
	//std::for_each(std_vect_mem.begin(), std_vect_mem.end(), ft_cout_endl<TestClass>);
	// cout << std_vect_mem.begin() - std_vect_mem.end() << endl;

	//cout << *it_empty;

	return 0;
}
