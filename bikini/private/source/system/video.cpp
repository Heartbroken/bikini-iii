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
#if defined(WIN32)
	static HWND create_dummy_window() {
		HINSTANCE l_instance = GetModuleHandle(0);
		wchar_t* l_window_class_name = L"bikini-iii video dummy window";
		WNDCLASSW l_window_class = { 0, DefWindowProcW, 0, 0, l_instance, 0, 0, 0, 0, l_window_class_name };
		RegisterClassW(&l_window_class);
		HWND l_handle = CreateWindowExW(0, l_window_class_name, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 10, 10, 0, 0, l_instance, 0);
		if(l_handle == 0) std::cerr << "ERROR: Can't create dummy window\n";
		return l_handle;
	}
#endif
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
bool video::create() {
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
#if defined(WIN32)
	m_d3dpresent_parameters.hDeviceWindow = _video_helper::create_dummy_window();
#endif
	m_d3dpresent_parameters.Windowed = true;
	m_d3dpresent_parameters.BackBufferWidth = 0;
	m_d3dpresent_parameters.BackBufferHeight = 0;
    m_d3dpresent_parameters.EnableAutoDepthStencil = false;
	m_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	DWORD l_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE|D3DCREATE_PUREDEVICE;
#if defined(WIN32)
	l_flags |= D3DCREATE_MULTITHREADED;
#endif
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
#if defined(WIN32)
	HRESULT l_result = m_direct3ddevice9_p->TestCooperativeLevel();
	if(l_result == D3DERR_DEVICELOST) return m_fsm.set_state(m_lost);
#endif
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
		kill(l_ID);
	}
}
void video::m_lost_u(real _dt) {
#if defined(WIN32)
	HRESULT l_result = m_direct3ddevice9_p->TestCooperativeLevel();
	if(l_result == D3DERR_DEVICENOTRESET) {
		if(FAILED(m_direct3ddevice9_p->Reset(&m_d3dpresent_parameters))) return m_fsm.set_state(m_failed);
		return m_fsm.set_state(m_ready);
	}
	if(l_result == D3DERR_DRIVERINTERNALERROR) {
		return m_fsm.set_state(m_failed);
	}
#endif
}
void video::m_lost_e() {}

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
	video::resource::info(video::rt::screen), window(0), fullscreen(false), width(0), height(0)
{}

// screen

screen *screen::sm_activescreen_p = 0;
screen::screen(const info &_info, video &_video) :
	video::resource(_info, _video), m_backbuffer_p(0), m_depthstencil_p(0)
{}
bool screen::create() {
	destroy();
	if(!get_video().ready()) return false;
	const info &l_info = get_info();
#if defined(XBOX)
	if(FAILED(get_video().get_direct3ddevice9().CreateRenderTarget(l_info.width, l_info.height, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, 0, &m_backbuffer_p, 0))) {
		std::cerr << "ERROR: Can't create render target\n";
		return false;
	}
#elif defined(WIN32)
	D3DPRESENT_PARAMETERS l_d3dpresent_parameters;
	memset(&l_d3dpresent_parameters, 0, sizeof(l_d3dpresent_parameters));
	l_d3dpresent_parameters.hDeviceWindow = l_info.window;
	l_d3dpresent_parameters.Windowed = !l_info.fullscreen;
	l_d3dpresent_parameters.BackBufferWidth = l_info.width;
	l_d3dpresent_parameters.BackBufferHeight = l_info.height;
    l_d3dpresent_parameters.EnableAutoDepthStencil = false;
	l_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	l_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	if(FAILED(get_video().get_direct3ddevice9().CreateAdditionalSwapChain(&l_d3dpresent_parameters, &m_backbuffer_p))) {
		std::cerr << "ERROR: Can't create swap chain\n";
		return false;
	}
#endif
	if(FAILED(get_video().get_direct3ddevice9().CreateDepthStencilSurface(l_info.width, l_info.height, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, 0, &m_depthstencil_p, 0))) {
		m_backbuffer_p->Release();
		std::cerr << "ERROR: Can't create depth buffer\n";
		return false;
	}
#if defined(XBOX)
	if(FAILED(get_video().get_direct3ddevice9().SetRenderTarget(0, m_backbuffer_p))) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetDepthStencilSurface(m_depthstencil_p))) return false;
#endif
	return super::create();
}
void screen::destroy() {
	assert(sm_activescreen_p != this);
#if defined(XBOX)
	get_video().get_direct3ddevice9().SetRenderTarget(0, 0);
	get_video().get_direct3ddevice9().SetDepthStencilSurface(0);
#endif
	if(m_backbuffer_p != 0) {
		m_backbuffer_p->Release();
		m_backbuffer_p = 0;
	}
	if(m_depthstencil_p != 0) {
		m_depthstencil_p->Release();
		m_depthstencil_p = 0;
	}
	super::destroy();
}
bool screen::begin() {
	if(!valid() || !get_video().ready() || sm_activescreen_p != 0) return false;
	HRESULT l_result = S_OK;
#if defined(WIN32)
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = m_backbuffer_p->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(m_depthstencil_p); if(FAILED(l_result)) return false;
#endif
	l_result = get_video().get_direct3ddevice9().BeginScene(); if(FAILED(l_result)) return false;
	sm_activescreen_p = this;
	return true;
}
bool screen::clear(uint _flags, const color &_color, real _depth, uint _stencil) {
	if(!valid() || !get_video().ready() || sm_activescreen_p != this) return false;
	DWORD l_flags = 0;
	if(_flags&cf::color) l_flags |= D3DCLEAR_TARGET;
	if(_flags&cf::depth) l_flags |= D3DCLEAR_ZBUFFER;
	if(_flags&cf::stencil) l_flags |= D3DCLEAR_STENCIL;
	if(FAILED(get_video().get_direct3ddevice9().Clear(0, 0, l_flags, _color, (float)_depth, (DWORD)_stencil))) return false;
	return true;
}
bool screen::end() {
	if(!valid() || !get_video().ready() || sm_activescreen_p != this) return false;
	sm_activescreen_p = 0;
	HRESULT l_result = S_OK;
	l_result = get_video().get_direct3ddevice9().EndScene(); if(FAILED(l_result)) return false;
#if defined(WIN32)
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = get_video().get_direct3ddevice9().GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(0); if(FAILED(l_result)) return false;
#endif
	return true;
}
bool screen::present() {
	if(!valid() || !get_video().ready()) return false;
#if defined(XBOX)
	get_video().get_direct3ddevice9().Present(0, 0, 0, 0);
#elif defined(WIN32)
	if(FAILED(m_backbuffer_p->Present(0, 0, 0, 0, 0))) return false;
#endif
	return true;
}

} /* video resources ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
