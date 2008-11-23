/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _player_loader_helper_

template<typename _Loader> struct _player_loader_proxy_ : player::loader {
	_player_loader_proxy_(_Loader &_loader) : m_loader(_loader) {}
	uint open(const wchar* _path) { return m_loader.open(_path); }
	bool good(uint _ID) const { return m_loader.good(_ID); }
	uint seek(uint _ID, sint _offset = 0, uint _from = 0) { return m_loader.seek(_ID, _offset, _from); }
	uint read(uint _ID, handle _buffer, uint _length) { return m_loader.read(_ID, _buffer, _length); }
	void close(uint _ID) { m_loader.close(_ID); }
private:
	_Loader &m_loader;
};

// player

template<typename _L>
inline void player::set_loader(_L &_loader) {
	assert(m_loader_p == 0 && "ERROR: Flash player loader has already set");
	m_loader_p = new _player_loader_proxy_<_L>(_loader);
}
inline player::loader& player::get_loader() const {
	return *m_loader_p;
}

// player::object

inline player& player::object::get_player() const {
	return static_cast<player&>(get_manager());
}
