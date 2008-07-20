/*//-----------------------------------------------------------------------------------------------

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*///-----------------------------------------------------------------------------------------------

#include "header.hpp"

namespace bk { //----------------------------------------------------------------------------------

window::window() : m_handle(0), m_oldproc(0) {
}

window::~window() {
}

bool window::create(uint _width, uint _height, HICON _icon) {
	HINSTANCE l_instance = GetModuleHandle(0);
    WNDCLASSW l_window_class = { 
		CS_HREDRAW|CS_VREDRAW,
		window::window_proc,
		0,
		0,
		l_instance,
        _icon,
        LoadCursor(NULL, IDC_ARROW), 
        (HBRUSH)GetStockObject(BLACK_BRUSH), NULL,
        L"bikini-iii window"
	};
    RegisterClassW(&l_window_class);
	m_handle = CreateWindowExW(
		WS_EX_TOOLWINDOW|WS_EX_APPWINDOW|WS_EX_RIGHT,
		L"bikini-iii window",
		0,
		WS_BORDER|WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(int)_width,
		(int)_height,
		0,
		0,
		l_instance,
		0
	);
	if(m_handle == 0) return false;
	set_size(_width, _height);
	SetWindowLong(m_handle, GWL_USERDATA, (LONG)(LONG_PTR)this);
	return true;
}

bool window::create(HWND _handle) {
	m_handle = _handle;
	m_oldproc = (WNDPROC)(LONG_PTR)GetWindowLong(m_handle, GWL_WNDPROC);
	SetWindowLong(m_handle, GWL_WNDPROC, (LONG)(LONG_PTR)window_proc);
	SetWindowLong(m_handle, GWL_USERDATA, (LONG)(LONG_PTR)this);
	return true;
}

void window::destroy() {
	if(m_handle != 0) DestroyWindow(m_handle);
}

HWND window::handle() {
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
	GetWindowRect(m_handle, &l_wrect);
	GetClientRect(m_handle, &l_crect);
	uint l_width = _width + (l_wrect.right - l_wrect.left) - (l_crect.right - l_crect.left);
	uint l_height = _height + (l_wrect.bottom - l_wrect.top) - (l_crect.bottom - l_crect.top);
	POINT l_shift = { l_wrect.left, l_wrect.top }; ScreenToClient(m_handle, &l_shift);
	sint l_left = (l_drect.right - (sint)_width) / 2 + l_shift.x;
	sint l_top = (l_drect.bottom - (sint)_height) / 2 + l_shift.y;
	MoveWindow(m_handle, l_left, l_top, l_width, l_height, TRUE);
}

bool window::update(real _dt) {
	if(m_handle == 0) return false;
	MSG l_message;
	while(PeekMessage(&l_message, NULL, 0U, 0U, PM_REMOVE)) {
		TranslateMessage(&l_message);
		DispatchMessage(&l_message);
		if(l_message.message == WM_QUIT) return false;
	}
	return true;
}

LRESULT CALLBACK window::window_proc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam) {
	window &l_window = *reinterpret_cast<window*>((LONG_PTR)GetWindowLong(_handle, GWL_USERDATA));
	if(&l_window != 0) return l_window.m_proc(_message, _wparam, _lparam);
	return DefWindowProc(_handle, _message, _wparam, _lparam);
}

LRESULT window::m_proc(UINT _message, WPARAM _wparam, LPARAM _lparam) {
	switch(_message) {
		case WM_CLOSE : {
			DestroyWindow(m_handle);
		} break;
		case WM_DESTROY : {
			if(m_oldproc == 0) PostQuitMessage(0);
			m_handle = 0;
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
	return DefWindowProc(m_handle, _message, _wparam, _lparam);
}

} // namespace bk //-------------------------------------------------------------------------------
