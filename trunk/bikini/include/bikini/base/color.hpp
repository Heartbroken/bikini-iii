/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// color
template<typename _Type>
struct color_ : matrix_<1, 4, _Type> {
	inline color_();
	inline color_(_Type _r, _Type _g, _Type _b, _Type _a = _Type(1));
	inline color_(u32 _c);
	inline const _Type r() const;
	inline _Type& r();
	inline const _Type g() const;
	inline _Type& g();
	inline const _Type b() const;
	inline _Type& b();
	inline const _Type a() const;
	inline _Type& a();
	inline operator u32 () const;
};
typedef color_<real> color;

const color white(r_1, r_1, r_1);
const color black(r_0, r_0, r_0);
const color red(r_1, r_0, r_0);
const color green(r_0, r_1, r_0);
const color blue(r_0, r_0, r_1);
const color yellow(r_1, r_1, r_0);
const color cyan(r_0, r_1, r_1);
const color magenta(r_1, r_0, r_1);

#include "color.inl"
