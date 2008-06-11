/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

static void test() {
	real2 a(r2_0), b(r2_1);
	real2 c = a + b;
	c += r2_1;
	a = b - c;
	a -= b;

	matrix_<3, 3, real> m3;
}

} /* namespace bk -------------------------------------------------------------------------------*/
