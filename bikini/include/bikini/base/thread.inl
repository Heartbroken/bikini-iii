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
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(); delete &d; return 0;
		}
		static inline handle run(_R &_r, _F _f) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _f), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _F, typename _A0> struct f1 {
		struct data {
			_R &r; _F f; _A0 a0;
			inline data(_R &_r, _F _f, _A0 _a0) : r(_r), f(_f), a0(_a0) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(d.a0); delete &d; return 0;
		}
		static inline handle run(_R &_r, _F _f, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _f, _a0), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _F, typename _A0, typename _A1> struct f2 {
		struct data {
			_R &r; _F f; _A0 a0; _A1 a1;
			inline data(_R &_r, _F _f, _A0 _a0, _A1 _a1) : r(_r), f(_f), a0(_a0), a1(_a1) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(d.a0, d.a1); delete &d; return 0;
		}
		static inline handle run(_R &_r, _F _f, _A0 _a0, _A1 _a1) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _f, _a0, _a1), CREATE_SUSPENDED, 0);
		}
	};

	template<typename _O> struct o0 {
		typedef typename select<
			traits<_O>::is_const,
			_R(_O::*)()const,
			_R(_O::*)()
		>::type _M;
		struct data {
			_R &r; _O &o; _M m;
			inline data(_R &_r, _O &_o, _M _m) : r(_r), o(_o), m(_m) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).*(d.m))(); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _O, typename _A0> struct o1 {
		typedef typename select<
			traits<_O>::is_const,
			_R(_O::*)(_A0)const,
			_R(_O::*)(_A0)
		>::type _M;
		struct data {
			_R &r; _O &o; _M m; _A0 a0;
			inline data(_R &_r, _O &_o, _M _m, _A0 _a0) : r(_r), o(_o), m(_m), a0(_a0) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).*(d.m))(d.a0); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m, _a0), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _O, typename _A0, typename _A1> struct o2 {
		typedef typename select<
			traits<_O>::is_const,
			_R(_O::*)(_A0, _A1)const,
			_R(_O::*)(_A0, _A1)
		>::type _M;
		struct data {
			_R &r; _O &o; _M m; _A0 a0; _A1 a1;
			inline data(_R &_r, _O &_o, _M _m, _A0 _a0, _A1 _a1) : r(_r), o(_o), m(_m), a0(_a0), a1(_a1) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).*(d.m))(d.a0, d.a1); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m, _A0 _a0, _A1 _a1) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m, _a0, _a1), CREATE_SUSPENDED, 0);
		}
	};
};

// _start
inline bool _start(handle _thread_h, sint _priority, uint _processor) {
	if(_thread_h == 0) return false;
	SetThreadPriority(_thread_h, (int)_priority);
	SetThreadIdealProcessor(_thread_h, (DWORD)_processor);
	return ResumeThread(_thread_h) != (DWORD)-1;
}

// task_
template<typename _R>
inline task_<_R>::task_(sint _priority, uint _processor) : m_thread_h(0), m_priority(_priority), m_processor(_processor) {
}
template<typename _R>
inline bool task_<_R>::done() {
	assert(m_thread_h != 0);
	if(WaitForSingleObject(m_thread_h, 0) == WAIT_TIMEOUT) return false;
	return true;
}
template<typename _R>
inline _R task_<_R>::wait() {
	assert(m_thread_h != 0);
	WaitForSingleObject(m_thread_h, INFINITE);
	return m_result;
}
// functor call
template<typename _R> template<typename _F>
inline bool task_<_R>::run(const _F &_f) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f0<_F>::run(m_result, _f);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _F, typename _A0>
inline bool task_<_R>::run(const _F &_f, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f1<_F, _A0>::run(m_result, _f, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _F, typename _A0, typename _A1>
inline bool task_<_R>::run(const _F &_f, _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f2<_F, _A0, _A1>::run(m_result, _f, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// function call
template<typename _R>
inline bool task_<_R>::run(_R(&_f)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f0<_R(&)()>::run(m_result, _f);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _A0, typename _P0>
inline bool task_<_R>::run(_R(&_f)(_A0), _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f1<_R(&)(_A0), _A0>::run(m_result, _f, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<_R>::run(_R(&_f)(_A0, _A1), _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::f2<_R(&)(_A0, _A1), _A0, _A1>::run(m_result, _f, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<_C>::run(m_result, _o, _m);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _O, typename _C, typename _A0, typename _P0>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)(_A0), _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<_C, _A0>::run(m_result, _o, _m, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _O, typename _C, typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)(_A0, _A1), _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o2<_C, _A0, _A1>::run(m_result, _o, _m, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// const member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)() const) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<const _C>::run(m_result, _o, _m);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _O, typename _C, typename _A0, typename _P0>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)(_A0) const, _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<const _C, _A0>::run(m_result, _o, _m, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _R> template<typename _O, typename _C, typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)(_A0, _A1) const, _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o2<const _C, _A0, _A1>::run(m_result, _o, _m, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}

// task_<void> specialization
template<>
struct task_<void> : uncopyble {
	inline task_(sint _priority = THREAD_PRIORITY_NORMAL, uint _processor = bad_ID);
	inline bool done();
	inline void wait();
	// functor call
	template<typename _Functor>
	inline bool run(const _Functor &_f);
	template<typename _Functor, typename _A0>
	inline bool run(const _Functor &_f, _A0 _a0);
	template<typename _Functor, typename _A0, typename _A1>
	inline bool run(const _Functor &_f, _A0 _a0, _A1 _a1);
	// function call
	inline bool run(void(&_f)());
	template<typename _A0, typename _P0>
	inline bool run(void(&_f)(_A0), _P0 _a0);
	template<typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(void(&_f)(_A0, _A1), _P0 _a0, _P1 _a1);
	// member function call
	template<typename _Object, typename _Class>
	inline bool run(_Object &_o, void(_Class::*_m)());
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(_Object &_o, void(_Class::*_m)(_A0), _P0 _a0);
	template<typename _Object, typename _Class, typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(_Object &_o, void(_Class::*_m)(_A0, _A1), _P0 _a0, _P1 _a1);
	// const member function call
	template<typename _Object, typename _Class>
	inline bool run(const _Object &_o, void(_Class::*_m)() const);
	template<typename _Object, typename _Class, typename _A0, typename _P0>
	inline bool run(const _Object &_o, void(_Class::*_m)(_A0) const, _P0 _a0);
	template<typename _Object, typename _Class, typename _A0, typename _A1, typename _P0, typename _P1>
	inline bool run(const _Object &_o, void(_Class::*_m)(_A0, _A1) const, _P0 _a0, _P1 _a1);

private:
	handle m_thread_h;
	sint m_priority;
	uint m_processor;
};

template<>
struct _task_helper_<void> {
	template<typename _F> struct f0 {
		struct data {
			_F f;
			inline data(_F _f) : f(_f) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(); delete &d; return 0;
		}
		static inline handle run(_F _f) {
			return CreateThread(0, 0, &thread_proc, new data(_f), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _F, typename _A0> struct f1 {
		struct data {
			_F f; _A0 a0;
			inline data(_F _f, _A0 _a0) : f(_f), a0(_a0) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(d.a0); delete &d; return 0;
		}
		static inline handle run(_F _f, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_f, _a0), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _F, typename _A0, typename _A1> struct f2 {
		struct data {
			_F f; _A0 a0; _A1 a1;
			inline data(_F _f, _A0 _a0, _A1 _a1) : f(_f), a0(_a0), a1(_a1) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(d.a0, d.a1); delete &d; return 0;
		}
		static inline handle run(_F _f, _A0 _a0, _A0 _a1) {
			return CreateThread(0, 0, &thread_proc, new data(_f, _a0, _a1), CREATE_SUSPENDED, 0);
		}
	};

	template<typename _O> struct o0 {
		typedef typename select<
			traits<_O>::is_const,
			void(_O::*)()const,
			void(_O::*)()
		>::type _M;
		struct data {
			_O &o; _M m;
			inline data(_O &_o, _M _m) : o(_o), m(_m) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); ((d.o).*(d.m))(); delete &d; return 0;
		}
		static inline handle run(_O _o, _M _m) {
			return CreateThread(0, 0, &thread_proc, new data(_o, _m), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _O, typename _A0> struct o1 {
		typedef typename select<
			traits<_O>::is_const,
			void(_O::*)(_A0)const,
			void(_O::*)(_A0)
		>::type _M;
		struct data {
			_O &o; _M m; _A0 a0;
			inline data(_O &_o, _M _m, _A0 _a0) : o(_o), m(_m), a0(_a0) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); ((d.o).*(d.m))(d.a0); delete &d; return 0;
		}
		static inline handle run(_O _o, _M _m, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_o, _m, _a0), CREATE_SUSPENDED, 0);
		}
	};
	template<typename _O, typename _A0, typename _A1> struct o2 {
		typedef typename select<
			traits<_O>::is_const,
			void(_O::*)(_A0, _A1)const,
			void(_O::*)(_A0, _A1)
		>::type _M;
		struct data {
			_O &o; _M m; _A0 a0; _A1 a1;
			inline data(_O &_o, _M _m, _A0 _a0, _A1 _a1) : o(_o), m(_m), a0(_a0), a1(_a1) {}
		};
		static DWORD __stdcall thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); ((d.o).*(d.m))(d.a0, d.a1); delete &d; return 0;
		}
		static inline handle run(_O _o, _M _m, _A0 _a0, _A1 _a1) {
			return CreateThread(0, 0, &thread_proc, new data(_o, _m, _a0, _a1), CREATE_SUSPENDED, 0);
		}
	};
};

// task_<void>
inline task_<void>::task_(sint _priority, uint _processor) : m_thread_h(0), m_priority(_priority), m_processor(_processor) {
}
inline bool task_<void>::done() {
	assert(m_thread_h != 0);
	if(WaitForSingleObject(m_thread_h, 0) == WAIT_TIMEOUT) return false;
	return true;
}
inline void task_<void>::wait() {
	assert(m_thread_h != 0);
	WaitForSingleObject(m_thread_h, INFINITE);
}
// functor call
template<typename _F>
inline bool task_<void>::run(const _F &_f) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f0<_F>::run(_f);
	return_start(m_thread_h, m_priority, m_processor);
}
template<typename _F, typename _A0>
inline bool task_<void>::run(const _F &_f, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f1<_F, _A0>::run(_f, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _F, typename _A0, typename _A1>
inline bool task_<void>::run(const _F &_f, _A0 _a0, _A1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f2<_F, _A0, _A1>::run(_f, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// function call
inline bool task_<void>::run(void(&_f)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f0<void(&)()>::run(_f);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _A0, typename _P0>
inline bool task_<void>::run(void(&_f)(_A0), _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f1<void(&)(_A0), _A0>::run(_f, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<void>::run(void(&_f)(_A0, _A1), _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::f2<void(&)(_A0, _A1), _A0, _A1>::run(_f, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// member function call
template<typename _O, typename _C>
inline bool task_<void>::run(_O &_o, void(_C::*_m)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o0<_C>::run(_o, _m);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _O, typename _C, typename _A0, typename _P0>
inline bool task_<void>::run(_O &_o, void(_C::*_m)(_A0), _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o1<_C, _A0>::run(_o, _m, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _O, typename _C, typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<void>::run(_O &_o, void(_C::*_m)(_A0, _A1), _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o2<_C, _A0, _A1>::run(_o, _m, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
// const member function call
template<typename _O, typename _C>
inline bool task_<void>::run(const _O &_o, void(_C::*_m)() const) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o0<const _C>::run(_o, _m);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _O, typename _C, typename _A0, typename _P0>
inline bool task_<void>::run(const _O &_o, void(_C::*_m)(_A0) const, _P0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o1<const _C, _A0>::run(_o, _m, _a0);
	return _start(m_thread_h, m_priority, m_processor);
}
template<typename _O, typename _C, typename _A0, typename _A1, typename _P0, typename _P1>
inline bool task_<void>::run(const _O &_o, void(_C::*_m)(_A0, _A1) const, _P0 _a0, _P1 _a1) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<void>::o2<const _C, _A0, _A1>::run(_o, _m, _a0, _a1);
	return _start(m_thread_h, m_priority, m_processor);
}
