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

void test_run(int) {
	std::cout << " !!!!!!!!!!!!!!!!!\n";
//	return 1;
}
void application::run() {
	//thread::task_<int> l_t0; l_t0.run(/*(const application&)*/*this, &application::test_run);
	thread::task l_t1;
	//functor<int, int> l_f(bk::test_run);
	//l_t1.run(l_f, -1);
	l_t1.run(bk::test_run, -1);
	//l_t0.wait();
	l_t1.wait();
}
int application::test_run(/*sint _i*/) /*const*/ {
	std::cout << /*int(_i) <<*/ " QQQQQQQQQQQQQQQQ\n";
	//thread::task l_t0; l_t0.run(sleep, real(2));
	//l_t0.wait();
	return 0;
}

} /* namespace bk -------------------------------------------------------------------------------*/
