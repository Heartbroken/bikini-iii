/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct movie : player::object {
	struct info : player::object::info {
		typedef movie object;
		inline const sint2& frame_size() const { return m_frame_size; }
		inline real frame_rate() const { return m_frame_rate; }
		inline uint define_count() const;
		inline uint define_type(uint _i) const;
		template<typename _Type> inline const typename _Type::info& get_define(uint _i) const;
		info(swfstream &_s);
		~info();
		void define_clip(swfstream &_s);
		void define_shape(swfstream &_s, tag::type _type);
		void define_button(swfstream &_s, tag::type _type);
		void set_class(uint _i, const wstring &_class);
	private:
		sint2 m_frame_size; real m_frame_rate;
		array_<player::object::info*> m_defines;
		wstring_array m_classes;
	};
	inline const sint2& frame_size() const { return get_info<info>().frame_size(); }
	inline real frame_rate() const { return get_info<info>().frame_rate(); }
	inline uint define_count() const { return get_info<info>().define_count(); }
	inline uint define_type(uint _i) const { return get_info<info>().define_type(_i); }
	template<typename _Type> inline const typename _Type::info& get_define(uint _i) const { return get_info<info>().get_define<_Type>(_i); }
	inline as::machine& get_script() { return m_script; }
	//inline as::avm2& get_script() { return m_script; }
	movie(const info &_info, player &_player);
	~movie();
	bool update(real _dt);
	bool render() const;
private:
	uint m_clip_ID;
	as::machine m_script;
	//as::avm2 m_script;
};

#include "movie.inl"