/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

#pragma comment(lib, "d3d9")

namespace bk { /*--------------------------------------------------------------------------------*/

// video

IDirect3D9 *video::sm_direct3d9_p = 0;

video::video() : m_direct3ddevice9_p(0) {
}
video::~video() {
}
bool video::create() {
	if(sm_direct3d9_p == 0) {
		sm_direct3d9_p = Direct3DCreate9(D3D_SDK_VERSION);
		if(sm_direct3d9_p == 0) {
			std::cerr << "ERROR: Direct3DCreate9 failed.\n";
			return false;
		}
	} else {
		sm_direct3d9_p->AddRef();
	}
	return true;
}
void video::destroy() {
	if(m_direct3ddevice9_p != 0) { while(m_direct3ddevice9_p->Release() != 0); m_direct3ddevice9_p = 0; }
	if(sm_direct3d9_p != 0 && sm_direct3d9_p->Release() == 0) sm_direct3d9_p = 0;
}
bool video::activate(HWND _window) {
	memset(&m_d3dpresent_parameters, 0, sizeof(m_d3dpresent_parameters));
	m_d3dpresent_parameters.hDeviceWindow = _window;
	m_d3dpresent_parameters.Windowed = true;
	u32 l_wwidth, l_wheight;
	if(!m_d3dpresent_parameters.Windowed) {
		//l_pp.BackBufferWidth = l_mode.width;
		//l_pp.BackBufferHeight = l_mode.height;
		//l_pp.BackBufferFormat = backbuffer_format[l_mode.bbmode].format;
		//l_pp.FullScreen_RefreshRateInHz = l_mode.rrate;
		////l_pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	} else {
		RECT l_rect; GetClientRect(_window, &l_rect);
		l_wwidth = l_rect.right; l_wheight = l_rect.bottom;
		//l_pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		m_d3dpresent_parameters.FullScreen_RefreshRateInHz = 0;
		m_d3dpresent_parameters.BackBufferWidth = l_wwidth;
		m_d3dpresent_parameters.BackBufferHeight = l_wheight;
	}
    m_d3dpresent_parameters.EnableAutoDepthStencil = true;
	m_d3dpresent_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpresent_parameters.SwapEffect = /*D3DSWAPEFFECT_FLIP*/D3DSWAPEFFECT_DISCARD/*D3DSWAPEFFECT_COPY*/;
	m_d3dpresent_parameters.PresentationInterval = /*D3DPRESENT_INTERVAL_ONE*/D3DPRESENT_INTERVAL_IMMEDIATE;
	if(FAILED(sm_direct3d9_p->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE,
		&m_d3dpresent_parameters,
		&m_direct3ddevice9_p
	))) {
		MessageBoxA(_window, "ERROR: Can't create D3D device", "bikini-iii", MB_OK|MB_ICONSTOP);
		return false;
	}
	return true;
}
bool video::reset() {
	if(sm_direct3d9_p == 0 || m_direct3ddevice9_p == 0) return false;
	//
	RECT l_rect; GetClientRect(m_d3dpresent_parameters.hDeviceWindow, &l_rect);
	m_d3dpresent_parameters.BackBufferWidth = l_rect.right;
	m_d3dpresent_parameters.BackBufferHeight = l_rect.bottom;
	//
	HRESULT l_res = m_direct3ddevice9_p->Reset(&m_d3dpresent_parameters);
	if(SUCCEEDED(l_res)) return true;
	std::cerr << "ERROR: Can't reset device\n";
	return false;
}
bool video::begin_scene() {
	if(sm_direct3d9_p == 0 || m_direct3ddevice9_p == 0) return false;
	HRESULT l_res = m_direct3ddevice9_p->BeginScene();
	if(SUCCEEDED(l_res)) return true;
	std::cerr << "ERROR: Can't begin scene\n";
	return false;
}
bool video::end_scene() {
	if(sm_direct3d9_p == 0 || m_direct3ddevice9_p == 0) return false;
	HRESULT l_res = m_direct3ddevice9_p->EndScene();
	if(SUCCEEDED(l_res)) return true;
	std::cerr << "ERROR: Can't end scene\n";
	return false;
}
bool video::present() {
	if(sm_direct3d9_p == 0 || m_direct3ddevice9_p == 0) return false;
	HRESULT l_res = m_direct3ddevice9_p->Present(0, 0, 0, 0);
	if(SUCCEEDED(l_res)) return true;
	std::cerr << "ERROR: Can't present scene\n";
	return false;
}
bool video::clear_viewport(/*uint _flags, const rgba &_color, real _depth, uint _stencil*/) {
	if(sm_direct3d9_p == 0 || m_direct3ddevice9_p == 0) return false;
	HRESULT l_res = m_direct3ddevice9_p->Clear(0, 0, D3DCLEAR_TARGET, 0xffffff00, 1.f, 0);
	if(SUCCEEDED(l_res)) return true;
	std::cerr << "ERROR: Can't clear viewport\n";
	return false;
}

} /* namespace bk -------------------------------------------------------------------------------*/
