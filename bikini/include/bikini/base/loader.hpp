/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct loader {
	~loader();
	uint open(const char* _name);
	voin close(uint _ID);
	u8 get(uint _ID);
private:
	std::vector<std::ifstream*> m_streams;
	std::vector<astr> m_stream_names;
};