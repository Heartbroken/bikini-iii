// test_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bk::vector3 l_0(bk::v3_0), l_1(bk::v3_1);
	bk::vector3 l_a = l_0 + l_1;
	bk::vector3 l_b(l_a);
	bk::real l_r = l_b.x;
	bk::uint l_size = sizeof(bk::vector3);
	l_size = sizeof(bk::vector_<3>);
	return 0;
}

