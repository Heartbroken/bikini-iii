/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// Returns current system time
rbig sys_time();
/// Make thread to sleep during next _t seconds (!!! not milliseconds !!!)
void sleep(real _t);

/// ticker
/** [TODO]
 */
struct ticker {
	ticker(real _period);
	~ticker();
	real period();
	void set_period(real _period);
	void sync();
private:
	real m_period;
	bool m_run;
	thread::signal m_sync;
	thread::task m_task;
	void m_proc();
};
