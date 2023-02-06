
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

using std::cout;
using std::string;
using std::endl;
using std::cin;

typedef ft::map<int, int>	FTMap;
typedef std::map<int, int>	STDMap;

typedef ft::pair<int, int>	FTPair;
typedef std::pair<int, int>	STDPair;

void showCommands()
{
	cout << "Show commands: help " << endl;
	cout << "Insertion:     i <number> <number> " << endl;
	cout << "Deletion:      d <number> <number>" << endl;
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
		else if (input[0] == 'i') 
		{
			insert(input, ft_map, std_map);
		}
		else if (input[0] == 'd')
		{
			deletion(input, ft_map, std_map);
		}
		else if (input[0] == 'p')
		{
			printMap(ft_map, std_map);
		}
		else if (input[0] == 'c')
		{
			clearMap(ft_map, std_map);
		}
		else if (input.find("help", 0) != string::npos)
		{
			showCommands();
		}
	}

	return 0;
}
