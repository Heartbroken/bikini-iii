/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// clip

clip::clip(const info &_info, player &_player, uint _movie_ID, uint _swfstream_ID) :
	player::object(_info, _player), m_movie_ID(_movie_ID), m_swfstream_ID(_swfstream_ID)
{
	player &l_player = get_player();
	if(l_player.exists(m_movie_ID) && l_player.exists(m_swfstream_ID)) {
		movie &l_movie = l_player.get<movie>(m_movie_ID);
		swfstream &l_stream = l_player.get<swfstream>(m_swfstream_ID);
		if(l_stream.good()) {
			m_frame_count = l_stream.UI16();
			while(true) {
				swfstream::record l_record = l_stream.RECORD();
				if(l_record.type == tag::End) break;
				switch(l_record.type) {
					case tag::DefineShape :
					case tag::DefineShape2 :
					case tag::DefineShape3 :
					case tag::DefineShape4 : {
						l_movie.define_shape(m_swfstream_ID, l_record.type);
					} break;
					case tag::DefineSprite : {
						l_movie.define_clip(m_swfstream_ID);
					} break;
					default : l_stream.seek(l_record.length);
				}
			}
		}
	}
}
clip::~clip() {
	while(!m_frames.empty()) {
		get_player().kill(m_frames.back());
		m_frames.pop_back();
	}
}

// clip::info

clip::info::info() : player::object::info(ot::clip) {
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
