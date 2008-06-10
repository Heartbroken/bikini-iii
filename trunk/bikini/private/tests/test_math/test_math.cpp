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
	return 0;
}

