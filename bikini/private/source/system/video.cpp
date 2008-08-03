/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

#pragma comment(lib, "d3d9")

namespace bk { /*--------------------------------------------------------------------------------*/

// _video_helper

struct _video_helper {
#	if defined(WIN32)
	static HWND create_dummy_window() {
		HINSTANCE l_instance = GetModuleHandle(0);
		wchar_t* l_window_class_name = L"bikini-iii video dummy window";
		WNDCLASSW l_window_class = { 0, DefWindowProcW, 0, 0, l_instance, 0, 0, 0, 0, l_window_class_name };
		RegisterClassW(&l_window_class);
		HWND l_handle = CreateWindowExW(0, l_window_class_name, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 10, 10, 0, 0, l_instance, 0);
		if(l_handle == 0) std::cerr << "ERROR: Can't create dummy window\n";
		return l_handle;
	}
#	endif
};

// video

IDirect3D9 *video::sm_direct3d9_p = 0;

video::video() :
	m_direct3ddevice9_p(0),
	m_void(&video::m_void_b, &video::m_void_u, &video::m_void_e),
	m_ready(&video::m_ready_b, &video::m_ready_u, &video::m_ready_e),
	m_failed(&video::m_failed_b, &video::m_failed_u, &video::m_failed_e),
	m_lost(&video::m_lost_b, &video::m_lost_u, &video::m_lost_e),
	m_fsm(*this, m_void)
{}
video::~video() {
	if(m_direct3ddevice9_p != 0) {
		std::cerr << "ERROR: Destroy video device before deleting\n";
		assert(m_direct3ddevice9_p == 0);
	}
}
bool video::create(bool _multithreaded) {
	if(sm_direct3d9_p == 0) {
		sm_direct3d9_p = Direct3DCreate9(D3D_SDK_VERSION);
		if(sm_direct3d9_p == 0) {
			std::cerr << "ERROR: Can't create Direct3D object.\n";
			m_fsm.set_state(m_failed);
			return false;
		}
	} else {
		sm_direct3d9_p->AddRef();
	}
	memset(&m_d3dpresent_parameters, 0, sizeof(m_d3dpresent_parameters));
#	if defined(WIN32)
	m_d3dpresent_parameters.hDeviceWindow = _video_helper::create_dummy_window();
#	endif
	m_d3dpresent_parameters.Windowed = true;
	m_d3dpresent_parameters.BackBufferWidth = 0;
	m_d3dpresent_parameters.BackBufferHeight = 0;
    m_d3dpresent_parameters.EnableAutoDepthStencil = false;
	m_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

#	if defined(XBOX)
	XVIDEO_MODE l_mode; memset(&l_mode, 0, sizeof(l_mode)); XGetVideoMode(&l_mode);
	bool l_enable720p = l_mode.dwDisplayWidth >= 1280;
	m_d3dpresent_parameters.BackBufferWidth  = l_enable720p ? 1280 : 640;
	m_d3dpresent_parameters.BackBufferHeight = l_enable720p ? 720 : 480;
#	endif

	DWORD l_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE|D3DCREATE_PUREDEVICE;
#	if defined(WIN32)
	if(_multithreaded) l_flags |= D3DCREATE_MULTITHREADED;
#	endif
	if(FAILED(sm_direct3d9_p->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		0,
		l_flags,
		&m_d3dpresent_parameters,
		&m_direct3ddevice9_p
	))) {
		std::cerr << "ERROR: Can't create D3D device\n";
		m_fsm.set_state(m_failed);
		return false;
	}
	m_fsm.set_state(m_ready);
	m_fsm.update(0);
	return true;
}
bool video::update(real _dt) {
	m_fsm.update(_dt);
	return true;
}
void video::destroy() {
	if(m_direct3ddevice9_p != 0) { while(m_direct3ddevice9_p->Release() != 0); m_direct3ddevice9_p = 0; }
	if(sm_direct3d9_p != 0 && sm_direct3d9_p->Release() == 0) sm_direct3d9_p = 0;
	m_fsm.set_state(m_void);
	m_fsm.update(0);
}
// void state
void video::m_void_b() {}
void video::m_void_u(real _dt) {}
void video::m_void_e() {}
// ready state
void video::m_ready_b() {}
void video::m_ready_u(real _dt) {
#	if defined(WIN32)
	HRESULT l_result = m_direct3ddevice9_p->TestCooperativeLevel();
	if(l_result == D3DERR_DEVICELOST) return m_fsm.set_state(m_lost);
#	endif
}
void video::m_ready_e() {}
// failed state
void video::m_failed_b() {}
void video::m_failed_u(real _dt) {}
void video::m_failed_e() {}
// lost state
void video::m_lost_b() {
	for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
		get<resource>(l_ID).destroy();
	}
}
void video::m_lost_u(real _dt) {
#	if defined(WIN32)
	HRESULT l_result = m_direct3ddevice9_p->TestCooperativeLevel();
	if(l_result == D3DERR_DEVICENOTRESET) {
		if(FAILED(m_direct3ddevice9_p->Reset(&m_d3dpresent_parameters))) return m_fsm.set_state(m_failed);
		return m_fsm.set_state(m_ready);
	}
	if(l_result == D3DERR_DRIVERINTERNALERROR) {
		return m_fsm.set_state(m_failed);
	}
#	endif
}
void video::m_lost_e() {
	for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
		get<resource>(l_ID).create();
	}
}

// video::resource::info

video::resource::info::info(uint _type) :
	device::resource::info(_type)
{}

// video::resource

video::resource::resource(const info &_info, video &_video) :
	device::resource(_info, _video)
{}

namespace vr { /* video resources ---------------------------------------------------------------*/

// screen::info

screen::info::info() :
	video::resource::info(video::rt::screen)
{}

// screen

screen *screen::sm_activescreen_p = 0;
#if defined(XBOX)
screen::screen(const info &_info, video &_video) :
	video::resource(_info, _video)
{}
#elif defined(WIN32)
screen::screen(const info &_info, video &_video, HWND _window, bool _fullscreen, uint _width, uint _height) :
	video::resource(_info, _video),
	m_window(_window), m_fullscreen(_fullscreen), m_width(_width), m_height(_height),
	m_backbuffer_p(0), m_depthstencil_p(0)
{}
#endif
bool screen::create() {
	destroy();
	thread::locker l_locker(m_lock);
	if(!get_video().ready()) return false;
#	if defined(XBOX)
	if(sm_activescreen_p != 0) return false;
	sm_activescreen_p = this;
#	elif defined(WIN32)
	if(m_width == 0 || m_height == 0) return false;
	D3DPRESENT_PARAMETERS l_d3dpresent_parameters;
	memset(&l_d3dpresent_parameters, 0, sizeof(l_d3dpresent_parameters));
	l_d3dpresent_parameters.hDeviceWindow = m_window;
	l_d3dpresent_parameters.Windowed = !m_fullscreen;
	l_d3dpresent_parameters.BackBufferWidth = m_width;
	l_d3dpresent_parameters.BackBufferHeight = m_height;
    l_d3dpresent_parameters.EnableAutoDepthStencil = false;
	l_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	l_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	if(FAILED(get_video().get_direct3ddevice9().CreateAdditionalSwapChain(&l_d3dpresent_parameters, &m_backbuffer_p))) {
		std::cerr << "ERROR: Can't create swap chain\n";
		return false;
	}
	if(FAILED(get_video().get_direct3ddevice9().CreateDepthStencilSurface(m_width, m_height, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, 0, &m_depthstencil_p, 0))) {
		m_backbuffer_p->Release(); m_backbuffer_p = 0;
		std::cerr << "ERROR: Can't create depth buffer\n";
		return false;
	}
#	endif
	return super::create();
}
void screen::destroy() {
#	if defined(WIN32)
	if(active()) end();
#	endif
	thread::locker l_locker(m_lock);
#	if defined(XBOX)
	sm_activescreen_p = 0;
#	elif defined(WIN32)
	if(m_backbuffer_p != 0) {
		m_backbuffer_p->Release();
		m_backbuffer_p = 0;
	}
	if(m_depthstencil_p != 0) {
		m_depthstencil_p->Release();
		m_depthstencil_p = 0;
	}
#	endif
	super::destroy();
}
bool screen::begin() {
	thread::locker l_locker(m_lock);
	if(!valid() || !get_video().ready()) return false;
#	if defined(WIN32)
	if(sm_activescreen_p != 0) return false;
	HRESULT l_result = S_OK;
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = m_backbuffer_p->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(m_depthstencil_p); if(FAILED(l_result)) return false;
	sm_activescreen_p = this;
#	endif
	if(FAILED(get_video().get_direct3ddevice9().BeginScene())) return false;
	return true;
}
bool screen::clear(uint _flags, const color &_color, real _depth, uint _stencil) {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid()) return false;
	screen *l_save_activescreen_p = sm_activescreen_p;
	if(l_save_activescreen_p != this) { if(l_save_activescreen_p != 0) { l_save_activescreen_p->end(); } begin(); }
	DWORD l_flags = 0;
	if(_flags&cf::color) l_flags |= D3DCLEAR_TARGET;
	if(_flags&cf::depth) l_flags |= D3DCLEAR_ZBUFFER;
	if(_flags&cf::stencil) l_flags |= D3DCLEAR_STENCIL;
	if(FAILED(get_video().get_direct3ddevice9().Clear(0, 0, l_flags, _color, (float)_depth, (DWORD)_stencil))) return false;
	if(l_save_activescreen_p != this) { end(); if(l_save_activescreen_p != 0) { l_save_activescreen_p->begin(); } }
	return true;
}
bool screen::draw_primitive(uint _start, uint _count) {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid() || !active()) return false;
	if(FAILED(get_video().get_direct3ddevice9().DrawPrimitive(D3DPT_TRIANGLELIST, _start, _count))) return false;
	return true;
}
bool screen::end() {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid() || !active()) return false;
	if(FAILED(get_video().get_direct3ddevice9().EndScene())) return false;
#	if defined(WIN32)
	sm_activescreen_p = 0;
	HRESULT l_result = S_OK;
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = get_video().get_direct3ddevice9().GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(0); if(FAILED(l_result)) return false;
#	endif
	return true;
}
bool screen::present() {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid()) return false;
#	if defined(XBOX)
	get_video().get_direct3ddevice9().Present(0, 0, 0, 0);
#	elif defined(WIN32)
	if(FAILED(m_backbuffer_p->Present(0, 0, 0, 0, 0))) return false;
#	endif
	return true;
}

// vbuffer::info

vbuffer::info::info() :
	video::resource::info(video::rt::vbuffer)
{}

// vbuffer

vbuffer* vbuffer::sm_activevbuffers_p[vbuffer::sm_maxvbuffers];
static bool sg_init_activevbuffers = false;

vbuffer::vbuffer(const info &_info, video &_video, uint _size, bool _dynamic) :
	video::resource(_info, _video),
	m_size(_size), m_dynamic(_dynamic),
	m_index(bad_ID), m_offset(0), m_stride(0),
	m_buffer_p(0)
{
	if(!sg_init_activevbuffers) {
		sg_init_activevbuffers = true;
		memset(sm_activevbuffers_p, 0, sizeof(sm_activevbuffers_p));
	}
}
bool vbuffer::create() {
	destroy();
	thread::locker l_locker(m_lock);
	if(!get_video().ready()) return false;
	if(m_size == 0) return false;
	if(FAILED(get_video().get_direct3ddevice9().CreateVertexBuffer(m_size, 0, 0, D3DPOOL_DEFAULT, &m_buffer_p, 0))) {
		std::cerr << "ERROR: Can't create vertex buffer\n";
		return false;
	}
	return true;
}
handle vbuffer::lock(uint _offset, uint _size, bool _discard) {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid()) return 0;
	handle l_handle = 0;
	if(FAILED(m_buffer_p->Lock(_offset, _size, &l_handle, _discard ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE))) {
		std::cerr << "ERROR: Can't lock vertex buffer\n";
		return 0;
	}
	return l_handle;
}
bool vbuffer::unlock() {
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid()) return false;
	if(FAILED(m_buffer_p->Unlock())) {
		std::cerr << "ERROR: Can't unlock vertex buffer\n";
		return false;
	}
	return true;
}
bool vbuffer::begin(uint _index, uint _offset, uint _stride) {
	assert(_index < sm_maxvbuffers);
	thread::locker l_locker(m_lock);
	if(!get_video().ready() || !valid()) return false;
	if(sm_activevbuffers_p[_index] == this && _index == m_index && _offset == m_offset && _stride == m_stride) return true;
	if(sm_activevbuffers_p[_index] != 0) sm_activevbuffers_p[_index]->end();
	if(FAILED(get_video().get_direct3ddevice9().SetStreamSource(_index, m_buffer_p, _offset, _stride))) {
		std::cerr << "ERROR: Can't set stream source\n";
		return false;
	}
	m_index = _index; m_offset = _offset; m_stride = _stride;
	return true;
}
bool vbuffer::end() {
	thread::locker l_locker(m_lock);
	if(m_index == bad_ID) return false;
	if(!get_video().ready() || !valid()) return false;
	sm_activevbuffers_p[m_index] = 0;
	uint l_index = bad_ID; swap(l_index, m_index);
	if(FAILED(get_video().get_direct3ddevice9().SetStreamSource(l_index, 0, 0, 0))) {
		std::cerr << "ERROR: Can't unset stream source\n";
		return false;
	}
	return true;
}
void vbuffer::destroy() {
	if(active()) end();
	thread::locker l_locker(m_lock);
	if(m_buffer_p != 0) {
		m_buffer_p->Release();
		m_buffer_p = 0;
	}
}

} /* video resources ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
