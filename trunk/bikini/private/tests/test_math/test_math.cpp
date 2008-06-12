// test_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	{
	bk::r1x3 l_b(-bk::r1x3_1);
	bk::r3x3 l_r(bk::r1x3_x, -bk::r1x3_z, bk::r1x3_y);
	bk::real l_00 = l_b[0][0];
	bk::uint l_count = 1000000;
	bk::rbig l_time = bk::sys_time();
	while(--l_count) {
		l_b = l_b * l_r;
	}
	l_time = bk::sys_time() - l_time;
	std::cout << bk::real(l_b[0][0]) << " " << bk::real(l_b[0][1]) << " " << bk::real(l_b[0][2]) << "\n";
	std::cout << l_time << "\n";
	}
	return 0;
}

