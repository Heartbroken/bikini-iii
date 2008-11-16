/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// player

uint player::play(const wchar* _movie_path, uint _layer) {
	uint l_layer = _layer;
	if(l_layer > m_layers.size()) {
		if(l_layer == bad_ID) l_layer = m_layers.size();
		m_layers.resize(l_layer + 1, bad_ID);
	} else if(m_layers[l_layer] != bad_ID) {
		// remove existing movie
		m_layers[l_layer] = bad_ID;
	}
	return l_layer;
}
bool player::pause(uint _layer, bool _yes) {
	return true;
}
bool player::stop(uint _layer) {
	return true;
}
bool player::show(uint _layer) {
	return true;
}
bool player::hide(uint _layer) {
	return true;
}
bool player::update(real _dt) {
	return true;
}
bool player::render(uint _layer) {
	return true;
}

// player::object

// player::object::info

player::object::info::info(uint _type) :
	bk::manager::object::info(_type)
{}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
