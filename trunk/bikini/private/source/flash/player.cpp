/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// player

player::player() : m_loader_p(0) {
}
player::~player() {
	while(!m_levels.empty()) {
		if(exists(m_levels.back())) kill(m_levels.back());
		m_levels.pop_back();
	}
	delete m_loader_p;
}
bool player::update(real _dt) {
	return true;
}
uint player::play(const wchar* _path, uint _level) {
	if(m_loader_p == 0) set_loader(m_def_loader);
	uint l_level = _level;
	if(l_level > m_levels.size()) {
		if(l_level == bad_ID) l_level = m_levels.size();
		m_levels.resize(l_level + 1, bad_ID);
	} else if(m_levels[l_level] != bad_ID) {
		if(exists(m_levels[l_level])) kill(m_levels[l_level]);
		m_levels[l_level] = bad_ID;
	}
	static po::movie::info sl_movie;
	m_levels[l_level] = spawn(sl_movie, _path);
	return l_level;
}
uint player::play(const achar* _path, uint _level) {
	uint l_length = strlen(_path);
	wchar* l_path  = (wchar*)_malloca(l_length);
	MultiByteToWideChar(CP_ACP, 0, _path, (int)l_length, l_path, (int)l_length);
	return play(l_path, _level);
}
bool player::pause(uint _level) {
	return true;
}
bool player::stop(uint _level) {
	return true;
}
bool player::show(uint _level) {
	return true;
}
bool player::hide(uint _level) {
	return true;
}
bool player::render(uint _level) {
	return true;
}

// player::object

player::object::object(const info &_info, player &_player) :
	manager::object(_info, _player)
{}
uint player::object::open_stream(const wchar* _path) const {
	static po::swfstream::info sl_swfstream;
	return get_player().spawn(sl_swfstream, _path);
}

// player::object::info

player::object::info::info(uint _type) :
	bk::manager::object::info(_type)
{}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
