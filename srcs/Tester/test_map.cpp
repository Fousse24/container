
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>

#include "iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "rbtree.hpp"
#include "test.hpp"
#include "tester_map.hpp"

using std::cout;
using std::cerr;
using std::string;
using std::endl;
using std::cin;
using ft::tester_map;

typedef ft::map<int, int>	FTMap;
typedef std::map<int, int>	STDMap;

typedef ft::pair<int, int>	FTPair;
typedef std::pair<int, int>	STDPair;

typedef tester_map<FTMap, FTPair>	FTTester;
typedef tester_map<STDMap, STDPair>	STDTester;

FTTester	ft_tester;
STDTester	std_tester;

void showCommands()
{
	cout << "Show commands: help " << endl;
	cout << "Insert:        i <number> <number> " << endl;
	cout << "Erase:         d <number> <number>" << endl;
	cout << "Clear:         c" << endl;
	cout << "[]:            [<number>]" << endl;
	cout << "At:            at <number>" << endl;
	cout << "Upper bound:   ub <number>" << endl;
	cout << "Lower bound:   lb <number>" << endl;
	cout << "Equal range:   eq <number>" << endl;
	cout << "Benchmark:     b" << endl;
	cout << "Print maps:    p" << endl;
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

void printMap()
{

	cout << "FT  ";
	ft_tester.print_cont();
	cout << endl;

	cout << "STD ";
	std_tester.print_cont();
	cout << endl;
}

template <class M>
void printMap(M & m)
{
	typedef typename M::iterator iterator;
	iterator	iter;

	cout << "Size " << m.size() << " : ";
	for (iter = m.begin(); iter != m.end(); iter++)
	{
		cout << (*iter).first << " ";
	}
}

void clearMap()
{
	ft_tester.clear_cont();
	std_tester.clear_cont();
}

void insert( string input, FTMap & ft_m, STDMap & std_m )
{
	string::size_type pos;

	try
	{
		pos = input.find(' ', 0);
		if (pos == string::npos)
			throw std::exception();

		ft_m.insert(FTPair(stoi(input), stoi(input.substr(pos + 1))));
		std_m.insert(STDPair(stoi(input), stoi(input.substr(pos + 1))));
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void erase( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		ft_m.erase(stoi(input));
		std_m.erase(stoi(input));
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void upperBound( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT ub  : " << (*(ft_m.upper_bound(stoi(input)))).first << endl;
		cout << "STD ub : " << (*(std_m.upper_bound(stoi(input)))).first << endl;
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void lowerBound( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT lb  : " << (*(ft_m.lower_bound(stoi(input)))).first << endl;
		cout << "STD lb : " << (*(std_m.lower_bound(stoi(input)))).first << endl;
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void equalRange( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT er  : " << (*(ft_m.equal_range(stoi(input))).first).first << " " << (*(ft_m.equal_range(stoi(input))).second).first << endl;
		cout << "STD er : " << (*(std_m.equal_range(stoi(input))).first).first << " " << (*(std_m.equal_range(stoi(input))).second).first << endl;
		
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
		cout << "FT []  : " << ft_tester.getCont()[stoi(input)] << endl;
		cout << "STD [] : " << std_tester.getCont()[stoi(input)] << endl;
		
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
		cout << "FT at  : " << ft_tester.getCont().at(stoi(input)) << endl;
		cout << "STD at : " << std_tester.getCont().at(stoi(input)) << endl;
		
	}
	catch (const std::exception& e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void swap()
{
	FTMap				first;
	FTMap				second;
	FTMap::iterator		it;
	FTMap::pointer		ptr;

	cout << endl << "Initializing 2 maps. First one with 1-2-3-4-5 and second with 6-7-8-9-10..." << endl;
	first.insert(ft::make_pair(1, 0));
	first.insert(ft::make_pair(2, 0));
	first.insert(ft::make_pair(3, 0));
	first.insert(ft::make_pair(4, 0));
	first.insert(ft::make_pair(5, 0));

	second.insert(ft::make_pair(6, 0));
	second.insert(ft::make_pair(7, 0));
	second.insert(ft::make_pair(8, 0));
	second.insert(ft::make_pair(9, 0));
	second.insert(ft::make_pair(10, 0));

	
	cout << endl << "Initializing:" << endl;
	cout << "an iterator it = first.find(4)" << endl;
	cout << "a reference ref = *(it)" << endl;
	cout << "a pointer ptr = it.base() " << endl;
	it = (first.find(4));
	FTMap::reference	ref = *it;
	ptr = it.base();
	cout << endl << "Values of iterator - ref - *ptr: " << endl << (*it).first << " - " << ref.first << " - " << (*ptr).first << endl;

	cout << endl << "Deleting key 2, 3 and 5 from first..." << endl;
	first.erase(2);
	first.erase(3);
	first.erase(5);
	// first.swap(second);
	cout << endl << "Values of iterator - ref - *ptr: " << endl << (*it).first << " - " << ref.first << " - " << (*ptr).first << endl;

	cout << endl << "Swapping first with second..." << endl;
	first.swap(second);
	cout << "Values of iterator - ref - *ptr: " << endl << (*it).first << " - " << ref.first << " - " << (*ptr).first << endl;
	cout << endl << "first and second content: " << endl;
	printMap(first);
	cout << endl;
	printMap(second);
	
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
	single_benchmark("bounds", &FTTester::bounds, &STDTester::bounds, "bounds");
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
	FTMap	ft_map;
	STDMap	std_map;
	string	input = "";
	
	ft_tester.setCont(&ft_map);
	std_tester.setCont(&std_map);

	ft_tester.name = "FTMap";
	std_tester.name = "STDMap";

	showCommands();
	while (input[0] != 'q')
	{
		cout << endl << "Enter command: ";
		std::getline(cin, input);
		if (!validateEntry(input))
		{
			cout << "Invalid entry" << endl;
			showCommands();
		}
		else if (input.find("i ") == 0)						insert(input.substr(2), ft_map, std_map);
		else if (input.find("e ") == 0)						erase(input.substr(2), ft_map, std_map);
		else if (input.find("at ") == 0)					at(input.substr(3));
		else if (input.find("ub ") == 0)					upperBound(input.substr(3), ft_map, std_map);
		else if (input.find("lb ") == 0)					lowerBound(input.substr(3), ft_map, std_map);
		else if (input.find("er ") == 0)					equalRange(input.substr(3), ft_map, std_map);
		else if (input.find("s") == 0 && input.size() == 1)	swap();
		else if (input.find("p") == 0 && input.size() == 1)	printMap();
		else if (input.find("c") == 0 && input.size() == 1)	clearMap();
		else if (input.find("b") == 0 && input.size() == 1)	benchmark();
		else if (input.find("[") == 0 && input.find("]") == input.size() - 1)	oper_index(input.substr(1));
		else if (input.find("help", 0) == 0)				showCommands();
	}

	return 0;
}


