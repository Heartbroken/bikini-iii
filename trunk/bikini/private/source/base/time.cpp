/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/
	
real sys_time() {
	//u32 l_fpcw = _control87(0, 0); _control87(_PC_64, _MCW_PC);
	static LARGE_INTEGER l_clock_freq;
	static bool l_once = (QueryPerformanceFrequency(&l_clock_freq) == TRUE);
	static rbig l_frq = rbig(l_clock_freq.QuadPart);
	LARGE_INTEGER l_clock; QueryPerformanceCounter(&l_clock);
	rbig l_time = rbig(l_clock.QuadPart) / l_frq;
	//_control87(l_fpcw, 0xffffffff);
	return real(l_time);
}

} /* namespace bk -------------------------------------------------------------------------------*/
