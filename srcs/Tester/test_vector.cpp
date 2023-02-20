
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#include "iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"
#include "vector.hpp"
#include "test.hpp"
#include "tester_vector.hpp"

using std::cout;
using std::cerr;
using std::string;
using std::endl;
using std::cin;
using ft::tester_vector;

typedef ft::vector<int>	FTVect;
typedef std::vector<int>	STDVect;

typedef tester_vector<FTVect>	FTTester;
typedef tester_vector<STDVect>	STDTester;

FTTester	ft_tester;
STDTester	std_tester;


void showCommands()
{
	cout << "Show commands: help " << endl;
	cout << "Insert:        i <number> " << endl;
	cout << "Erase:         e <position>" << endl;
	cout << "Clear:         c" << endl;
	cout << "[]:            [<position>]" << endl;
	cout << "At:            at <position>" << endl;
	cout << "Swap:          s" << endl;
	cout << "Benchmark:     b" << endl;
	cout << "Print vectors: p" << endl;
	cout << "Quit:          q" << endl;
}

void diff_print_files( string ft_file, string std_file, string diff_file)
{
	std::ifstream	diff;

	ft_tester.print_cont_to_file(ft_file);
	std_tester.print_cont_to_file(std_file);
	diff_file = "./diff/" + diff_file;
	system("mkdir -p ./diff");
	system(string("diff -c " + ft_file + " " + std_file + " > " + diff_file).c_str());

	diff.open(diff_file);
	if (diff.peek() != std::ifstream::traits_type::eof())
		cerr << "Error: Containers don't have the same content. Differences in the are in the file '" << diff_file << "'" << endl;
	else
	{
		diff.close();
		std::remove(diff_file.c_str());
	}
		
	std::remove(ft_file.c_str());
	std::remove(std_file.c_str());
	diff.close();

}

void printVect()
{

	cout << "FT  ";
	ft_tester.print_cont();
	cout << endl;

	cout << "STD ";
	std_tester.print_cont();
	cout << endl;
}

void clearVect()
{
	ft_tester.clear_cont();
	std_tester.clear_cont();
}

void insert( string input, FTVect & ft_v, STDVect & std_v )
{
	try
	{
		ft_v.insert(ft_v.begin(), stoi(input));
		std_v.insert(std_v.begin(), stoi(input));
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void erase( string input, FTVect & ft_v, STDVect & std_v )
{
	FTVect::iterator	ft_it = ft_v.begin();
	STDVect::iterator	std_it = std_v.begin();
	int	value;

	try
	{
		value = stoi(input);
		for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++, std_it++)
		{
			if (*ft_it == value)
				break;
		}
		if (ft_it != ft_v.end())
		{
			ft_v.erase(ft_it);
			std_v.erase(std_it);
		}
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void oper_index( string input )
{
	try
	{
		cout << "FT []  : " << ft_tester.getCont()[(FTVect::size_type)stoi(input)] << endl;
		cout << "STD [] : " << std_tester.getCont()[(FTVect::size_type)stoi(input)] << endl;
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void at( string input )
{
	try
	{
		cout << "FT at  : " << ft_tester.getCont().at((FTVect::size_type)stoi(input)) << endl;
		cout << "STD at : " << std_tester.getCont().at((STDVect::size_type)stoi(input)) << endl;
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void swap( void )
{
	FTVect				first;
	FTVect				second;
	FTVect::iterator	it;
	FTVect::pointer		ptr;

	cout << endl << "Initializing 2 vectors. First one with 1-2-3 and second with 4-5-6-7 " << endl;
	first.push_back(1);
	first.push_back(2);
	first.push_back(3);

	second.push_back(4);
	second.push_back(5);
	second.push_back(6);
	second.push_back(7);

	
	cout << endl << "Initializing:" << endl;
	cout << "an iterator it = (first.begin() + 1)" << endl;
	cout << "a reference ref = *(it)" << endl;
	cout << "a pointer ptr = it.base() " << endl;
	it = (first.begin() + 1);
	FTVect::reference	ref = *it;
	ptr = it.base();
	cout << endl << "Value of iterator, ref and *ptr: " << *it << " " << ref << " " << *ptr << endl;

	cout << endl << "Swapping both vectors" << endl;
	first.swap(second);
	cout << "Value of iterator, ref and *ptr: " << *it << " " << ref << " " << *ptr << endl;
	cout << "Value first.begin() and second.begin(): " << *first.begin() << " " << *second.begin() << endl;
}

template <class FT_FN, class STD_FN>
void	single_benchmark(string title, FT_FN ft_fn, STD_FN std_fn, string diffname )
{
	try {
		ft_tester.benchmark(title, ft_fn);
		std_tester.benchmark(title, std_fn);
		diff_print_files("ft.txt", "std.txt", diffname + ".diff");
		cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }
}

void	benchmark()
{
	single_benchmark("insert", &FTTester::insert, &STDTester::insert, "insert");
	single_benchmark("insert_range", &FTTester::insert_range, &STDTester::insert_range, "insert_range");
	single_benchmark("at_index", &FTTester::at_index, &STDTester::at_index, "at_index");
	single_benchmark("erase", &FTTester::erase, &STDTester::erase, "erase");
	single_benchmark("clear", &FTTester::clear, &STDTester::clear, "clear");
}

bool validateEntry( string input )
{
	if (input.length() <= 0)
	{
		return false;
	}
	return true;
}

int main() {
	FTVect	ft_vector;
	STDVect	std_vector;
	string	input = "";
	
	ft_tester.setCont(&ft_vector);
	std_tester.setCont(&std_vector);

	ft_tester.name = "FTVect";
	std_tester.name = "STDVect";

	showCommands();
	while (input[0] != 'q')
	{
		cout << endl << "Enter command: ";
		std::getline(std::cin, input);
		if (!validateEntry(input))
		{
			cout << "Invalid entry" << endl;
			showCommands();
		}
		else if (input.find("i ") == 0)						insert(input.substr(2), ft_vector, std_vector);
		else if (input.find("e ") == 0)						erase(input.substr(2), ft_vector, std_vector);
		else if (input.find("at ") == 0)					at(input.substr(3));
		else if (input.find("p") == 0 && input.size() == 1)	printVect();
		else if (input.find("c") == 0 && input.size() == 1)	clearVect();
		else if (input.find("b") == 0 && input.size() == 1)	benchmark();
		else if (input.find("[") == 0 && input.find("]") == input.size() - 1)	oper_index(input.substr(1));
		else if (input.find("s") == 0 && input.size() == 1) swap();
		else if (input.find("help", 0) == 0)				showCommands();
	}

	return 0;
}
