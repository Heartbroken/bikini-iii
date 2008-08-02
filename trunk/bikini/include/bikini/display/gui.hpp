/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _Window> struct gui_ {
	typedef _Window window;
	gui_(window &_window);
private:
	window &m_window;
};
typedef gui_<window> gui;

#include "gui.inl"