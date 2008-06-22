/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

application::application() {
}

application::~application() {
}

int test_run(int) {
	std::cout << " !!!!!!!!!!!!!!!!!\n";
	return 1;
}
void application::run() {
	//thread::task l_t0; l_t0.run(*this, &application::test_run, -1);
	thread::task_<int> l_t1(THREAD_PRIORITY_TIME_CRITICAL);
	functor<int, int> l_f(bk::test_run);
	//l_t1.run(l_f, -1);
	l_t1.run(bk::test_run, -1);
	//l_t0.wait();
	l_t1.wait();
}
void application::test_run(sint _i) {
	std::cout << int(_i) << " QQQQQQQQQQQQQQQQ\n";
	//thread::task l_t0; l_t0.run(sleep, real(2));
	//l_t0.wait();
}

} /* namespace bk -------------------------------------------------------------------------------*/
