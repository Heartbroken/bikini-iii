/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef halt
#	undef halt
#endif
#ifdef assert
#	undef assert
#endif

bool ARI(char* _expression, char* _file, int _line, char* _function, char* _message = 0);
bool ARI2(char* _expression, char* _file, int _line, char* _function, char* _message = 0);

#define halt { Sleep(1); __asm int 3 }

#ifdef _DEBUG
#	define assert(E)	while(!(E)) { if(bk::ARI(#E, __FILE__, __LINE__, __FUNCTION__)) break; halt; }
#else
#	define assert(E)
#endif

template<bool> struct compile_time_assert;
template<> struct compile_time_assert<true> {};

#define c_assert(E)	{ bk::compile_time_assert<((E) != 0)> COMPILE_TIME_ERROR; COMPILE_TIME_ERROR; }
