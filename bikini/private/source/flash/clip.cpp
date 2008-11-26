/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// record

struct record {
	tag::type type; uint length;
};
static record RECORD(swfstream &_s) {
	record l_v;
	uint l_c = _s.UI16();
	l_v.type = (tag::type)((l_c & 0xffc0) >> 6);
	l_v.length = l_c & 0x3f;
	if(l_v.length == 0x3f) {
		sint l_l = _s.SI32();
		l_v.length = l_l;
	}
	return l_v;
}

// clip

clip::clip(const info &_info, player &_player, uint _movie_ID) :
	player::object(_info, _player), m_movie_ID(_movie_ID)
{}
clip::~clip() {
}

// clip::info

clip::info::info(movie::info &_movie, swfstream &_s) : player::object::info(ot::clip) {
	if(_s.good()) {
		m_frame_count = _s.UI16();
		while(true) {
			record l_record = RECORD(_s);
			if(l_record.type == tag::End) break;
			switch(l_record.type) {
				case tag::DefineShape :
				case tag::DefineShape2 :
				case tag::DefineShape3 :
				case tag::DefineShape4 : {
					_movie.define_shape(_s, l_record.type);
				} break;
				case tag::DefineSprite : {
					_movie.define_clip(_s);
				} break;
				default : {
					_s.seek(l_record.length);
				}
			}
		}
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
