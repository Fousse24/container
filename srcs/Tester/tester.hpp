
#ifndef TESTER_HPP
#define TESTER_HPP

#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "timer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::time_point;

using std::string;
using std::cout;
using std::endl;

namespace ft
{

template <class Container>
class tester
{
protected:	
	typedef typename Container::iterator	ft_iterator;

	Container		*cont_;
	ft::timer		timer_;

public:
	tester()
	{
		cont_ = NULL;
	}

	tester( const Container & cont )
	{
		cont_ = &cont;
	}

	tester( const tester & other )
	{
		*this = other;
	}

	~tester() { }

	tester& operator=(const tester& rhs)
	{
		this->cont_ = rhs.cont_;
	}
	
	void benchmark() {}

	void	setCont(Container * cont) { cont_ = cont; }
};

}
#endif
