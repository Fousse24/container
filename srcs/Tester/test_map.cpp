
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "iterator.hpp"
#include "ft_lib.hpp"
#include "test.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "rbtree.hpp"
#include "test.hpp"
#include "tester_map.hpp"

using std::cout;
using std::string;
using std::endl;
using std::cin;
using ft::tester_map;

typedef ft::map<int, int>	FTMap;
typedef std::map<int, int>	STDMap;

typedef ft::pair<int, int>	FTPair;
typedef std::pair<int, int>	STDPair;

tester_map<FTMap, STDMap>	g_tester;	


void showCommands()
{
	cout << "Show commands: help " << endl;
	cout << "Insertion:     i <number> <number> " << endl;
	cout << "Deletion:      d <number> <number>" << endl;
	cout << "Upper bound:   ub <number>" << endl;
	cout << "Lower bound:   lb <number>" << endl;
	cout << "Equal range:   eq <number>" << endl;
	cout << "Benchmark:     b" << endl;
	cout << "Print maps:    p" << endl;
	// cout << "Print pre:     ps <number>" << endl;
	// cout << "Print succ:    pp <number>" << endl;
	cout << "Quit:          q" << endl;
}

void printMap( FTMap & ft_m, STDMap & std_m )
{
	FTMap::iterator		ft_it = ft_m.begin();
	STDMap::iterator	std_it = std_m.begin();

	cout << endl << "FT size " << ft_m.size() << " : ";
	for (; ft_it != ft_m.end(); ft_it++)
	{
		cout << (*ft_it).first << " ";
	}

	cout << endl << "STD size " << std_m.size() << " : ";
	for (; std_it != std_m.end(); std_it++)
	{
		cout << (*std_it).first << " ";
	}
	cout << endl;

}

void clearMap( FTMap & ft_m, STDMap & std_m )
{
	ft_m.clear();
	std_m.clear();
}

void insert( string input, FTMap & ft_m, STDMap & std_m )
{
	string::size_type pos;

	try
	{
		pos = input.find(' ', 2);
		if (pos == string::npos)
			throw std::exception();

		ft_m.insert(FTPair(stoi(input.substr(2, pos - 2)), stoi(input.substr(pos + 1))));
		std_m.insert(STDPair(stoi(input.substr(2, pos - 2)), stoi(input.substr(pos + 1))));
	}
	catch (std::exception e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void deletion( string input, FTMap & ft_m, STDMap & std_m )
{
	string::size_type pos;

	try
	{
		ft_m.erase(stoi(input.substr(2)));
		std_m.erase(stoi(input.substr(2)));
	}
	catch (std::exception e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void upperBound( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT ub  : " << (*(ft_m.upper_bound(stoi(input.substr(3))))).first << endl;
		cout << "STD ub : " << (*(std_m.upper_bound(stoi(input.substr(3))))).first << endl;
		
	}
	catch (std::exception e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void lowerBound( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT lb  : " << (*(ft_m.lower_bound(stoi(input.substr(3))))).first << endl;
		cout << "STD lb : " << (*(std_m.lower_bound(stoi(input.substr(3))))).first << endl;
		
	}
	catch (std::exception e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void equalRange( string input, FTMap & ft_m, STDMap & std_m )
{
	try
	{
		cout << "FT er  : " << (*(ft_m.equal_range(stoi(input.substr(3)))).first).first << endl;
		cout << "STD er : " << (*(std_m.equal_range(stoi(input.substr(3)))).first).first << endl;
		
	}
	catch (std::exception e)
	{
		cout << "Invalid number: " << e.what() << endl;
	}
}

void	benchmark()
{
	g_tester.benchmark();
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
	
	g_tester.setFTC(&ft_map);
	g_tester.setSTDC(&std_map);
	benchmark();

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
		else if (input.find("i ") == 0) 
		{
			insert(input, ft_map, std_map);
		}
		else if (input.find("d ") == 0) 
		{
			deletion(input, ft_map, std_map);
		}
		else if (input.find("ub ") == 0) 
		{
			upperBound(input, ft_map, std_map);
		}
		else if (input.find("lb ") == 0) 
		{
			lowerBound(input, ft_map, std_map);
		}
		else if (input.find("er ") == 0) 
		{
			equalRange(input, ft_map, std_map);
		}
		else if (input.find("p") == 0 && input.size() == 1) 
		{
			printMap(ft_map, std_map);
		}
		else if (input.find("c") == 0 && input.size() == 1)
		{
			clearMap(ft_map, std_map);
		}
		else if (input.find("b") == 0 && input.size() == 1)
		{
			benchmark();
		}
		else if (input.find("help", 0) == 0)
		{
			showCommands();
		}
	}

	return 0;
}
