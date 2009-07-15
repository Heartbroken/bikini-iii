/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// random number generator
/**	Template parametre _Owner is used to create a set
	of independent random number generators
 */
template<typename _Owner> struct random_ {
	/// Maximum random value
	static const uint max = 32767;
	/// Random numbers sequence seed
	static uint seed;
	/// Returns integer numbers in range [0..max]
	static inline uint get();
	/// Returns integer numbers in range [0.._max]. The result can't be greater than max
	static inline uint get(uint _max);
	/// Returns integer numbers in range [_min.._max]. The result can't be greater than max + _min
	static inline sint get(sint _min, sint _max);
	/// Returns integer numbers in range [0.._max]. If _max is negative the result is 0
	static inline real get(real _max);
	/// Returns integer numbers in range [_min.._max].
	static inline real get(real _min, real _max);
};
typedef random_<notype> random;

#include "random.inl"
