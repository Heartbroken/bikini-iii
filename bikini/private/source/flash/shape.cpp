/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// shape

shape::shape(const info &_info, player &_player) :
	player::object(_info, _player), m_position(r3x3_1)
{}
shape::~shape() {
}
bool shape::render() const {
	player &l_player = get_player();
	renderer &l_renderer = l_player.get_renderer();
	const info &l_info = get_info<info>();
	for(uint i = 1, s = l_info.point_count(); i < s; ++i) {
		const sint2 &l_p0 = l_info.get_point(i - 1), &l_p1 = l_info.get_point(i);
		real2 l_s = real(0.05) * real3(l_p0.x(), l_p0.y(), 1) * m_position;
		real2 l_e = real(0.05) * real3(l_p1.x(), l_p1.y(), 1) * m_position;
		l_renderer.draw_line(l_s, l_e, red, r_1);
	}
	return true;
}

// shape::info

shape::info::info(swfstream &_s, tag::type _type) : player::object::info(ot::shape) {
	m_rect = m_edge_rect = _s.RECT();
	if(_type == tag::DefineShape4) {
		m_edge_rect = _s.RECT();
		uint l_reserved = _s.UB(6);
		uint l_nonscalingstrokes = _s.UB(1);
		uint l_scalingstrokes = _s.UB(1);
	}
	m_read_shape_records(_s, _type);
}
void shape::info::m_read_fill_styles(swfstream &_s, tag::type _type) {
	uint l_count = _s.UI8();
	if(l_count == 0xff) l_count = _s.UI16();
	for(uint i = 0; i < l_count; ++i) {
		uint l_type = _s.UI8();
		switch(l_type) {
			case 0x00 : {
				color l_c = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
				uint a=0;
			} break;
		}
		_s.align();
	}
}
void shape::info::m_read_line_styles(swfstream &_s, tag::type _type) {
	uint l_count = _s.UI8();
	if(l_count == 0xff) l_count = _s.UI16();
	for(uint i = 0; i < l_count; ++i) {
		uint l_width = _s.UI16();
		uint l_startcapstyle = _s.UB(2);
		uint l_joinstyle = _s.UB(2);
		uint l_hasfillflag = _s.UB(1);
		uint l_nohscaleflag = _s.UB(1);
		uint l_novscaleflag = _s.UB(1);
		uint l_pixelhintingflag = _s.UB(1);
		uint l_reservedflag = _s.UB(5);
		uint l_noclose = _s.UB(1);
		uint l_endcapstyle = _s.UB(2);
		if(l_joinstyle == 2) {
			uint l_miterlimitfactor = _s.UI16();
		}
		if(l_hasfillflag == 0) {
			color l_color = _s.RGBA();
		}
		if(l_hasfillflag == 1) {
			//
		}
		_s.align();
	}
}
void shape::info::m_read_shape_records(swfstream &_s, tag::type _type) {
	enum {
		newstyles	= 1<<4,
		linestyle	= 1<<3,
		fillstyle1	= 1<<2,
		fillstyle0	= 1<<1,
		moveto		= 1<<0,
	};
	m_read_fill_styles(_s, _type);
	m_read_line_styles(_s, _type);
	uint l_numfillbits = _s.UB(4);
	uint l_numlinebits = _s.UB(4);
	sint2 l_curr_point;
	while(true) {
		uint l_type = _s.UB(1);
		if(l_type == 0) {
			uint l_flags = _s.UB(5);
			if(l_flags == 0) break;
			if(l_flags & moveto) {
				uint l_movebits = _s.UB(5);
				sint l_movex = _s.SB(l_movebits);
				sint l_movey = _s.SB(l_movebits);
				m_points.push_back(l_curr_point = sint2(l_movex, l_movey));
			}
			if(l_flags & fillstyle0) {
				uint l_fill0 = _s.UB(l_numfillbits);
			}
			if(l_flags & fillstyle1) {
				uint l_fill1 = _s.UB(l_numfillbits);
			}
			if(l_flags & linestyle) {
				uint l_line = _s.UB(l_numlinebits);
			}
			if(l_flags & newstyles) {
				m_read_fill_styles(_s, _type);
				m_read_line_styles(_s, _type);
				l_numfillbits = _s.UB(4);
				l_numlinebits = _s.UB(4);
			}
		} else {
			uint l_straight = _s.UB(1);
			uint l_numbits = _s.UB(4) + 2;
			if(l_straight) {
				uint l_generalline = _s.UB(1);
				uint l_vertline = (l_generalline == 0) ? _s.UB(1) : 0;
				sint l_deltax = (l_generalline == 1 || l_vertline == 0) ? _s.SB(l_numbits) : 0;
				sint l_deltay = (l_generalline == 1 || l_vertline == 1) ? _s.SB(l_numbits) : 0;
				m_points.push_back(l_curr_point += sint2(l_deltax, l_deltay));
			} else {
				sint l_cdeltax = _s.SB(l_numbits);
				sint l_cdeltay = _s.SB(l_numbits);
				sint l_adeltax = _s.SB(l_numbits);
				sint l_adeltay = _s.SB(l_numbits);
				m_points.push_back(l_curr_point += sint2(l_cdeltax, l_cdeltay));
				m_points.push_back(l_curr_point += sint2(l_adeltax, l_adeltay));
			}
		}
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
