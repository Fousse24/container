
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
#include <iostream>
#include <fstream>

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
	typedef typename Container::iterator	iterator;

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
	
	virtual void	print_cont_to_file(string name)
	{
		iterator iter;
		std::ofstream	file;

  		file.open(name);
		file << "Size " << cont_->size() << " : ";
		for (iter = cont_->begin(); iter != cont_->end(); iter++)
		{
			file << (*iter).first << " ";
		}

  		file.close();
	}

	virtual void	print_cont() const
	{
		iterator iter;

		cout << "Size " << cont_->size() << " : ";
		for (iter = cont_->begin(); iter != cont_->end(); iter++)
		{
			cout << (*iter).first << " ";
		}
	}

	void	benchmark() {}

	void	setCont(Container * cont) { cont_ = cont; }
	Container&	getCont() { return *cont_; }

	virtual void	clear_cont() { cont_->clear(); }
};

}
#endif
