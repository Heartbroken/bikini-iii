/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if !defined(XBOX)
#	error Wrong system include!!!
#endif

#include "Xtl.h"

#ifdef min
#	undef min
#endif

#ifdef max
#	undef max
#endif

#ifdef _T
#	undef _T
#endif

#ifdef UNICODE
#	undef UNICODE
#endif

/// bad GUID
const GUID bad_GUID = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
