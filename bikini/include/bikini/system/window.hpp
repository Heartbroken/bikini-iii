/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct window {
	window(video &_video);
	virtual ~window();
#	if defined(XBOX)
	bool create();
#	elif defined(WIN32)
	bool create(uint _width, uint _height, HICON _icon = 0);
	bool create(HWND _handle);
	HWND handle();
	void show(bool _yes = true);
	void hide();
	void set_caption(const wstr &_s);
	void set_caption(const astr &_s);
	void set_size(uint _width, uint _height);
#	endif
	bool update(real _dt);
	bool active() const;
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0) const;
	bool begin() const;
	bool draw_line(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c = white, uint _width = 1);
	bool draw_rect(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c = white);
	bool end() const;
	bool present() const;
	void destroy();
protected:
private:
#	if defined(WIN32)
	HWND m_handle;
	WNDPROC m_oldproc;
	static LRESULT CALLBACK window_proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam);
	LRESULT m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam);
#	endif
	thread::section m_lock;
	video &m_video;
	vr::screen::info m_screen;
	uint m_screen_ID;
	vr::vbuffer::info m_vbuffer;
	uint m_vbuffer_ID;
	uint m_curr_vbuffer_ID;
	vr::vformat::info m_vformat;
	uint m_vformat_ID;
	vr::rstates::info m_rstates;
	uint m_rstates_ID;
	vr::vshader::info m_vshader;
	uint m_vshader_ID;
	vr::pshader::info m_pshader;
	uint m_pshader_ID;
};
