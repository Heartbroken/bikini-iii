/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct shape : player::object {
	struct edge { uint s, c, e; };
	struct line_style { color c; uint w; };
	struct path { uint style; std::vector<edge> edges; };
	struct info : player::object::info {
		typedef shape object;
		info(swfstream &_s, tag::type _type);
		inline uint point_count() const { return m_points.size(); }
		inline const real2& get_point(uint _i) const { return m_points[_i]; }
		inline uint line_style_count() const { return m_line_styles.size(); }
		inline const line_style& get_line_style(uint _i) const { return m_line_styles[_i]; }
		inline uint line_path_count() const { return m_line_paths.size(); }
		inline const path& get_line_path(uint _i) const { return m_line_paths[_i]; }
	private:
		rect m_rect, m_edge_rect;
		void m_read_fill_styles(swfstream &_s, tag::type _type);
		void m_read_line_styles(swfstream &_s, tag::type _type);
		void m_read_shape_records(swfstream &_s, tag::type _type);
		std::vector<real2> m_points;
		std::vector<line_style> m_line_styles;
		std::vector<path> m_line_paths;
	};
	inline const r3x3& position() const { return m_position; }
	inline void set_position(const r3x3 &_p) { m_position = _p; }
	shape(const info &_info, player &_player);
	~shape();
	bool render() const;
private:
	r3x3 m_position;
};
