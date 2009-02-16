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

movie::movie(const info &_info, player &_player) :
	player::object(_info, _player), m_clip_ID(bad_ID)
{
	for(uint i = 0, s = _info.define_count(); i < s; ++i) if(_info.define_type(i) == po::ot::clip) {
		const clip::info &l_clip = _info.get_define<clip>(i);
		const byte_array &l_abc = l_clip.get_ABC();
		if(!l_abc.empty()) m_script.do_ABC(&l_abc[0], l_abc.size());
	}
	if(_info.define_count() > 0 && _info.define_type(0) == po::ot::clip) {
		m_clip_ID = _player.spawn(_info.get_define<clip>(0), ID());
	} else {
		std::cerr << "ERROR: Bad movie\n";
	}
}
movie::~movie() {
	if(get_player().exists(m_clip_ID)) get_player().kill(m_clip_ID);
}
bool movie::update(real _dt) {
	if(get_player().exists(m_clip_ID)) {
		get_player().get(m_clip_ID).update(_dt);
	}
	return true;
}
bool movie::render() const {
	if(get_player().exists(m_clip_ID)) {
		get_player().get<clip>(m_clip_ID).render();
	}
	return true;
}

// movie::info

movie::info::info(swfstream &_s) : player::object::info(ot::movie) {
	m_frame_size = _s.RECT().size();
	m_frame_rate = _s.FIXED8();
	m_defines.resize(1);
	m_defines[0] = new clip::info(*this, _s);
}
movie::info::~info() {
	while(!m_defines.empty()) {
		delete m_defines.back();
		m_defines.pop_back();
	}
}
void movie::info::define_clip(swfstream &_s) {
	if(_s.good()) {
		uint l_define_ID = _s.UI16();
		if(l_define_ID >= m_defines.size()) m_defines.resize(l_define_ID + 1, 0);
		m_defines[l_define_ID] = new clip::info(*this, _s);
	}
}
void movie::info::define_shape(swfstream &_s, tag::type _type) {
	if(_s.good()) {
		uint l_define_ID = _s.UI16();
		if(l_define_ID >= m_defines.size()) m_defines.resize(l_define_ID + 1, 0);
		m_defines[l_define_ID] = new shape::info(_s, _type);
	}
}
void movie::info::define_button(swfstream &_s, tag::type _type) {
	if(_s.good()) {
		uint l_define_ID = _s.UI16();
		if(l_define_ID >= m_defines.size()) m_defines.resize(l_define_ID + 1, 0);
		m_defines[l_define_ID] = new button::info(_s, _type);
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
