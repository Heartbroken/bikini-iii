/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct clip : player::object {
	struct frame {
		struct add_object { uint ID, depth; };
		struct select_object { uint depth; };
		struct move_object { r3x3 position; };
		struct tinge_object { cxform cxf; };
		struct morph_object { real ratio; };
		struct name_object { wstring name; };
		struct clipoff_object { uint clipdepth; };
		struct remove_object { uint depth; };
		struct do_action {};
		typedef make_typelist_<
			add_object,
			select_object,
			move_object,
			tinge_object,
			morph_object,
			name_object,
			clipoff_object,
			remove_object,
			do_action
		>::type commands;
		typedef variant_<commands> command;
		void add_command(swfstream &_s, tag::type _type);
		inline uint command_count() const { return m_commands.size(); }
		inline const command& get_command(uint _i) const { return m_commands[_i]; }
	private:
		std::vector<command> m_commands;
	};
	struct info : player::object::info {
		typedef clip object;
		typedef uint a0;
		info(movie::info &_movie, swfstream &_s);
		inline uint frame_count() const { return m_timeline.size(); }
		inline const frame& get_frame(uint _i) const { return m_timeline[_i]; }
	private:
		std::vector<frame> m_timeline;
	};
	inline const r3x3& position() const { return m_position; }
	inline void set_position(const r3x3 &_p) { m_position = _p; }
	clip(const info &_info, player &_player, uint _movie_ID);
	~clip();
	bool update(real _dt);
	bool render() const;
private:
	uint m_movie_ID;
	real m_time;
	uint m_curr_frame;
	r3x3 m_position;
	std::vector<uint> m_objects;
};
