/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// gui
gui::gui() :
	m_screen_ID(bad_ID)
{}
gui::~gui() {
	assert(m_screen_ID == bad_ID);
}
bool gui::create() {
	static gp::screen::info sl_screen;
	m_screen_ID = spawn(sl_screen);
	return true;
}
bool gui::render(const window &_window) const {
	if(exists(m_screen_ID)) {
		gp::screen &l_screen = get<gp::screen>(m_screen_ID);
		l_screen.render(_window);
	}
	return true;
}
void gui::destroy() {
	if(exists(m_screen_ID)) {
		kill(m_screen_ID);
		m_screen_ID = bad_ID;
	}
}

// gui::panel

gui::panel::panel(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID) :
	manager::object(_info, _gui), m_rect(_x, _y, _w, _h), m_parent_dependency(add_dependency(_parent_ID))
{
	if(get_gui().exists(parent_ID())) {
		panel &l_parent = get_gui().get<panel>(parent_ID());
		l_parent.add_kid(ID());
	}
}
bool gui::panel::render(const window &_window) const {
	for(uint i = 0, s = kid_count(); i < s; ++i) {
		uint l_kid_ID = kid_ID(i);
		if(get_gui().exists(l_kid_ID)) {
			get_gui().get<panel>(l_kid_ID).render(_window);
		}
	}
	return true;
}

// gui::panel::info

gui::panel::info::info(uint _type) :
	manager::object::info(_type)
{}

namespace gp { /*--------------------------------------------------------------------------------*/

// screen::info

screen::info::info() :
	gui::panel::info(gui::pt::screen)
{}

// screen

screen::screen(const info &_info, gui &_gui) :
	gui::panel(_info, _gui, 0, 0, 0, 0)
{}


} /* namespace gp -------------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
