/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// task

// _task_result_
template<typename _T> struct _task_result_<_T&> {
	inline _task_result_() : r(*(_T*)0) {}
	inline _task_result_(const _T &_r) : r(_r) {}
	inline _task_result_& operator = (const _T &_r) { this->~_task_result_(); new(this) _T(_r); return *this; }
	inline _T& get() const { return r; }
private:
	_T &r;
};
template<> struct _task_result_<void> {
	inline void get() const {}
};

// _task_helper_
template<typename _F> struct _task_helper_ {
	typedef typename _F::arglist::type arglist;
	template<typename _L> struct args_ : args_<typename _L::rest> {
		typedef typename _L::first type;
		typedef args_<typename _L::rest> parent;
		template<uint _I> struct arg_ {
			typedef typename select<_I == 0, type, typename parent::arg_<_I - 1>::type>::type type;
			typedef typename select<_I == 0, args_, typename parent::arg_<_I - 1>::level>::type level;
		};
		type a;
		inline args_(type _a, parent &_parent) : parent(_parent), a(_a) {}
		typedef typename arg_<0>::type A0;
		typedef typename arg_<1>::type A1;
		typedef typename arg_<2>::type A2;
		typedef typename arg_<3>::type A3;
		typedef typename arg_<4>::type A4;
		typedef typename arg_<5>::type A5;
		typedef typename arg_<6>::type A6;
		typedef typename arg_<7>::type A7;
		typedef typename arg_<8>::type A8;
		typedef typename arg_<9>::type A9;
		static inline args_ build(A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5, A6 _a6, A7 _a7, A8 _a8, A9 _a9) {
			return args_(_a0, parent::build(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, notype()));
		}
	};
	template<> struct args_<typelist<notype> > {
		template<uint _I> struct arg_ {
			typedef notype type;
			typedef arg_ level;
		};
		static inline args_ build(notype, notype, notype, notype, notype, notype, notype, notype, notype, notype) {
			return args_();
		}
	};
	typedef args_<arglist> args;
	typedef _task_result_<typename _F::rettype> R;
	struct data {
		R &r; _F &f; args a;
		inline data(R &_r, _F &_f, const args &_a) : r(_r), f(_f), a(_a) {}
	};
	template<uint _I> static inline typename args::arg_<_I>::type a(args &_a) {
		return static_cast<args::arg_<_I>::level&>(_a).a;
	};
	template<typename _R> struct ret_ {
		template<uint _N> static DWORD __stdcall proc_(handle _data);
		template<> static DWORD __stdcall proc_<0>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<1>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<2>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<3>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<4>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<5>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<6>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<7>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<8>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<9>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a), a<8>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<10>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.r = d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a), a<8>(d.a), a<9>(d.a)); delete &d; return 0;
		}
	};
	template<> struct ret_<void> {
		template<uint _N> static DWORD __stdcall proc_(handle _data);
		template<> static DWORD __stdcall proc_<0>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<1>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<2>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<3>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<4>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<5>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<6>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<7>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<8>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<9>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a), a<8>(d.a)); delete &d; return 0;
		}
		template<> static DWORD __stdcall proc_<10>(handle _data) {
			data &d = *reinterpret_cast<data*>(_data); d.f(a<0>(d.a), a<1>(d.a), a<2>(d.a), a<3>(d.a), a<4>(d.a), a<5>(d.a), a<6>(d.a), a<7>(d.a), a<8>(d.a), a<9>(d.a)); delete &d; return 0;
		}
	};
	typedef typename _F::arg0 A0;
	typedef typename _F::arg1 A1;
	typedef typename _F::arg2 A2;
	typedef typename _F::arg3 A3;
	typedef typename _F::arg4 A4;
	typedef typename _F::arg5 A5;
	typedef typename _F::arg6 A6;
	typedef typename _F::arg7 A7;
	typedef typename _F::arg8 A8;
	typedef typename _F::arg9 A9;
	static inline handle create(uint _s, R &_r, _F &_f, A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5, A6 _a6, A7 _a7, A8 _a8, A9 _a9) {
		return CreateThread(0, _s, &ret_<typename _F::rettype>::proc_<arglist::count>, new data(_r, _f, args::build(_a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9)), CREATE_SUSPENDED, 0);
	}
};

// _start
inline bool _start(handle _thread_h, sint _priority, uint _processor) {
	if(_thread_h == 0) return false;
	SetThreadPriority(_thread_h, (int)_priority);
	SetThreadIdealProcessor(_thread_h, (DWORD)_processor);
	return ResumeThread(_thread_h) != (DWORD)-1;
}

template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9> template<typename _F>
inline task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::task_(_F &_f, sint _priority, uint _stacksize, uint _processor) :
	m_functor(_f), m_handle(0), m_priority(_priority), m_stacksize(_stacksize), m_processor(_processor)
{}
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9> template<typename _O, typename _M>
inline task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::task_(_O &_o, const _M &_m, sint _priority, uint _stacksize, uint _processor) :
	m_functor(_o, _m), m_handle(0), m_priority(_priority), m_stacksize(_stacksize), m_processor(_processor)
{}
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::~task_() {
	if(m_handle != 0) CloseHandle(m_handle);
}

template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline bool task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::run(_A0 _a0, _A1 _a1, _A2 _a2, _A3 _a3, _A4 _a4, _A5 _a5, _A6 _a6, _A7 _a7, _A8 _a8, _A9 _a9) {
	m_handle = _task_helper_<functor>::create(m_stacksize, m_result, m_functor, _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
	return _start(m_handle, m_priority, m_processor);
}

template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline bool task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::done() const {
	assert(m_handle != 0);
	if(WaitForSingleObject(m_handle, 0) == WAIT_TIMEOUT) return false;
	return true;
}
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline _R task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::wait() const {
	assert(m_handle != 0);
	WaitForSingleObject(m_handle, INFINITE);
	return m_result.get();
}
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline void task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::terminate() {
	if(m_handle != 0) { TerminateThread(m_handle, 0); CloseHandle(m_handle); }
}
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline void task_<_R, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9>::clear() {
	if(m_handle != 0) CloseHandle(m_handle);
	m_handle = 0;
}

// event

inline event::event(bool _reset, bool _state) : m_handle(CreateEvent(0, 0, 0, 0)) {
}
inline event::~event() {
	if(m_handle != 0) CloseHandle(m_handle);
}
inline void event::set() {
	if(m_handle != 0) SetEvent(m_handle);
}
inline void event::reset() {
	if(m_handle != 0) ResetEvent(m_handle);
}
inline bool event::wait(real _time) {
	if(m_handle != 0) {
		if(WaitForSingleObject(m_handle, _time < infinity ? DWORD(_time * 1000.f) : INFINITE) == WAIT_TIMEOUT) return false;
		return true;
	}
	return false;
}
