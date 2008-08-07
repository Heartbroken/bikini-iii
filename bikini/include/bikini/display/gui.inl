/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// gui

// gui::rect

inline gui::rect::rect()
{}
inline gui::rect::rect(sint _l, sint _t, uint _w, uint _h) :
	m_lt(_l, _t), m_rb(_l + _w, _t + _h)
{}
inline sint gui::rect::left() const {
	return m_lt.cell<0>();
}
inline sint gui::rect::top() const {
	return m_lt.cell<1>();
}
inline sint gui::rect::right() const {
	return m_rb.cell<0>();
}
inline sint gui::rect::bottom() const {
	return m_rb.cell<1>();
}
inline uint gui::rect::width() const {
	return m_rb.cell<0>() - m_lt.cell<0>();
}
inline uint gui::rect::height() const {
	return m_rb.cell<1>() - m_lt.cell<1>();
}
inline const gui::point gui::rect::lefttop() const {
	return m_lt;
}
inline const gui::point gui::rect::rightbottom() const {
	return m_rb;
}
inline const gui::point gui::rect::size() const {
	return m_rb - m_lt;
}
inline gui::rect& gui::rect::operator = (const rect &_r) {
	m_lt = _r.lefttop(); m_rb = _r.rightbottom(); return *this;
}
inline bool gui::rect::operator == (const rect &_r) const {
	return m_lt == _r.lefttop() && m_rb == _r.rightbottom();
}

// gui::panel

inline gui& gui::panel::get_gui() const {
	return static_cast<gui&>(get_manager());
}
inline const gui::rect& gui::panel::get_rect() const {
	return m_rect;
}
inline void gui::panel::set_rect(const rect &_r) {
	m_rect = _r;
}
inline const color& gui::panel::get_color() const {
	return m_color;
}
inline void gui::panel::set_color(const color &_c) {
	m_color = _c;
}
inline uint gui::panel::parent_ID() const {
	return dependency(m_parent_dependency);
}
inline bool gui::panel::has_parent() const {
	return get_gui().exists(parent_ID());
}
inline gui::panel& gui::panel::get_parent() const {
	assert(has_parent());
	return get_gui().get<gui::panel>(parent_ID());
}
inline void gui::panel::add_kid(uint _ID) {
	m_kids.push_back(_ID);
}
inline uint gui::panel::kid_count() const {
	return m_kids.size();
}
inline uint gui::panel::kid_ID(uint _i) const {
	assert(_i < m_kids.size());
	return m_kids[_i];
}

// gui::panel::info
