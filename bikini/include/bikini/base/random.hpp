/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// random number generator
/**	Each instance of random generates independent
	sequence of random numbers. The user can reproduce a sequence
	by saving and restoring of the seed member
 */
struct random {
	/// Maximum random value
	static const uint max = 32767;
	/// Random numbers sequence seed
	uint seed;
	/// Constructor
	inline random(uint _seed = 0);
	/// Returns integer numbers in range [0..max]
	inline uint get();
	/// Returns integer numbers in range [0.._max]. The result can't be greater than max
	inline uint get(uint _max);
	/// Returns integer numbers in range [_min.._max]. The result can't be greater than max + _min
	inline sint get(sint _min, sint _max);
	/// Returns integer numbers in range [0.._max]. If _max is negative the result is 0
	inline real get(real _max);
	/// Returns integer numbers in range [_min.._max].
	inline real get(real _min, real _max);
};
random random_0;

#include "random.inl"
