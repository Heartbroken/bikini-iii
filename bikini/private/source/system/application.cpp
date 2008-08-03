/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// application

application::application() {
#if defined(WIN32)
	//
	typedef HWND (WINAPI *GetConsoleWindow_fn)(void);
	HMODULE l_kernel32_h = GetModuleHandleA("kernel32.dll");
	GetConsoleWindow_fn GetConsoleWindow = (GetConsoleWindow_fn)GetProcAddress(l_kernel32_h, "GetConsoleWindow");
	if(GetConsoleWindow != 0) ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//
	SetConsoleTitleA(" bikini-iii");
#endif
}
application::~application() {
}

bool application::run() {
	ticker l_ticker(0.1f);
	bk::rbig l_time = bk::sys_time();
	bool l_done = false;
	while(!l_done) {
		bk::real l_dt = bk::real(bk::sys_time() - l_time); l_time = bk::sys_time();
		update(l_dt);
		l_done = true;
		uint l_ID = get_first_ID();
		while(l_ID != bad_ID) {
			if(get<task>(l_ID).done()) kill(l_ID);
			else l_done = false;
			l_ID = get_next_ID(l_ID);
		}
		l_ticker.sync();
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
