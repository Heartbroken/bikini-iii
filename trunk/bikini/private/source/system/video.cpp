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
	static const int dummy_window_width = 100;
	static const int dummy_window_heigth = 100;
	static HWND create_dummy_window() {
		HINSTANCE l_instance = GetModuleHandle(0);
		wchar_t* l_window_class_name = L"bikini-iii video dummy window";
		WNDCLASSW l_window_class = { 0, DefWindowProcW, 0, 0, l_instance, 0, 0, 0, 0, l_window_class_name };
		RegisterClassW(&l_window_class);
		HWND l_handle = CreateWindowExW(0, l_window_class_name, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, dummy_window_width, dummy_window_heigth, 0, 0, l_instance, 0);
		if(l_handle == 0) std::cerr << "ERROR: Can't create dummy window\n";
		return l_handle;
	}
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
	m_d3dpresent_parameters.hDeviceWindow = _video_helper::create_dummy_window();
	m_d3dpresent_parameters.Windowed = true;
	m_d3dpresent_parameters.BackBufferWidth = _video_helper::dummy_window_width;
	m_d3dpresent_parameters.BackBufferHeight = _video_helper::dummy_window_heigth;
    m_d3dpresent_parameters.EnableAutoDepthStencil = false;
	m_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	if(FAILED(sm_direct3d9_p->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		0,
		D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE,
		&m_d3dpresent_parameters,
		&m_direct3ddevice9_p
	))) {
		std::cerr << "ERROR: Can't create D3D device\n";
		m_fsm.set_state(m_failed);
		return false;
	}
	m_fsm.set_state(m_ready);
	return true;
}
bool video::update(real _dt) {
	m_fsm.update(_dt);
	return true;
}
void video::destroy() {
	if(m_direct3ddevice9_p != 0) { while(m_direct3ddevice9_p->Release() != 0); m_direct3ddevice9_p = 0; }
	if(sm_direct3d9_p != 0 && sm_direct3d9_p->Release() == 0) sm_direct3d9_p = 0;
	DestroyWindow(m_d3dpresent_parameters.hDeviceWindow);
}
// void state
void video::m_void_b() {}
void video::m_void_u(real _dt) {}
void video::m_void_e() {}
// ready state
void video::m_ready_b() {}
void video::m_ready_u(real _dt) {}
void video::m_ready_e() {}
// failed state
void video::m_failed_b() {}
void video::m_failed_u(real _dt) {}
void video::m_failed_e() {}
// lost state
void video::m_lost_b() {}
void video::m_lost_u(real _dt) {}
void video::m_lost_e() {}

// video::resource

video::resource::resource(video &_video, uint _type) :
	device::resource(_video, _type)
{}

// video::swapchain

video::swapchain::swapchain(video &_video) :
	resource(_video, rt::swapchain),
	m_direct3dswapchain9_p(0)
{}
video::swapchain::~swapchain() {
}
bool video::swapchain::create() {
	return true;
}
void video::swapchain::destroy() {
	super::destroy();
}

} /* namespace bk -------------------------------------------------------------------------------*/
