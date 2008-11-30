/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// record

struct record {
	tag::type type; uint length;
};
static record RECORD(swfstream &_s) {
	record l_v;
	uint l_c = _s.UI16();
	l_v.type = (tag::type)((l_c & 0xffc0) >> 6);
	l_v.length = l_c & 0x3f;
	if(l_v.length == 0x3f) {
		sint l_l = _s.SI32();
		l_v.length = l_l;
	}
	return l_v;
}

// clip

clip::clip(const info &_info, player &_player, uint _movie_ID) :
	player::object(_info, _player), m_movie_ID(_movie_ID), m_time(0), m_curr_frame(bad_ID), m_position(r3x3_1)
{}
clip::~clip() {
	while(!m_objects.empty()) {
		if(get_player().exists(m_objects.back())) get_player().kill(m_objects.back());
		m_objects.pop_back();
	}
}
bool clip::update(real _dt) {
	m_time += _dt;
	player &l_player = get_player();
	movie &l_movie = l_player.get<movie>(m_movie_ID);
	uint l_curr_frame = uint(m_time * l_movie.frame_rate()) % get_info<info>().frame_count();
	if(m_curr_frame != l_curr_frame) {
		const frame &l_frame = get_info<info>().get_frame(l_curr_frame);
		uint l_object_ID = bad_ID;
		for(uint i = 0, s = l_frame.command_count(); i < s; ++i) {
			const frame::command &l_command = l_frame.get_command(i);
			switch(l_command.type()) {
				case frame::commands::type_<frame::add_object>::index : {
					frame::add_object l_c = l_command.get<frame::add_object>();
					if(l_c.depth >= m_objects.size()) m_objects.resize(l_c.depth + 1, bad_ID);
					if(l_player.exists(m_objects[l_c.depth])) l_player.kill(m_objects[l_c.depth]);
					switch(l_movie.define_type(l_c.ID)) {
						case ot::shape : m_objects[l_c.depth] = l_player.spawn(l_movie.get_define<shape>(l_c.ID)); break;
						case ot::clip : m_objects[l_c.depth] = l_player.spawn(l_movie.get_define<clip>(l_c.ID), m_movie_ID); break;
					}
					l_object_ID = m_objects[l_c.depth];
				} break;
				case frame::commands::type_<frame::select_object>::index : {
					frame::select_object l_c = l_command.get<frame::select_object>();
					assert(l_c.depth < m_objects.size());
					l_object_ID = m_objects[l_c.depth];
				} break;
				case frame::commands::type_<frame::move_object>::index : {
					frame::move_object l_c = l_command.get<frame::move_object>();
					if(l_player.exists(l_object_ID)) {
						switch(l_player.get(l_object_ID).type()) {
							case ot::shape : l_player.get<shape>(l_object_ID).set_position(position() * l_c.position); break;
							case ot::clip : l_player.get<clip>(l_object_ID).set_position(position() * l_c.position); break;
						}
					}
				} break;
				case frame::commands::type_<frame::tinge_object>::index : {
					frame::tinge_object l_c = l_command.get<frame::tinge_object>();
				} break;
				case frame::commands::type_<frame::morph_object>::index : {
					frame::morph_object l_c = l_command.get<frame::morph_object>();
				} break;
				case frame::commands::type_<frame::name_object>::index : {
					frame::name_object l_c = l_command.get<frame::name_object>();
				} break;
				case frame::commands::type_<frame::clipoff_object>::index : {
					frame::clipoff_object l_c = l_command.get<frame::clipoff_object>();
				} break;
				case frame::commands::type_<frame::remove_object>::index : {
					frame::remove_object l_c = l_command.get<frame::remove_object>();
					assert(l_c.depth < m_objects.size());
					if(l_player.exists(m_objects[l_c.depth])) l_player.kill(m_objects[l_c.depth]);
					m_objects[l_c.depth] = bad_ID;
				} break;
			}
		}
		m_curr_frame = l_curr_frame;
	}
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		uint l_object_ID = m_objects[i];
		if(l_player.exists(l_object_ID) && l_player.get(l_object_ID).type() == ot::clip) {
			l_player.get<clip>(l_object_ID).update(_dt);
		}
	}
	return true;
}
bool clip::render() const {
	player &l_player = get_player();
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		uint l_object_ID = m_objects[i];
		if(l_player.exists(l_object_ID)) {
			switch(l_player.get(l_object_ID).type()) {
				case ot::shape : l_player.get<shape>(l_object_ID).render(); break;
				case ot::clip : l_player.get<clip>(l_object_ID).render(); break;
			}
		}
	}
	return true;
}

// clip::info

clip::info::info(movie::info &_movie, swfstream &_s) : player::object::info(ot::clip) {
	uint l_frame_count = _s.UI16();
	m_timeline.resize(l_frame_count);
	uint l_curr_frame = 0;
	while(true) {
		record l_record = RECORD(_s);
		if(l_record.type == tag::End) break;
		uint l_position = _s.seek();
		assert(l_curr_frame < m_timeline.size());
		switch(l_record.type) {
			case tag::DefineShape :
			case tag::DefineShape2 :
			case tag::DefineShape3 :
			case tag::DefineShape4 : {
				_movie.define_shape(_s, l_record.type);
			} break;
			case tag::DefineSprite : {
				_movie.define_clip(_s);
			} break;
			case tag::PlaceObject :
			case tag::PlaceObject2 :
			case tag::PlaceObject3 :
			case tag::RemoveObject :
			case tag::RemoveObject2 :
			//case tag::DoAction :
			//case tag::StartSound :
			//case tag::StartSound2 :
			{
				m_timeline[l_curr_frame].add_command(_s, l_record.type);
			} break;
			case tag::ShowFrame : {
				++l_curr_frame;
			} break;
			default : {
				_s.seek(l_record.length);
			}
		}
		//_s.seek(l_position + l_record.length, 0);
		uint l_position2 = _s.seek();
		assert(l_position2 == l_position + l_record.length);
	}
}

// clip::frame

void clip::frame::add_command(swfstream &_s, tag::type _type) {
	enum place_flags {
		move			= 1<<0,
		has_character	= 1<<1,
		has_matrix		= 1<<2,
		has_cxform		= 1<<3,
		has_ratio		= 1<<4,
		has_name		= 1<<5,
		has_clipdepth	= 1<<6,
		has_clipactions	= 1<<7,
	};
	switch(_type) {
		case tag::PlaceObject : {
			assert(0 && "PlaceObject unsupported");
		} break;
		case tag::PlaceObject2 : {
			uint l_flags = _s.UB(8);
			uint l_depth = _s.UI16();
			if(l_flags & has_character) {
				add_object l_c; l_c.ID = _s.UI16(); l_c.depth = l_depth;
				m_commands.push_back(l_c);
			} else {
				select_object l_c; l_c.depth = l_depth;
				m_commands.push_back(l_c);
			}
			if(l_flags & has_matrix) {
				move_object l_c; l_c.position = _s.MATRIX();
				m_commands.push_back(l_c);
			}
			if(l_flags & has_cxform) {
				tinge_object l_c; l_c.cxf = _s.CXFORM();
				m_commands.push_back(l_c);
			}
			if(l_flags & has_ratio) {
				morph_object l_c; l_c.ratio = real(_s.UI16()) / real(65535);
				m_commands.push_back(l_c);
			}
			if(l_flags & has_name) {
				name_object l_c; l_c.name = _s.STRING();
				m_commands.push_back(l_c);
			}
			if(l_flags & has_clipdepth) {
				clipoff_object l_c; l_c.clipdepth = _s.UI16();
				m_commands.push_back(l_c);
			}
			if(l_flags & has_clipactions) {
				assert(0 && "Clip actoins not implemented");
			}
		} break;
		case tag::PlaceObject3 : {
			assert(0 && "PlaceObject3 not implemented");
		} break;
		case tag::RemoveObject : {
			uint l_define_ID = _s.UI16();
			remove_object l_c; l_c.depth = _s.UI16();
			m_commands.push_back(l_c);
		} break;
		case tag::RemoveObject2 : {
			remove_object l_c; l_c.depth = _s.UI16();
			m_commands.push_back(l_c);
		} break;
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
