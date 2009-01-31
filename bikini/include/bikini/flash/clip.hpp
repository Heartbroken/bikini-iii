/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// _placed
struct _placed : player::object {
	inline _placed(const info &_info, player &_player) : player::object(_info, _player), m_position(r3x3_1), m_moved(true) {}
	inline const r3x3& position() const { return m_position; }
	inline void set_position(const r3x3 &_p) { m_moved = !(m_position == _p); m_position = _p; }
	inline bool moved() const { return m_moved; }
	inline void set_moved(bool _yes = true) { m_moved = _yes; }
private:
	r3x3 m_position; bool m_moved;
};

/// clip
struct clip : _placed {
	typedef std::vector<u8> program;
	struct frame {
		struct object {
			uint ID; r3x3 position; cxform tinge; real ratio; wstring name; uint clipdepth;
			inline object() : ID(bad_ID) {}
		};
		typedef std::vector<object> objects;
		typedef std::vector<program> programs;
		inline void set_objects(const objects &_objects) { m_objects = _objects; }
		inline uint object_count() const { return m_objects.size(); }
		inline const object& get_object(uint _i) const { return m_objects[_i]; }
		inline void add_program(const program &_program) { m_programs.push_back(_program); }
		inline uint program_count() const { return m_programs.size(); }
		inline const program& get_program(uint _i) const { return m_programs[_i]; }
		////
		//struct add_object { uint ID, depth; };
		//struct select_object { uint depth; };
		//struct move_object { r3x3 position; };
		//struct tinge_object { cxform cxf; };
		//struct morph_object { real ratio; };
		//struct name_object { wstring name; };
		//struct clipoff_object { uint clipdepth; };
		//struct remove_object { uint depth; };
		//struct do_action { std::vector<u8> program; };
		//typedef make_typelist_<
		//	add_object,
		//	select_object,
		//	move_object,
		//	tinge_object,
		//	morph_object,
		//	name_object,
		//	clipoff_object,
		//	remove_object,
		//	do_action
		//>::type commands;
		//typedef variant_<commands> command;
		//void add_command(swfstream &_s, tag::type _type);
		//inline uint command_count() const { return m_commands.size(); }
		//inline const command& get_command(uint _i) const { return m_commands[_i]; }
	private:
		objects m_objects;
		programs m_programs;
		////
		//std::vector<command> m_commands;
	};
	struct info : _placed::info {
		typedef clip object;
		typedef uint a0;
		info(movie::info &_movie, swfstream &_s);
		inline uint frame_count() const { return m_timeline.size(); }
		inline const frame& get_frame(uint _i) const { return m_timeline[_i]; }
	private:
		std::vector<frame> m_timeline;
		void m_edit_objects(swfstream &_s, tag::type _tag, frame::objects &_objects);
		void m_read_actions(swfstream &_s, program &_program);
	};
	clip(const info &_info, player &_player, uint _movie_ID);
	~clip();
	bool update(real _dt);
	bool render() const;
private:
	uint m_movie_ID;
	real m_time;
	uint m_curr_frame;
	std::vector<uint> m_objects;
};
