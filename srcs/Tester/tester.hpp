
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

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::time_point;

using std::string;
using std::cout;
using std::endl;

namespace ft
{

template <class FTC, class STDC>
class tester
{
protected:	
	typedef typename FTC::iterator	ft_iterator;
	typedef typename STDC::iterator	std_iterator;
	typedef time_point<high_resolution_clock, high_resolution_clock::duration>	time_p;

	FTC		*_ftc;
	STDC	*_stdc;
	time_p	_start_time;
	time_p	_end_time;
	duration<double, std::milli>	exe_time;	

public:
	tester()
	{
		_ftc = NULL;
		_stdc = NULL;
	}

	tester( FTC & ftc, STDC & stdc )
	{
		_ftc = &ftc;
		_stdc = &stdc;
	}

	tester( const tester & tester )
	{
		*this = tester;
	}

	~tester() { }

	tester& operator=(const tester& v)
	{
		this->_ftc = v._ftc;
		this->stdc = v._stdc;
	}
	
	void	setFTC(FTC * ftc) { _ftc = ftc; }
	void	setSTDC(STDC * stdc) { _stdc = stdc; }

	virtual void	benchmark() = 0;

	void	printResult(string msg)
	{
		cout << msg << getExeTime() << endl;
	}

	void	startTime()
	{
		_start_time = high_resolution_clock::now();
	}

	void	endTime()
	{
		_end_time = high_resolution_clock::now();
		exe_time = _end_time - _start_time;
	}

	double	getExeTime()
	{
		return (double)exe_time.count();
	}
};

}
#endif
