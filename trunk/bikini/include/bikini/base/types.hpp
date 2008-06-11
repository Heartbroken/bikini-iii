/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned __int64	u64;
typedef char				s8;
typedef short				s16;
typedef int					s32;
typedef __int64				s64;
typedef float				f32;
typedef double				f64;

typedef size_t				uint;
typedef ptrdiff_t			sint;
#if defined(BIKINI_REAL_IS_DOUBLE)
	typedef double			real;
#else
	typedef float			real;
#endif
typedef double				rbig;

typedef void*				handle;
typedef const void*			pointer;

const GUID bad_GUID = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
const uint bad_ID = uint(-1);

const real r_0 = real(0);
const real r_1 = real(1);

#define super	__super
#define inline	__forceinline

template<bool _C, typename _T0, typename _T1> struct select { typedef _T0 type; };
template<typename _T0, typename _T1> struct select<false, _T0, _T1> { typedef _T1 type; };
