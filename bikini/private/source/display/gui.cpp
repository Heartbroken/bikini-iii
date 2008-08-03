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
template<uint _N> struct constants_ : matrix_<_N, 4, real> {};
bool gui::render(window &_window) const {
	bool l_save_active = _window.active();
	if(_window.active() || _window.begin()) {
		_window.clear(cf::all, yellow);
		std::vector<uint> l_order;
		l_order.push_back(m_screen_ID);
		for(uint i = 0; i < l_order.size(); ++i) {
			uint l_panel_ID = l_order[i];
			if(exists(l_panel_ID)) {
				panel &l_panel = get<panel>(l_panel_ID);
				if(!l_panel.render(_window) && l_panel.get_color().a() > 0) {
					const rect &l_r = l_panel.get_rect(); const color &l_c = l_panel.get_color();
					_window.draw_rect(l_r.left(), l_r.top(), l_r.right(), l_r.bottom(), l_c);
				}
				for(uint i = 0, s = l_panel.kid_count(); i < s; ++i) {
					l_order.push_back(l_panel.kid_ID(i));
				}
			}
		}
		if(!l_save_active) _window.end();
	}
	constants_<16> l_constants;
	l_constants.row<0>() = r1x4_0;
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
{
	set_color(0);
}


} /* namespace gp -------------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
