/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// player

player::player() :
	m_renderer_p(0), m_delete_renderer(false),
	m_loader_p(0), m_delete_loader(false)
{}
player::~player() {
	while(!m_levels.empty()) {
		if(exists(m_levels.back())) kill(m_levels.back());
		m_levels.pop_back();
	}
	delete m_loader_p;
}
bool player::create(renderer &_renderer) {
	m_renderer_p = &_renderer;
	m_delete_loader = true;
	m_loader_p = new _player_loader_proxy_<bk::loader>(m_def_loader);
	return true;
}
bool player::create(renderer &_renderer, loader &_loader) {
	m_renderer_p = &_renderer;
	m_loader_p = &_loader;
	return true;
}
bool player::update(real _dt) {
	return true;
}
void player::destroy() {
	if(m_delete_renderer) delete m_renderer_p;
	m_renderer_p = 0;
	if(m_delete_loader) delete m_loader_p;
	m_loader_p = 0;
}
uint player::play(const wchar* _path, uint _level) {
	assert(m_renderer_p != 0 && m_loader_p != 0);
	if(m_renderer_p == 0 || m_loader_p == 0) return bad_ID;
	po::movie::info &l_movie = static_cast<po::movie::info&>(m_load_movie(_path));
	uint l_level = _level;
	if(l_level > m_levels.size()) {
		if(l_level == bad_ID) l_level = m_levels.size();
		m_levels.resize(l_level + 1, bad_ID);
	} else if(m_levels[l_level] != bad_ID) {
		if(exists(m_levels[l_level])) kill(m_levels[l_level]);
		m_levels[l_level] = bad_ID;
	}
	m_levels[l_level] = spawn(l_movie);
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
player::object::info& player::m_load_movie(const wchar* _path) {
	std::vector<wstring>::iterator l_it = std::find(m_movie_names.begin(), m_movie_names.end(), _path);
	if(l_it != m_movie_names.end()) return *m_movies[l_it - m_movie_names.begin()];
	m_movie_names.push_back(_path);
	po::movie::info &l_movie = * new po::movie::info(swfstream(get_loader(), _path));
	m_movies.push_back(&l_movie);
	return l_movie;
}

// player::object

player::object::object(const info &_info, player &_player) :
	manager::object(_info, _player)
{}

// player::object::info

player::object::info::info(uint _type) :
	bk::manager::object::info(_type)
{}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
