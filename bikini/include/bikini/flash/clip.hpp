/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct clip : player::object {
	struct info : player::object::info {
		typedef clip object;
		typedef uint a0;
		info(movie::info &_movie, swfstream &_s);
	private:
		uint m_frame_count;
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	clip(const info &_info, player &_player, uint _movie_ID);
	~clip();
private:
	uint m_movie_ID;
};
