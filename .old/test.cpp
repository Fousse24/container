
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "vector.hpp"
#include "iterator.hpp"
#include "vector_iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"

using std::cout;
using std::string;
using std::endl;
using std::cin;

class TestClass
{	
public:
	int _value;
	TestClass(){}
	TestClass(int v){ _value = v ;}

};

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

template<class FT_C, class STD_C>
void test_insert(FT_C ft_c, STD_C std_c)
{
	FT_C	ft_test;
	STD_C	std_test;
	int i = 0;

	print_text(title("INSERT TESTS", 1), true);

	for (i = 0; i < 51; i++)
	{
		ft_test.push_back(i * 2);
	}
	cout << endl << "PUSH_BACK" << endl;
	for (i = 0; i < 51; i++)
	{
		std_test.push_back(i * 2);
	}
	
	print_text(title("INSERT 20 ELEMENTS OF VALUE 3 AT THE BEGINNING", 2), true);
	ft_c.insert(ft_c.begin(), 20, 3);
	std_c.insert(std_c.begin(), 20, 3);
	print_container(ft_c, 1);
	cout << endl;
	print_container(std_c, 2);
	cout << endl;

	print_text(title("INSERT 10 ELEMENTS OF ANOTHER VECTOR AT POSITION 5", 2), true);
	ft_c.insert(ft_c.begin() + 5, ft_test.begin(), ft_test.begin() + 10);
	std_c.insert(std_c.begin() + 5, std_test.begin(), std_test.begin() + 10);
	print_container(ft_c, 1);
	cout << endl;
	print_container(std_c, 2);
}

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

void enter_prompt(void)
{
	bool 	loop = true;
	string	input;

	// while ((condition)) {
	// statements
	// }
	

	while (loop)
	{
		print_text(title("Choose a test by entering the respective number", 1), true);
		cin >> input;
		if (!input.compare("1"))
			test_insert(ft::vector<int>(), std::vector<int>());
		else if (!input.compare("2"))
			test_pair();
		else
			loop = false;
	}
}

int main()
{
	int i = 0;
	ft::vector<int> vect;
	std::vector<int> std_vect;
	std::vector<TestClass*> std_vect_mem;
	std::map<string, int>	std_map;

	std_map.insert(std::pair<string, int>("hello", 1));
	cout << std_map.at("hello") << endl;

	enter_prompt();
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
	print_container(vect, 1);
	print_container(std_vect, 2);

	// vect.assign(5, 6);
	// print_container(vect, 2);
	// std_vect.assign(5, 6);
	// print_container(std_vect, 2);

	cout << endl << "CLEARING" << endl;
	vect.clear();
	std_vect.clear();
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

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
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	cout << endl << "RESIZE SMALLER 10" << endl;
	vect.resize(10);
	std_vect.resize(10);
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	cout << endl << "RESIZE BIGGER 15" << endl;
	vect.resize(15);
	std_vect.resize(15);
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	ft::vector<int> vect_buff;
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
	vect.insert(vect.begin() + 4, vect_buff.begin() + 2, vect_buff.begin() + 9);
	// vect.insert(vect.begin() + 4, std_vect.begin() + 2, std_vect.begin() + 9);
	std_vect.insert(std_vect.begin() + 4, vect_buff.begin() + 2, vect_buff.begin() + 9);
	// std_vect.insert(std_vect.begin() + 4, vect.begin() + 2, vect.begin() + 9);
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	// cout << ft::iterator_traits<ft::vector<int>::Iterator<ft::vector<int> > >::iterator_category(ft::ran
	
	cout << endl << "POP_BACK" << endl;
	vect.pop_back();
	std_vect.pop_back();
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	cout << endl << "ERASE RANGE 2-5" << endl;
	vect.erase(vect.begin() + 2, vect.begin() + 5);
	std_vect.erase(std_vect.begin() + 2, std_vect.begin() + 5);
	print_container(vect, 1);
	cout << endl;
	print_container(std_vect, 2);

	cout << endl << "INSERT 100 elements of value 2 from the second positions" << endl;
	test_insert(ft::vector<int>(), std::vector<int>());
	// vect.insert(vect.begin() + 1, 100, 2);
	// std_vect.insert(std_vect.begin() + 1, 100, 2);
	// print_container(vect, 1);
	// cout << endl;
	// print_container(std_vect, 2);
	
	// bool hey(ft::is_integral<int>::value);
	// cout << endl << endl << ft::enable_if<ft::is_integral<int>, bool>::type() << endl;
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

	// cout << endl << "STD::FOR_EACH" << endl;
	// std::for_each(std::begin(vect), std::end(vect), ft_cout_endl<int>);
	// print_container(vect, 1);
	// print_container(std_vect, 2);
	// std::for_each(std::begin(std_vect), std::end(std_vect), ft_cout_endl<int>);
	// std::for_each(std::begin(std_vect), std::begin(std_vect), ft_cout_endl<int>);
	// std::for_each(std_vect.begin(), std_vect.end(), ft_cout_endl<int>);
	//std::for_each(std_vect_mem.begin(), std_vect_mem.end(), ft_cout_endl<TestClass>);
	// cout << std_vect_mem.begin() - std_vect_mem.end() << endl;

	//cout << *it_empty;

	return 0;
}
