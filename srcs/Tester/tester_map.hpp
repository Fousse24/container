
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
#include <string>

#include "pair.hpp"
#include "tester.hpp"

using std::string;
using std::cout;
using std::endl;

namespace ft
{

template <class Container, class Pair>
class tester_map : public ft::tester<Container>
{	
protected:	
	typedef ft::tester<Container>				tester;
	typedef typename Container::key_type		key_type;
	typedef typename Container::mapped_type		mapped_type;
	typedef void (tester_map::*member_fn)(void);

public:
	string	name;

	tester_map() : tester()	{}
	tester_map( Container & cont ) : tester(cont) {}
	tester_map( const tester_map & other ) : tester(other) { *this = other; }
	~tester_map() { }

	tester_map& operator=(const tester_map& rhs) { this->cont_ = rhs.cont_;	}

	void benchmark(string fn_name, member_fn fn)
	{
		this->timer_.startTime();
		(this->*fn)();
		this->timer_.endTime();
		cout << (name + " " + fn_name + " : ") << this->timer_.getExeTime() << "ms" << endl;

	}

	void insert()
	{
		for (int i = 0; i < 1000000; i++)
		{
			this->cont_->insert(Pair(i, mapped_type()));
		}
	}

	void erase()
	{
		for (int i = 0; i < 1000000; i++)
		{
			this->cont_->erase(i);
		}
	}

	void clear()
	{
		insert();

		this->cont_->clear();

	}
};

	
}

#endif
