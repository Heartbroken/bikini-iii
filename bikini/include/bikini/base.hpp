/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "base_d")
#else
#	pragma comment(lib, "base")
#endif

#include "config.hpp"

#if defined(_WIN32)
#	include "base/system_win32.hpp"
#endif

#include <math.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

/// bikini-iii main namespace
namespace bk { /*--------------------------------------------------------------------------------*/

#include "base/assert.hpp"
#include "base/types.hpp"
#include "base/typelist.hpp"
#include "base/traits.hpp"
#include "base/math.hpp"
#include "base/time.hpp"

} /* namespace bk -------------------------------------------------------------------------------*/
