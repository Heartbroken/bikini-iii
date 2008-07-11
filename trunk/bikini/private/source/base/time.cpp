/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/
	
rbig sys_time() {
	//u32 l_fpcw = _control87(0, 0); _control87(_PC_64, _MCW_PC);
	static LARGE_INTEGER l_clock_freq;
	static bool l_once = (QueryPerformanceFrequency(&l_clock_freq) == TRUE);
	static rbig l_frq = rbig(l_clock_freq.QuadPart);
	LARGE_INTEGER l_clock; QueryPerformanceCounter(&l_clock);
	rbig l_time = rbig(l_clock.QuadPart) / l_frq;
	//_control87(l_fpcw, 0xffffffff);
	return l_time;
}

void sleep(real _t) {
	Sleep(DWORD(_t * real(1000)));
}

// ticker

ticker::ticker(real _period) : m_period(_period), m_run(true), m_event(false, false), m_task(*this, &ticker::m_proc, THREAD_PRIORITY_TIME_CRITICAL) {
	m_task.run();
}
ticker::~ticker() {
	m_run = false;
	m_task.wait();
}
real ticker::period() {
	return m_period;
}
void ticker::set_period(real _period) {
	m_period = _period;
}
void ticker::wait() {
	m_event.wait();
}
void ticker::m_proc() {
	while(m_run) {
		sleep(m_period);
		m_event.set();
	}
}

} /* namespace bk -------------------------------------------------------------------------------*/
