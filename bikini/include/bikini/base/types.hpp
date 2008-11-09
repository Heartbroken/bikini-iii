/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// types with exact size
typedef unsigned char		u8, byte;
typedef char				s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;
typedef unsigned __int64	u64;
typedef __int64				s64;
typedef float				f32;
typedef double				f64;

/// string
typedef std::string			str;

/// unsigned integer number
typedef uintptr_t			uint;
/// signed integer number
typedef intptr_t			sint;
/// big unsigned integer number
typedef unsigned __int64	ubig;
/// big signed integer number
typedef __int64				sbig;
/// big real number
typedef double				rbig;
/// real number
#if defined(BIKINI_REAL_IS_DOUBLE)
typedef double				real;
#else
typedef float				real;
#endif

typedef void*				handle;
typedef const void*			pointer;

typedef std::string			astr;
typedef std::wstring		wstr;

/// type selector template
template<bool _C, typename _T0, typename _T1>
struct select_ {
	typedef _T0 type;
};
template<typename _T0, typename _T1>
struct select_<false, _T0, _T1> {
	typedef _T1 type;
};

/// uncopyble type
struct uncopyble {
	inline uncopyble() {}
private:
	inline uncopyble(const uncopyble&);
	inline uncopyble& operator = (const uncopyble&);
};

/// notype type
struct notype {};
