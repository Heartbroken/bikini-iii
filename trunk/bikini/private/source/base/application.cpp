/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// application

bool application::run() {
	bool l_done = false;
	while(!l_done) {
		//thread::task_<void, real> l_step(sleep, THREAD_PRIORITY_TIME_CRITICAL);
		//l_step.run(0.1f);
		l_done = true;
		uint l_ID = get_first_ID();
		while(l_ID != bad_ID) {
			if(get<task>(l_ID).done()) kill(l_ID);
			else l_done = false;
			l_ID = get_next_ID(l_ID);
		}
		//l_step.wait();
	}
	return false;
}

// application::task

application::task::task(const info &_info, application &_application) :
	manager::object(_info, _application), m_task(*this, &application::task::main)
{
	m_task.run();
}

application::task::~task() {
	if(!m_task.done()) m_task.terminate();
}

// application::task::info

application::task::info::info(uint _type) : manager::object::info(_type) {}

} /* namespace bk -------------------------------------------------------------------------------*/
