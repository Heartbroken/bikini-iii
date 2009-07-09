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
inline uint random_<_ID>::get(uint _max /*= max*/) {
	seed = seed * 1103515245 + 12345;
	return uint(seed / 65536) % _max;
}
template<uint _ID>
inline real random_<_ID>::get(real _max) {
	return real(get(max)) / real(max) * _max;
}
template<uint _ID>
inline real random_<_ID>::get(real _min, real _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(_max - _min);
}
