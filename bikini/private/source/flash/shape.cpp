/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// triangulator

struct triangulator {
	typedef std::vector<real2> points;
	typedef std::vector<uint> poly;
	typedef std::vector<poly> polys;
	struct vertex { uint p, e0, e1; };
	typedef std::vector<vertex> vertices;
	typedef std::vector<uint> point_map;
	struct edge { uint v0, v1; };
	typedef std::vector<edge> edges;
	bool build(const points &_points, const polys &_polys) {
		vertices l_vertices; point_map l_point_map; 
		m_create_vertices(_points, l_vertices, l_point_map);
		return true;
	}
private:
	std::vector<uint> m_tris;
	void m_create_vertices(const points &_points, vertices &_vertices, point_map &_point_map) {
		for(uint i = 0, s = _points.size(); i < s; ++i) {
			vertex l_v; l_v.p = i; l_v.e0 = l_v.e1 = bad_ID;
			const real2 &l_p = _points[i];
			for(uint i = 0, s = _vertices.size(); i < s; ++i) {
				const real2 &l_p0 = _points[_vertices[i].p];
				if((l_p.x() < l_p0.x()) || (abs(l_p.x() - l_p0.x()) < eps && (l_p.y() < l_p0.y()))) {
					_vertices.insert(_vertices.begin() + i, l_v); l_v.p = bad_ID; break;
				}
			}
			if(l_v.p != bad_ID) _vertices.push_back(l_v);
		}
		_point_map.resize(_vertices.size());
		for(uint i = 0, s = _vertices.size(); i < s; ++i) {
			_point_map[i] = _vertices[i].p;
		}
	}
};

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
	static std::vector<real2> l_points; l_points.resize(0);
	for(uint i = 0, s = l_info.point_count(); i < s; ++i) {
		const real2 &l_p = l_info.get_point(i);
		l_points.push_back(real(0.05) * real3(l_p.x(), l_p.y(), 1) * m_position);
	}
	for(uint i = 0, s = l_info.line_path_count(); i < s; ++i) {
		const path &l_path = l_info.get_line_path(i);
		const line_style &l_line_style = l_info.get_line_style(l_path.style);
		if(l_line_style.w == 0) continue;
		uint l_line_start = 0;
		std::vector<std::vector<uint> > l_polys;
		for(uint i = 0, s = l_path.edges.size(); i < s; ++i) {
			const edge &l_edge = l_path.edges[i];
			if(l_polys.empty() || l_polys.back().back() != l_edge.s) {
				l_polys.push_back(std::vector<uint>());
				l_polys.back().push_back(l_edge.s);
			}
			if(l_edge.c != bad_ID) {
				struct _l { static void tesselate(const real2 &_s, const real2 &_c, const real2 &_e, std::vector<real2> &_points) {
					const real l_tolerance = real(0.1);
					real2 l_p0 = (_s + _e) * real(0.5), l_p = (l_p0 + _c) * real(0.5);
					if(length2(l_p - l_p0) <= l_tolerance) { _points.push_back(_e); return; }
					tesselate(_s, (_s + _c) * real(0.5), l_p, _points);
					tesselate(l_p, (_c + _e) * real(0.5), _e, _points);
				}};
				const real2 &l_s = l_points[l_edge.s];
				const real2 &l_c = l_points[l_edge.c];
				const real2 &l_e = l_points[l_edge.e];
				static std::vector<real2> l_edge_points; l_edge_points.resize(0);
				_l::tesselate(l_s, l_c, l_e, l_edge_points);
				for(uint i = 0, s = l_edge_points.size() - 1; i < s; ++i) {
					l_polys.back().push_back(l_points.size());
					l_points.push_back(l_edge_points[i]);
				}
			}
			l_polys.back().push_back(l_edge.e);
		}
		triangulator l_triangulator;
		l_triangulator.build(l_points, l_polys);
		for(uint i = 0, s = l_polys.size(); i < s; ++i) {
			const std::vector<uint> &l_poly = l_polys[i];
			for(uint i = 1, s = l_poly.size(); i < s; ++i) {
				l_renderer.draw_line(l_points[l_poly[i - 1]], l_points[l_poly[i]], l_line_style.c, l_line_style.w * real(0.05));
			}
		}
	}
	return true;
}

// shape::info

shape::info::info(swfstream &_s, tag::type _type) : player::object::info(ot::shape) {
	line_style l_line_style; l_line_style.c = 0; l_line_style.w = 0;
	m_line_styles.push_back(l_line_style);
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
				color l_color = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
				uint a = 0;
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
		switch(_type) {
			case tag::DefineShape :
			case tag::DefineShape2 :
			case tag::DefineShape3 : {
				color l_color = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
				line_style l_line_style; l_line_style.c = l_color; l_line_style.w = l_width;
				m_line_styles.push_back(l_line_style);
			} break;
			case tag::DefineShape4 : {
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
				color l_color = l_hasfillflag == 0 ? _s.RGBA() : 0;
				if(l_hasfillflag == 1) {
					//
				}
				line_style l_line_style; l_line_style.c = l_color; l_line_style.w = l_width;
				m_line_styles.push_back(l_line_style);
			} break;
		}
		_s.align();
	}
}
void shape::info::m_read_shape_records(swfstream &_s, tag::type _type) {
	enum {
		new_styles		= 1<<4,
		line_style		= 1<<3,
		fill_style1		= 1<<2,
		fill_style0		= 1<<1,
		move_to			= 1<<0,
	};
	m_read_fill_styles(_s, _type);
	m_read_line_styles(_s, _type);
	uint l_fill_bits = _s.UB(4);
	uint l_line_bits = _s.UB(4);
	//m_line_paths.push_back(path());
	real2 l_curr_point;
	while(true) {
		uint l_type = _s.UB(1);
		if(l_type == 0) {
			uint l_flags = _s.UB(5);
			if(l_flags == 0) break;
			if(l_flags & move_to) {
				uint l_move_bits = _s.UB(5);
				real l_move_x = _s.SB(l_move_bits);
				real l_move_y = _s.SB(l_move_bits);
				m_points.push_back(l_curr_point = real2(l_move_x, l_move_y));
				//m_paths.push_back(path());
			}
			if(l_flags & fill_style0) {
				uint l_fill0 = _s.UB(l_fill_bits);
			}
			if(l_flags & fill_style1) {
				uint l_fill1 = _s.UB(l_fill_bits);
			}
			if(l_flags & line_style) {
				uint l_style = _s.UB(l_line_bits);
				path l_path; l_path.style = l_style;
				m_line_paths.push_back(l_path);
			}
			if(l_flags & new_styles) {
				m_read_fill_styles(_s, _type);
				m_read_line_styles(_s, _type);
				l_fill_bits = _s.UB(4);
				l_line_bits = _s.UB(4);
			}
		} else {
			uint l_straight = _s.UB(1);
			uint l_delta_bits = _s.UB(4) + 2;
			edge l_edge;
			if(l_straight) {
				uint l_general_line = _s.UB(1);
				uint l_vert_line = (l_general_line == 0) ? _s.UB(1) : 0;
				real l_delta_x = (l_general_line == 1 || l_vert_line == 0) ? _s.SB(l_delta_bits) : 0;
				real l_delta_y = (l_general_line == 1 || l_vert_line == 1) ? _s.SB(l_delta_bits) : 0;
				m_points.push_back(l_curr_point += real2(l_delta_x, l_delta_y));
				l_edge.s = m_points.size() - 2; l_edge.c = bad_ID; l_edge.e = m_points.size() - 1;
			} else {
				real l_control_delta_x = _s.SB(l_delta_bits);
				real l_control_delta_y = _s.SB(l_delta_bits);
				real l_anchor_delta_x = _s.SB(l_delta_bits);
				real l_anchor_delta_y = _s.SB(l_delta_bits);
				m_points.push_back(l_curr_point += real2(l_control_delta_x, l_control_delta_y));
				m_points.push_back(l_curr_point += real2(l_anchor_delta_x, l_anchor_delta_y));
				l_edge.s = m_points.size() - 3; l_edge.c = m_points.size() - 2; l_edge.e = m_points.size() - 1;
			}
			if(!m_line_paths.back().edges.empty()) {
				const real2 &l_s0 = m_points[m_line_paths.back().edges.front().s];
				const real2 &l_e0 = m_points.back();
				if(length2(l_e0 - l_s0) < eps) {
					l_edge.e = m_line_paths.back().edges.front().s;
					m_points.pop_back();
				}
			}
			m_line_paths.back().edges.push_back(l_edge);
		}
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
