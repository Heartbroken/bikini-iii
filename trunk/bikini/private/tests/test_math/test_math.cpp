// test_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bk::real3 l_b(bk::r3_1);
	bk::uint l_count = 1000000;
	while(--l_count) {
		//bk::real3 l_tmp = l_b * bk::r3x3_1;
		bk::real3 l_tmp;
		l_b.mul(bk::r3x3_1, l_tmp);
		l_b += l_tmp;
	}
	std::cout << bk::real(l_b[0][0]) << bk::real(l_b[0][1]) << bk::real(l_b[0][2]);
	return 0;
}

