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
	inline bool run(_R(&_f)());
	template<typename _A0> inline bool run(_R(&_f)(_A0), _A0 _a0);
	template<typename _Object> inline bool run(_Object &_o, _R(_Object::*_m)());
	inline bool done();
	inline _R wait();
private:
	handle m_thread_h;
	sint m_priority;
	_R m_result;
};
typedef task_<void> task;

#include "thread.inl"

} /*---------------------------------------------------------------------------------------------*/

//
//
//
//
///// TODO
//template<typename _Restype>
//struct thread_ {
//	inline thread_();
//	template<typename _Function> bool run(_Function &_f);
//	template<typename _Object, typename _Function> bool run(_Object &_o, const _Function &_f);
//	inline const _Restype& wait() const;
//private:
//	handle m_thread_h;
//	_Restype m_result;
//};
//typedef thread_<bool> thread;
//
//
//// inline
//template<typename _R>
//inline thread_<_R>::thread_() : m_thread_h(0) {
//}
//template<typename _R> template<typename _F>
//inline bool thread_<_R>::run(_F &_f) {
//	struct _l {
//		_R &r; _F &f; _l(_R &_r, _F &_f) : r(_r), f(_f) {}
//		static DWORD WINAPI thread_proc(handle _data) {
//			_l &l = *reinterpret_cast<_l*>(_data);
//			l.r = l.f();
//			return 0;
//		}
//	};
//	m_thread_h = CreateThread(0, 0, &_l::thread_proc, &_l(m_result, _f), 0, 0);
//	return m_thread_h != 0;
//}
//template<typename _R> template<typename _O, typename _F>
//bool thread_<_R>::run(_O &_o, const _F &_f) {
//	struct _l {
//		_R &r; _O &o; const _F &f; _l(_R &_r, _O &_o, const _F &_f) : r(_r), o(_o), f(_f) {}
//		static DWORD WINAPI thread_proc(handle _data) {
//			_l &l = *reinterpret_cast<_l*>(_data);
//			l.r = ((l.o).*(l.f))();
//			return 0;
//		}
//	};
//	m_thread_h = CreateThread(0, 0, &_l::thread_proc, &_l(m_result, _o, _f), 0, 0);
//	return m_thread_h != 0;
//}
//template<typename _R>
//inline const _R& thread_<_R>::wait() const {
//	WaitForSingleObject(m_thread_h, INFINITE);
//	return m_result;
//}
