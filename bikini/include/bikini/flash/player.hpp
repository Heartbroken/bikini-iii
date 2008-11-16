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
		virtual uint seek(uint _ID, sint _offset = 0, uint _from = 0) = 0;
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
	};
	template<typename _Loader> inline void set_loader(_Loader &_loader);
	inline loader& get_loader() const;
	uint play(const wchar* _movie_path, uint _layer = bad_ID);
	bool pause(uint _layer, bool _yes = true);
	bool stop(uint _layer);
	bool show(uint _layer);
	bool hide(uint _layer);
	bool update(real _dt);
	bool render(uint _layer = bad_ID);
private:
	loader *m_loader_p;
	bk::loader m_def_loader;
	std::vector<uint> m_layers;
};