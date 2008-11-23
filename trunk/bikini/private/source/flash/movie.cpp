/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// movie

movie::movie(const info &_info, player &_player, const wchar* _path) :
	player::object(_info, _player)
{
	player &l_player = get_player();
	uint l_swfstream_ID = open_stream(_path);
	if(l_player.exists(l_swfstream_ID)) {
		swfstream &l_stream = l_player.get<swfstream>(l_swfstream_ID);
		if(l_stream.good()) {
			m_frame_size = l_stream.RECT().size();
			m_frame_rate = l_stream.FIXED8();
			static clip::info sl_clip;
			m_mainclip_ID = l_player.spawn(sl_clip, ID(), l_stream.ID());
		}
		l_player.kill(l_swfstream_ID);
	}
}
movie::~movie() {
	while(!m_defines.empty()) {
		if(get_player().exists(m_defines.back())) get_player().kill(m_defines.back());
		m_defines.pop_back();
	}
}
void movie::define_shape(uint _swfstream_ID, tag::code _type) {
	player &l_player = get_player();
	if(l_player.exists(_swfstream_ID)) {
		swfstream &l_stream = l_player.get<swfstream>(_swfstream_ID);
		if(l_stream.good()) {
			uint l_define_ID = l_stream.UI16();
			static shape::info sl_shape;
			uint l_shape_ID = l_player.spawn(sl_shape, _swfstream_ID, _type);
			if(l_define_ID >= m_defines.size()) m_defines.resize(l_define_ID + 1, bad_ID);
			m_defines[l_define_ID] = l_shape_ID;
		}
	}
}
void movie::define_clip(uint _swfstream_ID) {
	player &l_player = get_player();
	if(l_player.exists(_swfstream_ID)) {
		swfstream &l_stream = l_player.get<swfstream>(_swfstream_ID);
		if(l_stream.good()) {
			uint l_define_ID = l_stream.UI16();
			static clip::info sl_clip;
			uint l_clip_ID = l_player.spawn(sl_clip, ID(), _swfstream_ID);
			if(l_define_ID >= m_defines.size()) m_defines.resize(l_define_ID + 1, bad_ID);
			m_defines[l_define_ID] = l_clip_ID;
		}
	}
}


// movie::info

movie::info::info() : player::object::info(ot::movie) {
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
