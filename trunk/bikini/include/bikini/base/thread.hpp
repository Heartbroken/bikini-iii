/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace thread { /*----------------------------------------------------------------------------*/

/// task_
template<typename _R>
struct task_ : uncopyble {
	inline task_(sint _priority = THREAD_PRIORITY_NORMAL, uint _processor = bad_ID);
	inline ~task_();
	inline bool done() const;
	inline _R wait() const;
	inline void terminate();
	inline void clear();
	// functor call
	template<typename _Functor>
	inline bool run(const _Functor &_f);
	template<typename _Functor, typename _A0>
	inline bool run(const _Functor &_f, _A0 _a0);
	template<typename _Functor, typename _A0, typename _A1>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1);
	// function call
	inline bool run(_R(&_f)());
	template<typename _A0, typename _P0>
	inline bool run(_R(&_f)(_A0), _P0 _a0);
	template<typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(_R(&_f)(_A0, _A1), _P0 _a0, _P1 _a1);
	// member function call
	template<typename _Object, typename _Class>
	inline bool run(_Object &_o, _R(_Class::*_m)());
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(_Object &_o, _R(_Class::*_m)(_A0), _P0 _a0);
	template<typename _Object, typename _Class, typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(_Object &_o, _R(_Class::*_m)(_A0, _A1), _P0 _a0, _P1 _a1);
	// const member function call
	template<typename _Object, typename _Class>
	inline bool run(const _Object &_o, _R(_Class::*_m)() const);
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(const _Object &_o, _R(_Class::*_m)(_A0) const, _P0 _a0);
	template<typename _Object, typename _Class, typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(const _Object &_o, _R(_Class::*_m)(_A0, _A1) const, _P0 _a0, _P1 _a1);
	//
private:
	handle m_handle;
	sint m_priority;
	uint m_processor;
	_R m_result;
};
typedef task_<void> task;

#include "thread.inl"

} /* namespace thread ---------------------------------------------------------------------------*/
