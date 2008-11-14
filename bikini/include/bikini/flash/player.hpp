/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	flash player
/**	[TODO]
 */
struct player : manager {
	struct object : manager::object {
		struct info : manager::object::info {
			typedef player manager;
			info(uint _type);
		};
	};
};