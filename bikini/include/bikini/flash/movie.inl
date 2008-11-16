/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _movie_loader_proxy_

template<typename _Loader> struct _movie_loader_proxy_ : movie::loader {
	_movie_loader_proxy_(_Loader &_loader) : m_loader(_loader) {}
	uint open(const wchar* _path) { return m_loader.open(_path); }
	bool good(uint _ID) const { return m_loader.good(_ID); }
	uint seek(uint _ID, sint _offset = 0, uint _from = 0) { return m_loader.seek(_ID, _offset, _from); }
	uint read(uint _ID, handle _buffer, uint _length) { return m_loader.read(_ID, _buffer, _length); }
	void close(uint _ID) { m_loader.close(_ID); }
private:
	_Loader &m_loader;
};

// movie

template<typename _L>
inline void movie::set_loader(_L &_loader) {
	assert(m_loader_p == 0 && "ERROR: Flash movie loader has already set");
	m_loader_p = new _movie_loader_proxy_<_L>(_loader);
}
inline movie::loader& movie::get_loader() const {
	return *m_loader_p;
}
template<typename _L>
inline bool movie::load(const wchar* _path, _L &_loader) {
	set_loader(_loader);
	load(_path);
}
