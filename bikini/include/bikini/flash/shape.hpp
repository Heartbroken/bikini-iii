/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct shape : player::object {
	struct info : player::object::info {
		typedef shape object;
		typedef uint a0;
		typedef tag::code a1;
		info();
	};
	shape(const info &_info, player &_player, uint _swfstream_ID, tag::code _type);
	~shape();
private:
	uint m_swfstream_ID;
	rect m_rect;
};
