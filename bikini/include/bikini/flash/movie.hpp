/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct movie : player::object {
	struct info : player::object::info {
		typedef movie object;
		typedef const wchar* a0;
		info();
	};
	movie(const info &_info, player &_player, const wchar* _path);
	~movie();
	void define_shape(uint _swfstream_ID, tag::code _type);
	void define_clip(uint _swfstream_ID);
private:
	sint2 m_frame_size;
	real m_frame_rate;
	uint m_mainclip_ID;
	std::vector<uint> m_defines;
};

#include "movie.inl"