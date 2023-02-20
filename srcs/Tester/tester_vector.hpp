
#ifndef TESTER_VECTOR_HPP
#define TESTER_VECTOR_HPP

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

template <class Container>
class tester_vector : public ft::tester<Container>
{	
protected:	
	typedef ft::tester<Container>				tester;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef void (tester_vector::*member_fn)(void);

public:
	string	name;
	Container temp;

	tester_vector() : tester()	{ init_temp(); }
	tester_vector( Container & cont ) : tester(cont) { init_temp(); }
	tester_vector( const tester_vector & other ) : tester(other) { *this = other; }
	~tester_vector() { }

	tester_vector& operator=(const tester_vector& rhs)
	{
		this->cont_ = rhs.cont_;
		temp = rhs.temp;
	}

	void	init_temp()
	{
		temp.assign( 10000000, 5);
	}

	void benchmark(string fn_name, member_fn fn)
	{
		this->timer_.startTime();
		(this->*fn)();
		this->timer_.endTime();
		cout << (name + " " + fn_name + " : ") << this->timer_.getExeTime() << "ms" << endl;
	}

	void insert()
	{
		for (int i = 0; i < 5000000; i++)
		{
			this->cont_->insert(this->cont_->begin() + i, i);
		}
	}

	void insert_range()
	{
		this->cont_->insert(this->cont_->begin(), temp.begin(), temp.end());
	}

	void at_index()
	{
		for (size_type i = 0; i < this->cont_->size(); i++)
		{
			this->cont_->at(i);
			(*this->cont_)[i];
		}
	}

	void erase()
	{
		this->cont_->erase(this->cont_->begin(), this->cont_->end());
	}

	void clear()
	{
		// insert();

		this->temp.clear();

	}
};

	
}

#endif
