/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct renderer {
	virtual ~renderer() {}
	virtual void draw_line(const real2 &_s, const real2 &_e, const color &_c, real _width) = 0;
};
