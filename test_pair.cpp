
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "vector.hpp"
#include "iterator.hpp"
#include "vector_iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"
#include "pair.hpp"

#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[0m"

using std::cout;
using std::string;
using std::endl;
using std::cin;


template <class T1, class T2> 
void	print_pairs(const ft::pair<T1, T2> & p1, const ft::pair<T1, T2> & p2)
{
	print_text(title("CONTENT", 3), true);
	cout << p1 << endl;
	cout << p2 << endl;
}



void test_pair(void)
{
	// std::pair<int, string>	std_pair_equal;
	ft::pair<int, string>	p1;
	ft::pair<int, string>	p2;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv1;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv2;
	ft::vector<int>	v1(20, 5);
	ft::vector<int> v2(20, 5);

	print_text(title("PAIR TESTS", 1), true);

	test_pair_equal();
	test_pair_compare();

}

void test_pair_equal(void)
{
	ft::pair<int, string>	p1;
	ft::pair<int, string>	p2;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv1;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv2;
	ft::vector<int>	v1(20, 5);
	ft::vector<int> v2(20, 5);

	print_text(title("TEST EQUAL <int, string> ", 2), true);
	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << GREEN << "Pairs are equal!" << RESET;
	else
		cout << RED << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Ruarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are equal!" << RESET;
	else
		cout << GREEN << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(41, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are equal!" << RESET;
	else
		cout << GREEN << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(43, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are equal!" << RESET;
	else
		cout << GREEN << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Ruarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are equal!" << RESET;
	else
		cout << GREEN << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	print_text(title("TEST EQUAL <ft::vector<int> >, <ft::vector<int> >; vectors content is 20 int of value 5", 2), true);
	pv1 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	pv2 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	// print_pairs<ft::vector<int>, ft::vector<int>>(p1, p2);
	if (pv1 == pv2)
		cout << GREEN << "Pairs are equal!" << RESET;
	else
		cout << RED << "Pairs are not equal!" << RESET;
	cout << endl << endl;

	print_text(title("TEST EQUAL <ft::vector<int> >, <ft::vector<int> >; pair 2 has another vector with different content", 2), true);
	v2 = ft::vector<int>(19, 5);
	pv1 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v1);
	pv2 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	if (pv1 == pv2)
		cout << RED << "Pairs are equal!" << RESET;
	else
		cout << GREEN << "Pairs are not equal!" << RESET;
	cout << endl << endl;
}

void test_pair_compare(void)
{
	ft::pair<int, string>	p1;
	ft::pair<int, string>	p2;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv1;
	ft::pair<ft::vector<int>, ft::vector<int> >	pv2;
	ft::vector<int>	v1(20, 5);
	ft::vector<int> v2(20, 5);

	print_text(title("TEST COMPARE <int, string> ", 2), true);
	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << GREEN << "Pairs are COMPARE!" << RESET;
	else
		cout << RED << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Ruarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are COMPARE!" << RESET;
	else
		cout << GREEN << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Quarante-deux");
	p2 = ft::pair<int, string>(41, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are COMPARE!" << RESET;
	else
		cout << GREEN << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(43, "Quarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are COMPARE!" << RESET;
	else
		cout << GREEN << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	p1 = ft::pair<int, string>(42, "Ruarante-deux");
	p2 = ft::pair<int, string>(42, "Quarante-deux");
	print_pairs<int, string>(p1, p2);
	if (p1 == p2)
		cout << RED << "Pairs are COMPARE!" << RESET;
	else
		cout << GREEN << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	print_text(title("TEST COMPARE <ft::vector<int> >, <ft::vector<int> >; vectors content is 20 int of value 5", 2), true);
	pv1 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	pv2 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	// print_pairs<ft::vector<int>, ft::vector<int>>(p1, p2);
	if (pv1 == pv2)
		cout << GREEN << "Pairs are COMPARE!" << RESET;
	else
		cout << RED << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;

	print_text(title("TEST COMPARE <ft::vector<int> >, <ft::vector<int> >; pair 2 has another vector with different content", 2), true);
	v2 = ft::vector<int>(19, 5);
	pv1 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v1);
	pv2 = ft::pair<ft::vector<int>, ft::vector<int> >(v1, v2);
	if (pv1 == pv2)
		cout << RED << "Pairs are COMPARE!" << RESET;
	else
		cout << GREEN << "Pairs are not COMPARE!" << RESET;
	cout << endl << endl;
}


// void enter_prompt(void)
// {
// 	bool 	loop = true;
// 	string	input;

// 	// while ((condition)) {
// 	// statements
// 	// }
	

// 	while (loop)
// 	{
// 		print_text(title("Choose a test by entering the respective number", 1), true);
// 		cin >> input;
// 		if (!input.compare("1"))
// 			test_insert(ft::vector<int>(), std::vector<int>());
// 		else
// 			loop = false;
// 	}
// }
