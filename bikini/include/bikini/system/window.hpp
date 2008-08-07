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
	struct screen { vr::screen::info info; uint ID; } m_screen;
	struct vbuffer { vr::vbuffer::info info; uint ID, def_ID, pos; } m_vbuffer;
	struct vformat { vr::vformat::info info; uint ID, def_ID; } m_vformat;
	struct rstates { vr::rstates::info info; uint ID, def_ID; } m_rstates;
	struct vshader { vr::vshader::info info; uint ID, def_ID; } m_vshader;
	struct pshader { vr::pshader::info info; uint ID, def_ID; } m_pshader;
};