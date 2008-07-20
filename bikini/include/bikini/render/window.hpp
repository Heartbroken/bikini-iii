/*//-----------------------------------------------------------------------------------------------

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*///-----------------------------------------------------------------------------------------------

#pragma once

struct window {
	window();
	virtual ~window();
	bool create(uint _width, uint _height, HICON _icon = 0);
	bool create(HWND _handle);
	void destroy();
	HWND handle();
	void show(bool _yes = true);
	void hide();
	void set_caption(const wstr &_s);
	void set_caption(const astr &_s);
	void set_size(uint _width, uint _height);
	bool update(real _dt);

protected:

private:
	HWND m_handle;
	WNDPROC m_oldproc;
	static LRESULT CALLBACK window_proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam);
	LRESULT m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam);
};