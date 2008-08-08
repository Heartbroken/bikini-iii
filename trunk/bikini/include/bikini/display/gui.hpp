/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct gui : manager {
	struct et { enum panel_type {
		screen
	};};
	typedef matrix_<1, 2, sint> point;
	struct rect {
		inline rect();
		inline rect(sint _l, sint _t, uint _w, uint _h);
		inline sint left() const;
		inline sint top() const;
		inline sint right() const;
		inline sint bottom() const;
		inline uint width() const;
		inline uint height() const;
		inline const point lefttop() const;
		inline const point rightbottom() const;
		inline const point size() const;
		inline rect& operator = (const rect &_r);
		inline bool operator == (const rect &_r) const;
	private:
		point m_lt, m_rb;
	};
	struct element : manager::object {
		struct info : manager::object::info {
			typedef element object;
			typedef gui manager;
			typedef sint a0;
			typedef sint a1;
			typedef uint a2;
			typedef uint a3;
			typedef uint a4;
			info(uint _type);
		};
		element(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID = bad_ID);
		inline gui& get_gui() const;
		inline const rect& get_rect() const;
		inline void set_rect(const rect &_r);
		inline const color& get_color() const;
		inline void set_color(const color &_c);
		inline uint parent_ID() const;
		inline bool has_parent() const;
		inline element& get_parent() const;
		inline void add_kid(uint _ID);
		inline uint kid_count() const;
		inline uint kid_ID(uint _i) const;
		virtual bool render(const window &_window) const;
	private:
		rect m_rect; color m_color;
		uint m_parent_dependency;
		std::vector<uint> m_kids;
	};
	inline uint screen_ID() const;
	gui();
	~gui();
	bool create();
	bool render(window &_window) const;
	void destroy();
private:
	uint m_screen_ID;
};

namespace ge { /*--------------------------------------------------------------------------------*/

struct screen : gui::element {
	struct info : gui::element::info {
		typedef screen object;
		info();
	};
	screen(const info &_info, gui &_gui);
};

} /* namespace ge -------------------------------------------------------------------------------*/

#include "gui.inl"