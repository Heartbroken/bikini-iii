/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// random number generator
/**	Template parametre _ID is used to create a set
	of independent random number generators
 */
template<uint _ID> struct random_ {
	static const uint ID = _ID;
	static const uint max = 32768;
	static uint seed;
	static inline uint get(uint _max = max);
	static inline real get(real _max);
	static inline real get(real _min, real _max);
};
typedef random_<0> random;

#include "random.inl"
