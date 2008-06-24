/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace thread { /*----------------------------------------------------------------------------*/

/// task_
template<typename _R>
struct task_ : dont_copy {
	inline task_();
	inline task_(sint _priority);
	inline void set_priority(sint _priority);
	inline bool done();
	inline _R wait();
	// functor call
	template<typename _Functor>
	inline bool run(const _Functor &_f);
	template<typename _Functor, typename _A0>
	inline bool run(const _Functor &_f, _A0 _a0);
	// function call
	inline bool run(_R(&_f)());
	template<typename _A0, typename _P0>
	inline bool run(_R(&_f)(_A0), _P0 _a0);
	// member function call
	template<typename _Object, typename _Class>
	inline bool run(_Object &_o, _R(_Class::*_m)());
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(_Object &_o, _R(_Class::*_m)(_A0), _P0 _a0);
	// const member function call
	template<typename _Object, typename _Class>
	inline bool run(const _Object &_o, _R(_Class::*_m)() const);
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(const _Object &_o, _R(_Class::*_m)(_A0) const, _P0 _a0);
	//
private:
	handle m_thread_h;
	sint m_priority;
	_R m_result;
};
typedef task_<void> task;

#include "thread.inl"

} /* namespace thread ---------------------------------------------------------------------------*/
