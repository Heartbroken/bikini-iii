/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct shape : player::object {
	struct info : player::object::info {
		typedef shape object;
		info(swfstream &_s, tag::type _type);
	private:
		rect m_rect;
	};
	shape(const info &_info, player &_player);
	~shape();
private:
};
