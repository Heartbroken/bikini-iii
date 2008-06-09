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
typedef float				real;

typedef void*				handle;
typedef const void*			pointer;

const GUID bad_GUID = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
const uint bad_ID = uint(-1);

const real r_0 = real(0);
const real r_1 = real(1);

#define super	__super
#define inline	__forceinline
