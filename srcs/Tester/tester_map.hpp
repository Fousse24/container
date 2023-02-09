
#ifndef TESTER_MAP_HPP
#define TESTER_MAP_HPP

#include <initializer_list>
#include <limits>
#include <memory>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <utility>
#include "pair.hpp"

#include "tester.hpp"


using std::cout;
using std::endl;

namespace ft
{

template <class FTC, class STDC>
class tester_map : public ft::tester<FTC, STDC>
{	
protected:	
	typedef ft::tester<FTC, STDC>		tester;
	typedef typename STDC::key_type		key_type;
	typedef typename STDC::mapped_type	mapped_type;

public:
	tester_map() : tester()
	{
		this->_ftc = NULL;
		this->_stdc = NULL;
	}

	tester_map( FTC & ftc, STDC & stdc ) : tester(ftc, stdc)
	{
	}

	tester_map( const tester_map & tester_map ) : tester(tester_map)
	{
		*this = tester_map;
	}

	~tester_map() { }

	tester_map& operator=(const tester_map& v)
	{
		this->_ftc = v._ftc;
		this->_stdc = v._stdc;
	}

	void benchmark()
	{
		this->insert();
		cout << endl;
		this->erase();
		cout << endl;
		this->clear();
	}

	void insert()
	{
		this->startTime();
		for (int i = 0; i < 1000000; i++)
		{
			this->_ftc->insert(ft::make_pair(i, mapped_type()));
		}
		this->endTime();
		this->printResult("FT insert 1million : ");

		this->startTime();
		for (int i = 0; i < 1000000; i++)
		{
			this->_stdc->insert(std::make_pair(i, mapped_type()));
		}
		this->endTime();
		this->printResult("STD insert 1million: ");

	}

	void erase()
	{
		this->startTime();
		for (int i = 0; i < 1000000; i++)
		{
			this->_ftc->erase(i);
		}
		this->endTime();
		this->printResult("FT erase 1million : ");

		this->startTime();
		for (int i = 0; i < 1000000; i++)
		{
			this->_stdc->erase(i);
		}
		this->endTime();
		this->printResult("STD erase 1million: ");

	}

	void clear()
	{
		for (int i = 0; i < 1000000; i++)
		{
			this->_ftc->insert(ft::make_pair(i, mapped_type()));
			this->_stdc->insert(std::make_pair(i, mapped_type()));
		}

		this->startTime();
		this->_ftc->clear();
		this->endTime();
		this->printResult("FT clear : ");

		this->startTime();
		this->_stdc->clear();
		this->endTime();
		this->printResult("STD clear : ");

	}
};

	
}

#endif
