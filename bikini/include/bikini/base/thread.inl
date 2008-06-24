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
		typedef typename select<
			traits<_O>::is_const,
			_R(_O::*)()const,
			_R(_O::*)()
		>::type _M;
		struct data {
			_R &r; _O &o; _M m;
			inline data(_R &_r, _O &_o, _M _m) : r(_r), o(_o), m(_m) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).*(d.m))(); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m), 0, 0);
		}
	};
	template<typename _O, typename _A0> struct o1 {
		typedef typename select<
			traits<_O>::is_const,
			_R(_O::*)(_A0)const,
			_R(_O::*)(_A0)
		>::type _M;
		struct data {
			_R &r; _O &o; _M _m; _A0 a0;
			inline data(_O &_o, _M _m, _A0 _a0) : r(_r), o(_o), m(_m), a0(_a0) {}
		};
		static DWORD WINAPI thread_proc(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = ((d.o).(d.m))(d.a0); delete &d; return 0;
		}
		static inline handle run(_R &_r, _O _o, _M _m, _A0 _a0) {
			return CreateThread(0, 0, &thread_proc, new data(_r, _o, _m, _a0), 0, 0);
		}
	};
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
	return m_result.value();
}
// functor call
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
// function call
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
// member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<_C>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _C, typename _A0>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)(_A0), _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<_C, _A0>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
// const member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)() const) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<const _C>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _C, typename _A0>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)(_A0) const, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<const _C, _A0>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}

// task_<void> specialization
template<>
struct task_<void> : dont_copy {
	inline task_();
	inline task_(sint _priority);
	inline void set_priority(sint _priority);
	inline bool done();
	inline void wait();
	// functor call
	template<typename _Functor>
	inline bool run(const _Functor &_f);
	template<typename _Functor, typename _A0>
	inline bool run(const _Functor &_f, _A0 _a0);
	// function call
	inline bool run(void(&_f)());
	template<typename _A0>
	inline bool run(void(&_f)(_A0), _A0 _a0);
	// member function call
	template<typename _Object, typename _Class>
	inline bool run(_Object &_o, void(_Class::*_m)());
	template<typename _Object, typename _Class, typename _A0>
	inline bool run(_Object &_o, void(_Class::*_m)(_A0), _A0 _a0);
	// const member function call
	template<typename _Object, typename _Class>
	inline bool run(const _Object &_o, void(_Class::*_m)() const);
	template<typename _Object, typename _Class, typename _A0>
	inline bool run(const _Object &_o, void(_Class::*_m)(_A0) const, _A0 _a0);

private:
	handle m_thread_h;
	sint m_priority;
};


// task_<void>
template<>
inline task_<_R>::task_() : m_thread_h(0), m_priority(THREAD_PRIORITY_NORMAL) {
}
template<>
inline task_<_R>::task_(sint _priority) : m_thread_h(0), m_priority(_priority) {
}
template<>
inline void task_<_R>::set_priority(sint _p) {
	m_priority = clamp(_p, THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
}
template<>
inline bool task_<_R>::done() {
	if(WaitForSingleObject(m_thread_h, 0) == WAIT_TIMEOUT) return false;
	return true;
}
template<>
inline _R task_<_R>::wait() {
	assert(m_thread_h != 0);
	WaitForSingleObject(m_thread_h, INFINITE);
	return m_result.value();
}
// functor call
template<> template<typename _F>
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
// function call
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
// member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)()) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<_C>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _C, typename _A0>
inline bool task_<_R>::run(_O &_o, _R(_C::*_m)(_A0), _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<_C, _A0>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
// const member function call
template<typename _R> template<typename _O, typename _C>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)() const) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o0<const _C>::run(m_result, _o, _m);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
template<typename _R> template<typename _O, typename _C, typename _A0>
inline bool task_<_R>::run(const _O &_o, _R(_C::*_m)(_A0) const, _A0 _a0) {
	assert(m_thread_h == 0);
	m_thread_h = _task_helper_<_R>::o1<const _C, _A0>::run(m_result, _o, _m, _a0);
	if(m_thread_h != 0) SetThreadPriority(m_thread_h, (int)m_priority);
	return m_thread_h != 0;
}
