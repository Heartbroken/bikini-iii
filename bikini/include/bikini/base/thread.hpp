/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace thread { /*----------------------------------------------------------------------------*/

/// task_
template<typename _R, typename _A0 = notype, typename _A1 = notype, typename _A2 = notype, typename _A3 = notype, typename _A4 = notype, typename _A5 = notype, typename _A6 = notype, typename _A7 = notype, typename _A8 = notype, typename _A9 = notype>
struct task_ : uncopyble {
	typedef functor_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9> functor;
	template<typename _F> inline task_(_F &_f, sint _priority = THREAD_PRIORITY_NORMAL, uint _stacksize = 0, uint _processor = bad_ID);
	template<typename _O, typename _M> inline task_(_O &_o, const _M &_m, sint _priority = THREAD_PRIORITY_NORMAL, uint _stacksize = 0, uint _processor = bad_ID);
	inline ~task_();
	inline bool run();
	inline bool done() const;
	inline _R wait() const;
	inline void terminate();
	inline void clear();
private:
	functor m_functor;
	handle m_handle;
	sint m_priority;
	uint m_stacksize;
	uint m_processor;
	_R m_result;
};
typedef task_<void> task;

/// event
struct event : uncopyble {
	inline event(bool _reset = false, bool _state = false);
	inline ~event();
	inline void set();
	inline bool wait(real _time = infinity);
private:
	HANDLE m_handle;
};

#include "thread.inl"

} /* namespace thread ---------------------------------------------------------------------------*/
