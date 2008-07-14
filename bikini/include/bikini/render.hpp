/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "render_d")
#else
#	pragma comment(lib, "render")
#endif

#include "base.hpp"

#include <d3d9.h>

namespace bk { /*--------------------------------------------------------------------------------*/

#include "render/resource.hpp"
#include "render/video.hpp"
#include "render/window.hpp"

} /* namespace bk -------------------------------------------------------------------------------*/
