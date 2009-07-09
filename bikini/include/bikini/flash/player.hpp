/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	flash player
/**	[TODO]
 */
struct player : manager {
	struct object : manager::object {
		struct info : manager::object::info {
			typedef player manager;
			info(uint _type);
		};
		object(const info &_info, player &_player);
		inline player& get_player() const;
	};
	player();
	~player();
	inline renderer& get_renderer() const;
	inline loader& get_loader() const;
	bool create(renderer &_renderer);
	bool create(renderer &_renderer, loader &_loader);
	template<typename _Renderer> inline bool create(_Renderer &_renderer);
	template<typename _Renderer, typename _Loader> inline bool create(_Renderer &_renderer, _Loader &_loader);
	bool update(real _dt);
	void destroy();
	uint play(const wchar* _path, uint _level = bad_ID);
	uint play(const achar* _path, uint _level = bad_ID);
	bool pause(uint _level = bad_ID);
	bool stop(uint _level = bad_ID);
	bool show(uint _level = bad_ID);
	bool hide(uint _level = bad_ID);
	bool render(uint _level = bad_ID) const;
private:
	renderer *m_renderer_p; bool m_delete_renderer;
	loader *m_loader_p; bool m_delete_loader;
	bk::loader m_def_loader;
	array_<uint> m_levels;
	array_<object::info*> m_movies;
	array_<wstring> m_movie_names;
	object::info& m_load_movie(const wchar* _path);
};

#include "player.inl"