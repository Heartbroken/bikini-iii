/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct shape : player::object {
	struct info : player::object::info {
		typedef shape object;
		info(swfstream &_s, tag::type _type);
		inline uint point_count() const { return m_points.size(); }
		inline const sint2& get_point(uint _i) const { return m_points[_i]; }
	private:
		rect m_rect, m_edge_rect;
		void m_read_fill_styles(swfstream &_s, tag::type _type);
		void m_read_line_styles(swfstream &_s, tag::type _type);
		void m_read_shape_records(swfstream &_s, tag::type _type);
		std::vector<sint2> m_points;
	};
	inline const r3x3& position() const { return m_position; }
	inline void set_position(const r3x3 &_p) { m_position = _p; }
	shape(const info &_info, player &_player);
	~shape();
	bool render() const;
private:
	r3x3 m_position;
};
