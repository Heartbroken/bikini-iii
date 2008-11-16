/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct movie {
	struct loader {
		virtual ~loader() {}
		virtual uint open(const wchar* _path) = 0;
		virtual bool good(uint _ID) const = 0;
		virtual uint seek(uint _ID, sint _offset = 0, uint _from = 0) = 0;
		virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
		virtual void close(uint _ID) = 0;
	};
	struct swf {
		struct tag {
		};
		inline swf(movie &_movie, uint _file_ID) : m_movie(_movie), m_file_ID(_file_ID) {}
	private:
		movie &m_movie;
		uint m_file_ID;
	};
	movie();
	~movie();
	template<typename _Loader> inline void set_loader(_Loader &_loader);
	inline loader& get_loader() const;
	template<typename _Loader> inline bool load(const wchar* _path, _Loader &_loader);
	bool load(const wchar* _path);
private:
	loader *m_loader_p;
	bk::loader m_def_loader;
};

#include "movie.inl"