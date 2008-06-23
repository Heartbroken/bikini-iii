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
	explicit inline task_(sint _priority);
	inline void set_priority(sint _priority);
	inline bool done();
	inline _R wait();
	// function call
	inline bool run(_R(&_f)());
	template<typename _A0>
	inline bool run(_R(&_f)(_A0), _A0 _a0);
	template<typename _A0, typename _A1>
	inline bool run(_R(&_f)(_A0, _A1), _A0 _a0, _A1 _a1);
	template<typename _A0, typename _A1, typename _A2>
	inline bool run(_R(&_f)(_A0, _A1, _A2), _A0 _a0, _A1 _a1, _A2 _a2);
	template<typename _A0, typename _A1, typename _A2, typename _A3>
	inline bool run(_R(&_f)(_A0, _A1, _A2, _A3), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3);
	template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
	inline bool run(_R(&_f)(_A0, _A1, _A2, _A3, _A4), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4);
	// member function call
	template<typename _Object>
	inline bool run(_Object &_o, _R(_Object::*_m)());
	template<typename _Object, typename _A0>
	inline bool run(_Object &_o, _R(_Object::*_m)(_A0), _A0 _a0);
	template<typename _Object, typename _A0, typename _A1>
	inline bool run(_Object &_o, _R(_Object::*_m)(_A0, _A1), _A0 _a0, _A1 _a1);
	template<typename _Object, typename _A0, typename _A1, typename _A2>
	inline bool run(_Object &_o, _R(_Object::*_m)(_A0, _A1, _A2), _A0 _a0, _A1 _a1, _A2 _a2);
	template<typename _Object, typename _A0, typename _A1, typename _A2, typename _A3>
	inline bool run(_Object &_o, _R(_Object::*_m)(_A0, _A1, _A2, _A3), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3);
	template<typename _Object, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
	inline bool run(_Object &_o, _R(_Object::*_m)(_A0, _A1, _A2, _A3, _A4), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4);
	// const member function call
	template<typename _Object>
	inline bool run(const _Object &_o, _R(_Object::*_m)() const);
	template<typename _Object, typename _A0>
	inline bool run(const _Object &_o, _R(_Object::*_m)(_A0) const, _A0 _a0);
	template<typename _Object, typename _A0, typename _A1>
	inline bool run(const _Object &_o, _R(_Object::*_m)(_A0, _A1) const, _A0 _a0, _A1 _a1);
	template<typename _Object, typename _A0, typename _A1, typename _A2>
	inline bool run(const _Object &_o, _R(_Object::*_m)(_A0, _A1, _A2) const, _A0 _a0, _A1 _a1, _A2 _a2);
	template<typename _Object, typename _A0, typename _A1, typename _A2, typename _A3>
	inline bool run(const _Object &_o, _R(_Object::*_m)(_A0, _A1, _A2, _A3) const, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3);
	template<typename _Object, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
	inline bool run(const _Object &_o, _R(_Object::*_m)(_A0, _A1, _A2, _A3, _A4) const, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4);
	// functor call
	template<typename _Functor>
	inline bool run(const _Functor &_f);
	template<typename _Functor, typename _A0>
	inline bool run(const _Functor &_f, _A0 _a0);
	template<typename _Functor, typename _A0, typename _A1>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1);
	template<typename _Functor, typename _A0, typename _A1, typename _A2>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1, _A2 _a2);
	template<typename _Functor, typename _A0, typename _A1, typename _A2, typename _A3>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3);
	template<typename _Functor, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4);
	//
private:
	handle m_thread_h;
	sint m_priority;
	_R m_result;
};
typedef task_<void> task;

#include "thread.inl"

} /* namespace thread ---------------------------------------------------------------------------*/
