/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct movie : player::object {
	struct info : player::object::info {
		typedef movie object;
		inline uint define_count() const;
		inline uint define_type(uint _i) const;
		template<typename _Type> inline const typename _Type::info& get_define(uint _i) const;
		info(swfstream &_s);
		~info();
		void define_shape(swfstream &_s, tag::type _type);
		void define_clip(swfstream &_s);
	private:
		sint2 m_frame_size; real m_frame_rate;
		std::vector<player::object::info*> m_defines;
	};
	movie(const info &_info, player &_player);
	~movie();
private:
	uint m_clip_ID;
};

#include "movie.inl"