/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

#if defined(XBOX)
#	include "window.vs.xbox.h"
#	include "window.ps.xbox.h"
#elif defined(WIN32)
#	include "window.vs.h"
#	include "window.ps.h"
#endif

window::window(video &_video) :
#	if defined(WIN32)
	m_handle(0), m_oldproc(0),
#	endif
	m_video(_video)
{
	m_vbuffer.info.descs.push_back(vr::vbuffer::desc(1024 * 100, 0, true));

	m_vformat.info.format.push_back(vr::vformat::element(0, 0, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0));
	m_vformat.info.format.push_back(vr::vformat::element(0, 12, D3DDECLTYPE_D3DCOLOR, 0, D3DDECLUSAGE_COLOR, 0));
	m_vformat.info.format.push_back(vr::vformat::end);

	m_rstates.info.states.push_back(vr::rstates::state(D3DRS_ZENABLE, FALSE));
	m_rstates.info.states.push_back(vr::rstates::state(D3DRS_ALPHABLENDENABLE, TRUE));
	m_rstates.info.states.push_back(vr::rstates::state(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	m_rstates.info.states.push_back(vr::rstates::state(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));

	m_vshader.info.function = window_vs;
	m_pshader.info.function = window_ps;

	m_scissor.x0 = m_scissor.y0 = m_scissor.x1 = m_scissor.y1 = bad_ID;
}
window::~window() {
}
#if defined(XBOX)
bool window::create() {
	if(!m_video.ready()) return false;
	m_screen.ID = m_video.spawn(m_screen.info);
	m_vbuffer.ID = m_vbuffer.def_ID = m_video.spawn(m_vbuffer.info);
	m_vformat.ID = m_vformat.def_ID = m_video.spawn(m_vformat.info);
	m_rstates.ID = m_rstates.def_ID = m_video.spawn(m_rstates.info);
	m_vshader.ID = m_vshader.def_ID = m_video.spawn(m_vshader.info);
	m_pshader.ID = m_pshader.def_ID = m_video.spawn(m_pshader.info);
	m_vbuffer.start = m_vbuffer.used = 0; m_vbuffer.data = 0;
	return true;
}
#elif defined(WIN32)
bool window::create(uint _width, uint _height, HICON _icon) {
	HINSTANCE l_instance = GetModuleHandleA(0);
    WNDCLASSW l_window_class = { CS_HREDRAW|CS_VREDRAW, window::window_proc, 0, 0, l_instance, _icon, LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL, L"bikini-iii window" };
    RegisterClassW(&l_window_class);
	m_handle = CreateWindowExW(WS_EX_TOOLWINDOW|WS_EX_APPWINDOW|WS_EX_RIGHT, L"bikini-iii window", 0, WS_BORDER|WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, (int)_width, (int)_height, m_video.get_focus_window(), 0, l_instance, 0);
	if(m_handle == 0) return false;
	set_size(_width, _height);
	SetWindowLong(m_handle, GWL_USERDATA, (LONG)(LONG_PTR)this);
	if(!m_video.ready()) return false;
	m_screen.ID = m_video.spawn(m_screen.info, m_handle, false, _width, _height);
	m_vbuffer.ID = m_vbuffer.def_ID = m_video.spawn(m_vbuffer.info);
	m_vformat.ID = m_vformat.def_ID = m_video.spawn(m_vformat.info);
	m_rstates.ID = m_rstates.def_ID = m_video.spawn(m_rstates.info);
	m_vshader.ID = m_vshader.def_ID = m_video.spawn(m_vshader.info);
	m_pshader.ID = m_pshader.def_ID = m_video.spawn(m_pshader.info);
	m_vbuffer.start = m_vbuffer.used = 0; m_vbuffer.data = 0;
	return true;
}
bool window::create(HWND _handle) {
	m_handle = _handle;
	m_oldproc = (WNDPROC)(LONG_PTR)GetWindowLong(m_handle, GWL_WNDPROC);
	SetWindowLong(m_handle, GWL_WNDPROC, (LONG)(LONG_PTR)window_proc);
	SetWindowLong(m_handle, GWL_USERDATA, (LONG)(LONG_PTR)this);
	if(!m_video.ready()) return false;
	RECT l_crect; GetClientRect(m_handle, &l_crect);
	m_screen.ID = m_video.spawn(m_screen.info, m_handle, false, l_crect.right, l_crect.bottom);
	m_vbuffer.ID = m_vbuffer.def_ID = m_video.spawn(m_vbuffer.info); m_vbuffer.data = 0;
	m_vformat.ID = m_vformat.def_ID = m_video.spawn(m_vformat.info);
	m_rstates.ID = m_rstates.def_ID = m_video.spawn(m_rstates.info);
	m_vshader.ID = m_vshader.def_ID = m_video.spawn(m_vshader.info);
	m_pshader.ID = m_pshader.def_ID = m_video.spawn(m_pshader.info);
	m_vbuffer.start = m_vbuffer.used = 0; m_vbuffer.data = 0;
	return true;
}
HWND window::get_handle() {
	return m_handle;
}
void window::show(bool _yes) {
	ShowWindow(m_handle, _yes ? SW_SHOW : SW_HIDE);
}
void window::hide() {
	ShowWindow(m_handle, SW_HIDE);
}
void window::set_caption(const wstr &_s) {
	SetWindowTextW(m_handle, _s.c_str());
}
void window::set_caption(const astr &_s) {
	SetWindowTextA(m_handle, _s.c_str());
}
void window::set_size(uint _width, uint _height) {
	RECT l_drect, l_wrect, l_crect;
	GetWindowRect(GetDesktopWindow(), &l_drect);
//std::cout << l_drect.right << " " << l_drect.bottom << "\n";
	GetWindowRect(m_handle, &l_wrect);
	GetClientRect(m_handle, &l_crect);
	uint l_width = _width + (l_wrect.right - l_wrect.left) - (l_crect.right - l_crect.left);
	uint l_height = _height + (l_wrect.bottom - l_wrect.top) - (l_crect.bottom - l_crect.top);
	POINT l_shift = { l_wrect.left, l_wrect.top }; ScreenToClient(m_handle, &l_shift);
	sint l_left = (l_drect.right - (sint)_width) / 2 + l_shift.x;
	sint l_top = (l_drect.bottom - (sint)_height) / 2 + l_shift.y;
	MoveWindow(m_handle, l_left, l_top, l_width, l_height, TRUE);
}
LRESULT CALLBACK window::window_proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam) {
	window &l_window = *reinterpret_cast<window*>((LONG_PTR)GetWindowLong(_handle, GWL_USERDATA));
	if(&l_window != 0) return l_window.m_proc(_message, _wparam, _lparam);
	return DefWindowProcW(_handle, _message, _wparam, _lparam);
}
LRESULT window::m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam) {
	switch(_message) {
		case WM_CLOSE : {
			DestroyWindow(m_handle);
		} break;
		case WM_DESTROY : {
			if(m_oldproc == 0) {
				PostQuitMessage(0);
				SetWindowLong(m_handle, GWL_USERDATA, (LONG)(LONG_PTR)0);
				m_handle = 0;
			} else {
				SetWindowLong(m_handle, GWL_WNDPROC, (LONG)(LONG_PTR)m_oldproc);
			}
		} break;
		case WM_SIZE : {
			if(m_video.exists(m_screen.ID)) {
				thread::locker l_locker(m_lock);
				vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
				if(!l_screen.fullscreen()) {
					l_screen.destroy();
					RECT l_crect; GetClientRect(m_handle, &l_crect);
					l_screen.set_size(l_crect.right, l_crect.bottom);
				} else {
					set_size(l_screen.width(), l_screen.height());
				}
			}
		} break;
		case WM_GETMINMAXINFO : {
			MINMAXINFO &l_minmax = *(MINMAXINFO*)(void*)_lparam;
			RECT l_drect, l_wrect, l_crect;
			GetWindowRect(GetDesktopWindow(), &l_drect);
			GetWindowRect(m_handle, &l_wrect);
			GetClientRect(m_handle, &l_crect);
			l_minmax.ptMaxTrackSize.x = l_drect.right + ((l_wrect.right - l_wrect.left) - l_crect.right);
			l_minmax.ptMaxTrackSize.y = l_drect.bottom + ((l_wrect.bottom - l_wrect.top) - l_crect.bottom);
		} break;
	}
	if(m_oldproc != 0) return m_oldproc(m_handle, _message, _wparam, _lparam);
	return DefWindowProcW(m_handle, _message, _wparam, _lparam);
}
#endif
uint window::width() const {
#	if defined(XBOX)
#	elif defined(WIN32)
	RECT l_crect; GetClientRect(m_handle, &l_crect);
	return l_crect.right;
#	endif
}
uint window::height() const {
#	if defined(XBOX)
#	elif defined(WIN32)
	RECT l_crect; GetClientRect(m_handle, &l_crect);
	return l_crect.bottom;
#	endif
}
bool window::update(real _dt) {
#	if defined(WIN32)
	if(m_oldproc == 0) {
		MSG l_message;
		while(PeekMessage(&l_message, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&l_message);
			DispatchMessage(&l_message);
			if(l_message.message == WM_QUIT) return false;
		}
	}
#	endif
	return true;
}
bool window::active() const {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.active();
}
bool window::clear(uint _flags, const color &_color, real _depth, uint _stencil) const {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.clear(_flags, _color, _depth, _stencil);
}
bool window::begin() const {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.begin();
}
bool window::set_scissor(uint _x0, uint _y0, uint _x1, uint _y1) {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	if(m_scissor.x0 == _x0 && m_scissor.y0 == _y0 && m_scissor.x1 == _x1 && m_scissor.y1 == _y1) return true;
	m_flush_tris();
	m_scissor.x0 = _x0; m_scissor.y0 = _y0; m_scissor.x1 = _x1; m_scissor.y1 = _y1;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.set_scissor(_x0, _y0, _x1, _y1);
}
bool window::remove_scissor() {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	if(m_scissor.x0 == bad_ID && m_scissor.y0 == bad_ID && m_scissor.x1 == bad_ID && m_scissor.y1 == bad_ID) return true;
	m_flush_tris();
	m_scissor.x0 = m_scissor.y0 = m_scissor.x1 = m_scissor.y1 = bad_ID;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.remove_scissor();
}
bool window::draw_line(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c, uint _width) {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	f32 l_length = (f32)sqrt((_x1 - _x0) * (_x1 - _x0) + (_y1 - _y0) * (_y1 - _y0));
	f1x4 l_p0(-.5f * _width, .5f * _width, 0, 1);
	f1x4 l_p1(-.5f * _width,-.5f * _width, 0, 1);
	f1x4 l_p2(l_length + .5f * _width,-.5f * _width, 0, 1);
	f1x4 l_p3(l_length + .5f * _width, .5f * _width, 0, 1);
	f32 l_angle = atan2(f32(_y1 - _y0), f32(_x1 - _x0));
	f32 l_s = (f32)sin(l_angle), l_c = (f32)cos(l_angle);
	f4x4 l_rotate  (f1x4( l_c, l_s, 0.f, 0.f),
					f1x4(-l_s, l_c, 0.f, 0.f),
					f1x4( 0.f, 0.f, 1.f, 0.f),
					f1x4( 0.f, 0.f, 0.f, 1.f));
	f32 l_x = (f32)_x0, l_y = (f32)_y0;
	f4x4 l_trans   (f1x4( 1.f, 0.f, 0.f, 0.f),
					f1x4( 0.f, 1.f, 0.f, 0.f),
					f1x4( 0.f, 0.f, 1.f, 0.f),
					f1x4( l_x, l_y, 0.f, 1.f));
	f32 l_w = 2.f / (f32)width(), l_h = 2.f / (f32)height();
	f4x4 l_project (f1x4( l_w, 0.f, 0.f, 0.f),
					f1x4( 0.f,-l_h, 0.f, 0.f),
					f1x4( 0.f, 0.f, 1.f, 0.f),
					f1x4(-1.f, 1.f, 0.f, 1.f));
	f4x4 l_xform = l_rotate * l_trans * l_project;
	l_p0 = l_p0 * l_xform; l_p1 = l_p1 * l_xform; l_p2 = l_p2 * l_xform; l_p3 = l_p3 * l_xform;
	vertex l_v[6];
	l_v[0].p = f1x3(l_p0[0][0], l_p0[0][1], 0); l_v[0].c = _c;
	l_v[1].p = f1x3(l_p1[0][0], l_p1[0][1], 0); l_v[1].c = _c;
	l_v[2].p = f1x3(l_p2[0][0], l_p2[0][1], 0); l_v[2].c = _c;
	l_v[3].p = f1x3(l_p2[0][0], l_p2[0][1], 0); l_v[3].c = _c;
	l_v[4].p = f1x3(l_p3[0][0], l_p3[0][1], 0); l_v[4].c = _c;
	l_v[5].p = f1x3(l_p0[0][0], l_p0[0][1], 0); l_v[5].c = _c;
	m_add_tris(sizeof(l_v) / sizeof(vertex) / 3, l_v);
	return true;
}
bool window::draw_rect(sint _x0, sint _y0, sint _x1, sint _y1, const color &_c) {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	f32 l_w = (f32)width(), l_h = (f32)height();
	f32 l_x0 = 2.f * ((f32)_x0 - .5f) / l_w - 1.f, l_y0 = -(2.f * ((f32)_y0 - .5f) / l_h - 1.f);
	f32 l_x1 = 2.f * ((f32)_x1 - .5f) / l_w - 1.f, l_y1 = -(2.f * ((f32)_y1 - .5f) / l_h - 1.f);
	vertex l_v[6];
	l_v[0].p = f1x3(l_x0, l_y0, 0); l_v[0].c = _c;
	l_v[1].p = f1x3(l_x0, l_y1, 0); l_v[1].c = _c;
	l_v[2].p = f1x3(l_x1, l_y1, 0); l_v[2].c = _c;
	l_v[3].p = f1x3(l_x1, l_y1, 0); l_v[3].c = _c;
	l_v[4].p = f1x3(l_x1, l_y0, 0); l_v[4].c = _c;
	l_v[5].p = f1x3(l_x0, l_y0, 0); l_v[5].c = _c;
	m_add_tris(sizeof(l_v) / sizeof(vertex) / 3, l_v);
	return true;
}
bool window::flush_drawings() {
	return m_flush_tris();
}
bool window::end() const {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.end();
}
bool window::present() const {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID);
	return l_screen.present();
}
void window::destroy() {
	if(m_video.exists(m_pshader.def_ID)) m_video.kill(m_pshader.def_ID);
	if(m_video.exists(m_vshader.def_ID)) m_video.kill(m_vshader.def_ID);
	if(m_video.exists(m_rstates.def_ID)) m_video.kill(m_rstates.def_ID);
	if(m_video.exists(m_vformat.def_ID)) m_video.kill(m_vformat.def_ID);
	if(m_video.exists(m_vbuffer.def_ID)) m_video.kill(m_vbuffer.def_ID);
	if(m_video.exists(m_screen.ID)) m_video.kill(m_screen.ID);
#	if defined(WIN32)
	DestroyWindow(m_handle);
#	endif
}
bool window::m_add_tris(uint _count, vertex *_v_p) {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	uint l_size = sizeof(vertex) * 3 * _count;
	if(m_vbuffer.start + m_vbuffer.used + l_size > m_vbuffer.info.descs[0].size/*1024 * 100*/) {
		m_flush_tris(); m_vbuffer.start = 0;
	}
	if(m_vbuffer.data == 0 && m_video.exists(m_vbuffer.ID)) {
		vr::vbuffer &l_vbuffer = m_video.get<vr::vbuffer>(m_vbuffer.ID);
		if(!l_vbuffer.valid()) return false;
		m_vbuffer.data = l_vbuffer.lock();
	}
	if(m_vbuffer.data != 0) {
		memcpy((u8*)m_vbuffer.data + m_vbuffer.start + m_vbuffer.used, _v_p, l_size);
		m_vbuffer.used += l_size;
	}
	return true;
}
bool window::m_flush_tris() {
	if(!m_video.ready() || !m_video.exists(m_screen.ID)) return false;
	if(m_vbuffer.data == 0 || !m_video.exists(m_vbuffer.ID)) return false;
	if(!m_video.exists(m_vformat.ID) || !m_video.exists(m_rstates.ID)) return false;
	if(!m_video.exists(m_vshader.ID) || !m_video.exists(m_pshader.ID)) return false;
	vr::screen &l_screen = m_video.get<vr::screen>(m_screen.ID); if(!l_screen.valid() || !l_screen.active()) return false;
	vr::vbuffer &l_vbuffer = m_video.get<vr::vbuffer>(m_vbuffer.ID); if(!l_vbuffer.valid()) return false;
	vr::vformat &l_vformat = m_video.get<vr::vformat>(m_vformat.ID); if(!l_vformat.valid()) return false;
	vr::rstates &l_rstates = m_video.get<vr::rstates>(m_rstates.ID); if(!l_rstates.valid()) return false;
	vr::vshader &l_vshader = m_video.get<vr::vshader>(m_vshader.ID); if(!l_vshader.valid()) return false;
	vr::pshader &l_pshader = m_video.get<vr::pshader>(m_pshader.ID); if(!l_pshader.valid()) return false;
	l_vbuffer.unlock(); m_vbuffer.data = 0;
	l_vbuffer.begin(0, sizeof(vertex));
	l_vformat.set();
	l_vshader.set();
	l_pshader.set();
	l_rstates.set();
	l_screen.draw_primitive(m_vbuffer.start / sizeof(vertex), m_vbuffer.used / sizeof(vertex) / 3);
	l_vbuffer.end();
	m_vbuffer.start += m_vbuffer.used; m_vbuffer.used = 0;
	return true;
}

} /* namespace bk -------------------------------------------------------------------------------*/
