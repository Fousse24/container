
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
	cout << "[]:            [<number>]" << endl;
	cout << "At:            at <number>" << endl;
	cout << "Upper bound:   ub <number>" << endl;
	cout << "Lower bound:   lb <number>" << endl;
	cout << "Equal range:   eq <number>" << endl;
	cout << "Benchmark:     b" << endl;
	cout << "Print maps:    p" << endl;
	// cout << "Print pre:     ps <number>" << endl;
	// cout << "Print succ:    pp <number>" << endl;
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
		cout << "FT er  : " << (*(ft_m.equal_range(stoi(input))).first).first << endl;
		cout << "STD er : " << (*(std_m.equal_range(stoi(input))).first).first << endl;
		
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

void	benchmark()
{
	try {
		ft_tester.benchmark("insert", &FTTester::insert);
		std_tester.benchmark("insert", &STDTester::insert);
		diff_print_files("ft.txt", "std.txt", "insert.diff");
		cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }
	

	try {
		ft_tester.benchmark("insert_range", &FTTester::insert_range);
	std_tester.benchmark("insert_range", &STDTester::insert_range);
	diff_print_files("ft.txt", "std.txt", "insert_range.diff");
	cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }

	try {
		ft_tester.benchmark("at_index", &FTTester::at_index);
	std_tester.benchmark("at_index", &STDTester::at_index);
	diff_print_files("ft.txt", "std.txt", "at_index.diff");
	cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }

	try {
		ft_tester.benchmark("bounds", &FTTester::bounds);
	std_tester.benchmark("bounds", &STDTester::bounds);
	diff_print_files("ft.txt", "std.txt", "bounds.diff");
	cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }

	try {
		ft_tester.benchmark("erase", &FTTester::erase);
	std_tester.benchmark("erase", &STDTester::erase);
	diff_print_files("ft.txt", "std.txt", "erase.diff");
	cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }

	try {
		ft_tester.benchmark("clear", &FTTester::clear);
	std_tester.benchmark("clear", &STDTester::clear);
	diff_print_files("ft.txt", "std.txt", "clear.diff");
	cout << endl;
	}
	catch (std::exception & e) { cout << e.what() << endl; }
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
		std::getline(std::cin, input);
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
		else if (input.find("p") == 0 && input.size() == 1)	printMap();
		else if (input.find("c") == 0 && input.size() == 1)	clearMap();
		else if (input.find("b") == 0 && input.size() == 1)	benchmark();
		else if (input.find("[") == 0 && input.find("]") == input.size() - 1)	oper_index(input.substr(1));
		else if (input.find("help", 0) == 0)				showCommands();
	}

	return 0;
}
