/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// random
template<typename _O>
uint random_<_O>::seed = 0;
template<typename _O>
inline uint random_<_O>::get() {
	seed = seed * 1103515245 + 12345;
	return uint(seed / 65536) & max;
}
template<typename _O>
inline uint random_<_O>::get(uint _max) {
	return get() % (_max + 1);
}
template<typename _O>
inline sint random_<_O>::get(sint _min, sint _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(uint(_max - _min));
}
template<typename _O>
inline real random_<_O>::get(real _max) {
	return bk::max(real(0), real(get()) * _max / real(max));
}
template<typename _O>
inline real random_<_O>::get(real _min, real _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(_max - _min);
}
