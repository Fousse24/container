
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::time_point;

namespace ft
{
class timer
{
protected:	
	typedef time_point<high_resolution_clock, high_resolution_clock::duration>	time_p;

	time_p	_start_time;
	time_p	_end_time;
	duration<double, std::milli>	exe_time;	

public:
	timer() {}

	timer( const timer & other ) { *this = other; }

	~timer() {}

	timer& operator=(const timer& rhs) 
	{ 
		_start_time = rhs._start_time;
		return *this;
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
