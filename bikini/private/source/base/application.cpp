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
		thread::task l_step(THREAD_PRIORITY_TIME_CRITICAL);
		l_step.run(sleep, 0.1f);
		l_done = true;
		uint l_ID = get_first_ID();
		while(l_ID != bad_ID) {
			if(get<task>(l_ID).done()) kill(l_ID);
			else l_done = false;
			l_ID = get_next_ID(l_ID);
		}
		l_step.wait();
	}
	return false;
}

// application::task

application::task::task(const info &_info, application &_application) : manager::object(_info, _application) {
	m_task.run(*this, &application::task::main);
}

// application::task::info

application::task::info::info(uint _type) : manager::object::info(_type) {}

} /* namespace bk -------------------------------------------------------------------------------*/
