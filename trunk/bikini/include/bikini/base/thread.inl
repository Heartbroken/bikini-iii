/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _task_helper_
template<typename _R>
struct _task_helper_ {
	template<typename _F> struct data_;
	// _R
	template<> struct data_<_R(&)()> {
		typedef _R(&_F)(); _R &r; _F f;
		data_<_R(&)()>(_R &_r, _F _f) : r(_r), f(_f) {}
	};
	template<int>
	static DWORD WINAPI thread_proc_(handle _data) {
		data_<_R(&)()> &d = *reinterpret_cast<data_<_R(&)()>*>(_data); d.r = d.f(); delete &d; return 0;
	}
	static inline handle run(_R &_r, _R(&_f)()) {
		return CreateThread(0, 0, &thread_proc_<0>, new data_<_R(&)()>(_r, _f), 0, 0);
	}
	// _R, _A0
	template<typename _A0> struct data_<_R(&)(_A0)> {
		typedef _R(&_F)(_A0); _R &r; _F f; _A0 a0;
		data_<_R(&)(_A0)>(_R &_r, _F _f, _A0 _a0) : r(_r), f(_f), a0(_a0) {}
	};
	template<typename _A0> static DWORD WINAPI thread_proc_(handle _data) {
		data_<_R(&)(_A0)> &d = *reinterpret_cast<data_<_R(&)(_A0)>*>(_data); d.r = d.f(d.a0); delete &d; return 0;
	}
	template<typename _A0>
	static inline handle run(_R &_r, _R(&_f)(_A0), _A0 _a0) {
		return CreateThread(0, 0, &thread_proc_<_A0>, new data_<_R(&)(_A0)>(_r, _f, _a0), 0, 0);
	}
	// _R, _C
	template<typename _C> struct data_<_R(_C::*)()> {
		typedef _R(_C::*_M)(); _R &r; _C &c; _M m;
		data_<_R(_C::*)()>(_R &_r, _C &_c, _M _m) : r(_r), c(_c), m(_m) {}
	};
	template<int, typename _C>
	static DWORD WINAPI thread_proc_(handle _data) {
		data_<_R(_C::*)()> &d = *reinterpret_cast<data_<_R(_C::*)()>*>(_data); d.r = ((d.c).*(d.m))(); delete &d; return 0;
	}
	template<typename _C>
	static inline handle run(_R &_r, _C &_c, _R(_C::*_m)()) {
		return CreateThread(0, 0, &thread_proc_<0, _C>, new data_<_R(_C::*)()>(_r, _c, _m), 0, 0);
	}
};
template<>
struct _task_helper_<void> {
	template<typename _F> struct data_;
	// void
	template<> struct data_<void(&)()> {
		typedef void(&_F)(); _F f;
		data_<void(&)()>(_F _f) : f(_f) {}
	};
	template<int>
	static DWORD WINAPI thread_proc_(handle _data) {
		data_<void(&)()> &d = *reinterpret_cast<data_<void(&)()>*>(_data); d.f(); delete &d; return 0;
	}
	static inline handle run(void(&_f)()) {
		return CreateThread(0, 0, &thread_proc_<0>, new data_<void(&)()>(_f), 0, 0);
	}
	// void, _A0
	template<typename _A0> struct data_<void(&)(_A0)> {
		typedef void(&_F)(_A0); _F f; _A0 a0;
		data_<void(&)(_A0)>(_F _f, _A0 _a0) : f(_f), a0(_a0) {}
	};
	template<typename _A0> static DWORD WINAPI thread_proc_(handle _data) {
		data_<void(&)(_A0)> &d = *reinterpret_cast<data_<void(&)(_A0)>*>(_data); d.f(d.a0); delete &d; return 0;
	}
	template<typename _A0>
	static inline handle run(void(&_f)(_A0), _A0 _a0) {
		return CreateThread(0, 0, &thread_proc_<_A0>, new data_<void(&)(_A0)>(_f, _a0), 0, 0);
	}
	// void, _C
	template<typename _C> struct data_<void(_C::*)()> {
		typedef void(_C::*_M)(); _C &c; _M m;
		data_<void(_C::*)()>(_C &_c, _M _m) : c(_c), m(_m) {}
	};
	template<int, typename _C>
	static DWORD WINAPI thread_proc_(handle _data) {
		data_<void(_C::*)()> &d = *reinterpret_cast<data_<void(_C::*)()>*>(_data); ((d.c).*(d.m))(); delete &d; return 0;
	}
	template<typename _C>
	static inline handle run(_C &_c, void(_C::*_m)()) {
		return CreateThread(0, 0, &thread_proc_<0, _C>, new data_<void(_C::*)()>(_c, _m), 0, 0);
	}
};

// task_
template<typename _R>
inline task_<_R>::task_() : m_thread_h(0) {}

template<typename _R> template<typename _F>
inline bool task_<_R>::run_function(_F &_f) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0>
inline bool task_<_R>::run_function(_F &_f, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _M>
inline bool task_<_R>::run_method(_O &_o, const _M &_m) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m);
	return m_thread_h != 0;
}
template<typename _R>
inline _R task_<_R>::wait() {
	assert(m_thread_h != 0);
	WaitForSingleObject(m_thread_h, INFINITE);
	return m_result;
}

// task_<void> specialization
template<>
struct task_<void> {
	inline task_() : m_thread_h(0) {}
	template<typename _F>
	inline bool run_function(_F &_f) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_f);
		return m_thread_h != 0;
	}
	template<typename _F, typename _A0>
	inline bool run_function(_F &_f, _A0 _a0) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_f, _a0);
		return m_thread_h != 0;
	}
	template<typename _O, typename _M>
	inline bool run_method(_O &_o, const _M &_m) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_o, _m);
		return m_thread_h != 0;
	}
	inline void wait() {
		assert(m_thread_h != 0);
		WaitForSingleObject(m_thread_h, INFINITE);
	}
private:
	handle m_thread_h;
};
