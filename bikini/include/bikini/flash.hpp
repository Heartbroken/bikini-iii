/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "flash_d")
#else
#	pragma comment(lib, "flash")
#endif

#include "base.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

#include "flash/loader.hpp"
#include "flash/renderer.hpp"
#include "flash/swftagtypes.hpp"
#include "flash/swfstream.hpp"
#include "flash/player.hpp"
#include "flash/actionscript.hpp"
#include "flash/objects.hpp"

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
