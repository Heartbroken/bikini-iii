/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// create random GUID
inline GUID random_GUID() {
	GUID l_guid;
	l_guid.Data1 = (unsigned long)((random::get() << 16) | random::get());
	l_guid.Data2 = (unsigned short)random::get();
	l_guid.Data3 = (unsigned short)(0x4000 | (0x0fff & random::get()));
	for(uint i = 0; i < 8; ++i) l_guid.Data4[i] = (unsigned char)random::get();
	return l_guid;
}
