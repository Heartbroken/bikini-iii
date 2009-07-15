/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// random
template<uint _ID>
uint random_<_ID>::seed = 0;
template<uint _ID>
inline void random_<_ID>::set(uint _seed) {
	seed = _seed;
}
template<uint _ID>
inline uint random_<_ID>::get() {
	seed = seed * 1103515245 + 12345;
	return uint(seed / 65536) % max;
}
template<uint _ID>
inline uint random_<_ID>::get(uint _max) {
	return get() % (_max + 1);
}
template<uint _ID>
inline sint random_<_ID>::get(sint _min, sint _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(uint(_max - _min));
}
template<uint _ID>
inline real random_<_ID>::get(real _max) {
	return bk::max(real(0), real(get()) * _max / real(max));
}
template<uint _ID>
inline real random_<_ID>::get(real _min, real _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(_max - _min);
}
