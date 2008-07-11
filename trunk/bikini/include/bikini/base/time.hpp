/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

rbig sys_time();
void sleep(real _t);

/// ticker
/** [TODO]
 */
struct ticker {
	ticker(real _period);
	~ticker();
	real period();
	void set_period(real _period);
	void tick();
private:
	real m_period;
	bool m_run;
	thread::event m_tick;
	thread::task m_task;
	void m_proc();
};
