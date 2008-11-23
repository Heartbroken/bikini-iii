/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	flash player
/**	[TODO]
 */
struct player : manager {
	struct loader {
		virtual ~loader() {}
		virtual uint open(const wchar* _path) = 0;
		virtual bool good(uint _ID) const = 0;
		virtual uint seek(uint _ID, sint _offset = 0, uint _from = 1) = 0;
		virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
		virtual void close(uint _ID) = 0;
	};
	struct renderer {
		virtual ~renderer() {}
	};
	struct object : manager::object {
		struct info : manager::object::info {
			typedef player manager;
			info(uint _type);
		};
		object(const info &_info, player &_player);
		inline player& get_player() const;
		uint open_stream(const wchar* _path) const;
	};
	player();
	~player();
	template<typename _Loader> inline void set_loader(_Loader &_loader);
	inline loader& get_loader() const;
	bool update(real _dt);
	uint play(const wchar* _path, uint _level = bad_ID);
	uint play(const achar* _path, uint _level = bad_ID);
	bool pause(uint _level = bad_ID);
	bool stop(uint _level = bad_ID);
	bool show(uint _level = bad_ID);
	bool hide(uint _level = bad_ID);
	bool render(uint _level = bad_ID);
private:
	loader *m_loader_p;
	bk::loader m_def_loader;
	std::vector<uint> m_levels;
};

#include "player.inl"