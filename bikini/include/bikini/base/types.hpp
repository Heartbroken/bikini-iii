/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// old types
typedef unsigned char		u8;
typedef char				s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;
typedef unsigned __int64	u64;
typedef __int64				s64;
typedef float				f32;
typedef double				f64;
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
#if defined(BIKINI_REAL_IS_DOUBLE)
/// real number
typedef double				real;
#else
/// real number
typedef float				real;
#endif

typedef void*				handle;
typedef const void*			pointer;

typedef std::string			astr;
typedef std::wstring		wstr;

// constants

/// bad GUID
const GUID bad_GUID = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
/// bad ID
const uint bad_ID = uint(-1);
/// real 0
const real r_0 = real(0);
/// real 1
const real r_1 = real(1);

// defines

#define super __super
#define inline __forceinline

// templates

/// type selector template
template<bool _C, typename _T0, typename _T1> struct select { typedef _T0 type; };
template<typename _T0, typename _T1> struct select<false, _T0, _T1> { typedef _T1 type; };

struct uncopyble {
	inline uncopyble() {}
private:
	inline uncopyble(const uncopyble&);
	inline uncopyble& operator = (const uncopyble&);
};