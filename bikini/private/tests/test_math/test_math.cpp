// test_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bk::real3 l_0(bk::r3_0), l_1(bk::r3_1);
	bk::real3 l_a = l_0 + l_1;
	bk::real3 l_b(l_a);
	bk::real l_r = l_b[0];
	bk::uint l_size = sizeof(bk::real3);
	l_size = sizeof(bk::vector_<3>);
	bk::real2 l_r2;
	bk::v2(l_r2).x = bk::v2(bk::r2_0).x;
	bk::v2(l_r2).y = 0;
//	bk::v2(bk::r2_0).x = bk::real(1);
	l_r2 = bk::r2_0;
	bk::real3x3 m3;
	l_size = sizeof(m3);
	return 0;
}

