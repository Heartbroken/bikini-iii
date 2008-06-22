/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

typedef make_typelist<u8, u16, u32, u64, uint, ubig>::type unsigneds;
typedef make_typelist<s8, s16, s32, s64, sint, sbig>::type signeds;
typedef make_typelist<bool>::type boolean;
typedef make_typelist<f32, f64, real, rbig>::type floats;
typedef make_typelist<bool, u8, u16, u32, u64, uint, ubig, s8, s16, s32, s64, sint, sbig, f32, f64, real, rbig>::type fundamentals;

template<typename _Type> struct traits {
private:
	template<typename _T> struct pointer_traits { static const bool yes = false; typedef notype type; };
	template<typename _T> struct pointer_traits<_T*> { static const bool yes = true; typedef _T type; };

	template<typename _T> struct reference_traits { static const bool yes = false; typedef _T type; };
	template<typename _T> struct reference_traits<_T&> { static const bool yes = true; typedef _T type; };
	template<typename _T> struct reference_traits<const _T&> { static const bool yes = true; typedef _T type; };

	template<typename _T> struct parameter_traits { typedef const _T& type; };
	template<typename _T> struct parameter_traits<_T&> { typedef _T& type; };

	template<typename _T> struct member_ptr_traits { static const bool yes = false; };
	template<typename _T, typename _M> struct member_ptr_traits<_T _M::*> { static const bool yes = true; };
	template<typename _T, typename _M> struct member_ptr_traits<_T _M::*&> { static const bool yes = true; };

	template<typename _T> struct const_traits { static const bool yes = false; typedef _T type; };
	template<typename _T> struct const_traits<const _T> { static const bool yes = true; typedef _T type; };

public:
	static const bool is_pointer = pointer_traits<_Type>::yes;
	typedef typename pointer_traits<_Type>::type pointed;

	static const bool is_reference = reference_traits<_Type>::yes;
	typedef typename reference_traits<_Type>::type referred;

	static const bool is_member_pointer = member_ptr_traits<_Type>::yes;

	static const bool is_const = const_traits<_Type>::yes;
	typedef typename const_traits<_Type>::type nonconst;

	static const bool is_unsigned = unsigneds::type<_Type>::exists;
	static const bool is_signed = signeds::type<_Type>::exists;
	static const bool is_boolean = boolean::type<_Type>::exists;
	static const bool is_integer = is_unsigned || is_signed || is_boolean;
	static const bool is_float = floats::type<_Type>::exists;
	static const bool is_arithmetical = is_integer || is_float;
	static const bool is_fundamental = is_arithmetical /*|| typelist<void>::type<_Type>::exists*/;

	typedef typename select<
		is_arithmetical || is_pointer || is_member_pointer,
		_Type,
		typename parameter_traits<_Type>::type
	>::type parameter;
};