/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _task_helper_
template<typename _R>
struct _task_helper_ {
	template<typename _F> struct f0 {
		struct data {
			_R &r; _F f;
			inline data(_R &_r, _F _f) : r(_r), f(_f) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(); delete &d; return 0;
		}
		static inline handle run(_R &_r, _F _f) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _f), 0, 0);
		}
	};
	template<typename _F, typename _A0> struct f1 {
		struct data {
			_R &r; _F f; _A0 a0;
			inline data(_R &_r, _F _f, _A0 _a0) : r(_r), f(_f), a0(_a0) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(d.a0); delete &d; return 0;
		}
		static inline handle run(_R &_r, _F _f, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _f, _a0), 0, 0);
		}
	};

	template<typename _O> struct o0 {
		typedef _R(_O::*_M)();
		struct data {
			_O &o; _M _m;
			inline data(_O &_o, _M _m) : o(_o), m(_m) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).(d.m))(); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m), 0, 0);
		}
	};
	template<typename _O, typename _A0> struct o1 {
		typedef _R(_O::*_M)(_A0);
		struct data {
			_O &o; _M _m; _A0 a0;
			inline data(_O &_o, _M _m, _A0 _a0) : o(_o), m(_m), a0(_a0) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).(d.m))(d.a0); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m, _a0), 0, 0);
		}
	};

	//template<typename _F> struct data_;
	//// function call
	//	// _R
	//template<> struct data_<_R(&)()> {
	//	typedef _R(&_F)(); _R &r; _F f;
	//	data_<_R(&)()>(_R &_r, _F _f) : r(_r), f(_f) {}
	//};
	//template<int>
	//static DWORD WINAPI thread_proc_(handle _data) {
	//	data_<_R(&)()> &d = *reinterpret_cast<data_<_R(&)()>*>(_data); d.r = d.f(); delete &d; return 0;
	//}
	//static inline handle run(_R &_r, _R(&_f)()) {
	//	return CreateThread(0, 0, &thread_proc_<0>, new data_<_R(&)()>(_r, _f), 0, 0);
	//}
	//	// _R, _A0
	//template<typename _A0> struct data_<_R(&)(_A0)> {
	//	typedef _R(&_F)(_A0); _R &r; _F f; _A0 a0;
	//	data_<_R(&)(_A0)>(_R &_r, _F _f, _A0 _a0) : r(_r), f(_f), a0(_a0) {}
	//};
	//template<typename _A0> static DWORD WINAPI thread_proc_(handle _data) {
	//	data_<_R(&)(_A0)> &d = *reinterpret_cast<data_<_R(&)(_A0)>*>(_data); d.r = d.f(d.a0); delete &d; return 0;
	//}
	//template<typename _A0>
	//static inline handle run(_R &_r, _R(&_f)(_A0), _A0 _a0) {
	//	return CreateThread(0, 0, &thread_proc_<_A0>, new data_<_R(&)(_A0)>(_r, _f, _a0), 0, 0);
	//}
	//// member function call
	//	// _R, _C
	//template<typename _C> struct data_<_R(_C::*)()> {
	//	typedef _R(_C::*_M)(); _R &r; _C &c; _M m;
	//	data_<_R(_C::*)()>(_R &_r, _C &_c, _M _m) : r(_r), c(_c), m(_m) {}
	//};
	//template<int, typename _C>
	//static DWORD WINAPI thread_proc_(handle _data) {
	//	data_<_R(_C::*)()> &d = *reinterpret_cast<data_<_R(_C::*)()>*>(_data); d.r = ((d.c).*(d.m))(); delete &d; return 0;
	//}
	//template<typename _C>
	//static inline handle run(_R &_r, _C &_c, _R(_C::*_m)()) {
	//	return CreateThread(0, 0, &thread_proc_<0, _C>, new data_<_R(_C::*)()>(_r, _c, _m), 0, 0);
	//}
};
template<>
struct _task_helper_<void> {
	template<typename _F> struct data_;
	// function call
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
	// member function call
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
		// void, _C, _A0
	template<typename _C, typename _A0> struct data_<void(_C::*)(_A0)> {
		typedef void(_C::*_M)(_A0); _C &c; _M m; _A0 a0;
		data_<void(_C::*)(_A0)>(_C &_c, _M _m, _A0 _a0) : c(_c), m(_m), a0(_a0) {}
	};
	template<int, typename _C, typename _A0>
	static DWORD WINAPI thread_proc_(handle _data) {
		data_<void(_C::*)(_A0)> &d = *reinterpret_cast<data_<void(_C::*)(_A0)>*>(_data); ((d.c).*(d.m))(d.a0); delete &d; return 0;
	}
	template<typename _C, typename _A0>
	static inline handle run(_C &_c, void(_C::*_m)(_A0), _A0 _a0) {
		return CreateThread(0, 0, &thread_proc_<0, _C, _A0>, new data_<void(_C::*)(_A0)>(_c, _m, _a0), 0, 0);
	}
};

// task_
template<typename _R>
inline task_<_R>::task_() : m_thread_h(0), m_priority(THREAD_PRIORITY_NORMAL) {
}
template<typename _R>
inline task_<_R>::task_(sint _priority) : m_thread_h(0), m_priority(_priority) {
}
template<typename _R>
inline void task_<_R>::set_priority(sint _p) {
	m_priority = clamp(_p, THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
}
template<typename _R>
inline bool task_<_R>::done() {
	if(WaitForSingleObject(m_thread_h, 0) == WAIT_TIMEOUT) return false;
	return true;
}
template<typename _R>
inline _R task_<_R>::wait() {
	assert(m_thread_h != 0);
	WaitForSingleObject(m_thread_h, INFINITE);
	return m_result;
}
template<typename _R>
inline bool task_<_R>::run(_R(&_f)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f0<_R(&)()>::run(m_result, _f);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _A0>
inline bool task_<_R>::run(_R(&_f)(_A0), _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f1<_R(&)(_A0), _A0>::run(m_result, _f, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _A0, typename _A1>
inline bool task_<_R>::run(_R(&_f)(_A0, _A1), _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _A0, typename _A1, typename _A2>
inline bool task_<_R>::run(_R(&_f)(_A0, _A1, _A2), _A0 _a0, _A1 _a1, _A2 _a2) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _A0, typename _A1, typename _A2, typename _A3>
inline bool task_<_R>::run(_R(&_f)(_A0, _A1, _A2, _A3), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2, _a3);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
inline bool task_<_R>::run(_R(&_f)(_A0, _A1, _A2, _A3, _A4), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2, _a3, _a4);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)(_A0), _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)(_A0, _A1), _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)(_A0, _A1, _A2), _A0 _a0, _A1 _a1, _A2 _a2) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2, typename _A3>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)(_A0, _A1, _A2, _A3), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2, _a3);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
inline bool task_<_R>::run(_O &_o, _R(_O::*_m)(_A0, _A1, _A2, _A3, _A4), _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2, _a3, _a4);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)() const) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)(_A0) const, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<_O, _A0>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)(_A0, _A1) const, _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)(_A0, _A1, _A2) const, _A0 _a0, _A1 _a1, _A2 _a2) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2, typename _A3>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)(_A0, _A1, _A2, _A3) const, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2, _a3);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
inline bool task_<_R>::run(const _O &_o, _R(_O::*_m)(_A0, _A1, _A2, _A3, _A4) const, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _o, _m, _a0, _a1, _a2, _a3, _a4);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F>
inline bool task_<_R>::run(const _F &_f) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f0<_F>::run(m_result, _f);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0>
inline bool task_<_R>::run(const _F &_f, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f1<_F, _A0>::run(m_result, _f, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0, typename _A1>
inline bool task_<_R>::run(const _F &_f, _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0, typename _A1, typename _A2>
inline bool task_<_R>::run(const _F &_f, _A0 _a0, _A1 _a1, _A2 _a2) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0, typename _A1, typename _A2, typename _A3>
inline bool task_<_R>::run(const _F &_f, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2, _a3);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _F, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
inline bool task_<_R>::run(const _F &_f, _A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::run(m_result, _f, _a0, _a1, _a2, _a3, _a4);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}

// task_<void> specialization
template<>
struct task_<void> : dont_copy {
	inline task_() : m_thread_h(0), m_priority(THREAD_PRIORITY_NORMAL) {
	}
	explicit inline task_(sint _priority) : m_thread_h(0), m_priority(_priority) {
	}
	inline void set_priority(sint _p) {
		m_priority = clamp(_p, THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);
		if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	}
	inline bool run(void(&_f)()) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_f);
		if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
		return m_thread_h != 0;
	}
	template<typename _A0>
	inline bool run(void(&_f)(_A0), _A0 _a0) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_f, _a0);
		if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
		return m_thread_h != 0;
	}
	template<typename _O>
	inline bool run(_O &_o, void(_O::*_m)()) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_o, _m);
		if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
		return m_thread_h != 0;
	}
	template<typename _O, typename _A0>
	inline bool run(_O &_o, void(_O::*_m)(_A0), _A0 _a0) {
		assert(m_thread_h == 0);
		m_thread_h = _task_helper_<void>::run(_o, _m, _a0);
		if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
		return m_thread_h != 0;
	}
	inline bool done() {
		if(WaitForSingleObject(m_thread_h, 0) == WAIT_TIMEOUT) return false;
		return true;
	}
	inline void wait() {
		assert(m_thread_h != 0);
		WaitForSingleObject(m_thread_h, INFINITE);
	}
private:
	handle m_thread_h;
	sint m_priority;
};
