/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"


#if defined(XBOX)
#	if defined(_DEBUG)
#		pragma comment(lib, "d3d9d")
#	else
#		pragma comment(lib, "d3d9")
#	endif
//#	pragma comment(lib, "xapilibd")
//#	pragma comment(lib, "d3dx9d")
//#	pragma comment(lib, "xgraphicsd")
//#	pragma comment(lib, "xboxkrnl")
#elif defined(WIN32)
#	pragma comment(lib, "d3d9")
#endif

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
	m_screen_ID(bad_ID), m_vbuffer_ID(bad_ID),
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
	m_d3dpresent_parameters.BackBufferWidth = 10;
	m_d3dpresent_parameters.BackBufferHeight = 10;
	m_d3dpresent_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpresent_parameters.FullScreen_RefreshRateInHz = 0;
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
		m_d3dpresent_parameters.hDeviceWindow,
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
	if(!super::update(_dt)) return false;
	m_fsm.update(_dt);
	if(!ready()) return false;
	//for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
	//	resource &l_resource = get<resource>(l_ID);
	//	if(!l_resource.valid() && !l_resource.create()) kill(l_ID);
	//}
	return true;
}
void video::destroy() {
	m_fsm.set_state(m_void);
	m_fsm.update(0);
	for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) kill(l_ID);
	if(m_direct3ddevice9_p != 0) { while(m_direct3ddevice9_p->Release() != 0); m_direct3ddevice9_p = 0; }
	if(sm_direct3d9_p != 0 && sm_direct3d9_p->Release() == 0) sm_direct3d9_p = 0;
	super::destroy();
}
// void state
void video::m_void_b() {}
void video::m_void_u(real _dt) {}
void video::m_void_e() {}
// ready state
void video::m_ready_b() {
	//for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
	//	get<resource>(l_ID).create();
	//}
}
void video::m_ready_u(real _dt) {
#	if defined(WIN32)
	HRESULT l_result = m_direct3ddevice9_p->TestCooperativeLevel();
	if(l_result == D3DERR_DEVICELOST) return m_fsm.set_state(m_lost);
#	endif
}
void video::m_ready_e() {
	//for(uint l_ID = get_first_ID(); l_ID != bad_ID; l_ID = get_next_ID(l_ID)) {
	//	get<resource>(l_ID).destroy();
	//}
}
// failed state
void video::m_failed_b() {}
void video::m_failed_u(real _dt) {}
void video::m_failed_e() {}
// lost state
void video::m_lost_b() {}
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

// window::info

window::info::info() : video::resource::info(video::rt::window) {}

// window
window::window(const info &_info, video &_video, HWND _window) :
	video::resource(_info, _video), m_window(_window),
	m_backbuffer_p(0), m_depthstencil_p(0),
	m_size(sint2_0)
{
	m_oldwndproc = (WNDPROC)SetWindowLong(m_window, GWL_WNDPROC, (LONG)_wndproc);
	SetWindowLong(m_window, GWL_USERDATA, (LONG)this);
}
window::~window()
{
	if (m_backbuffer_p)
	{
		m_backbuffer_p->Release();
		m_backbuffer_p = 0;
	}
	if (m_depthstencil_p)
	{
		m_depthstencil_p->Release();
		m_depthstencil_p = 0;
	}
	SetWindowLong(m_window, GWL_WNDPROC, (LONG)m_oldwndproc);
}
bool window::update(real _dt)
{
	RECT l_crect; GetClientRect(m_window, &l_crect);
	if (l_crect.right != m_size.x() || l_crect.bottom != m_size.y())
	{
		m_size = sint2(l_crect.right, l_crect.bottom);

		set_invalid();

		if (m_backbuffer_p)
		{
			m_backbuffer_p->Release();
			m_backbuffer_p = 0;
		}
		if (m_depthstencil_p)
		{
			m_depthstencil_p->Release();
			m_depthstencil_p = 0;
		}

		do
		{

			if (m_size.x() == 0 || m_size.y() == 0)
			{
				break;
			}

			D3DPRESENT_PARAMETERS l_d3dpp;
			memset(&l_d3dpp, 0, sizeof(l_d3dpp));
			l_d3dpp.hDeviceWindow = m_window;
			l_d3dpp.Windowed = TRUE;
			l_d3dpp.BackBufferWidth = (UINT)m_size.x();
			l_d3dpp.BackBufferHeight = (UINT)m_size.y();
			l_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
			l_d3dpp.FullScreen_RefreshRateInHz = 0;
			l_d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)4;
			l_d3dpp.MultiSampleQuality = 0;
			l_d3dpp.EnableAutoDepthStencil = FALSE;
			l_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			l_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

			if (FAILED(get_video().get_direct3ddevice9().CreateAdditionalSwapChain(
					&l_d3dpp, &m_backbuffer_p
				)))
			{
				break;
			}

			if (FAILED(get_video().get_direct3ddevice9().CreateDepthStencilSurface(
					l_d3dpp.BackBufferWidth, l_d3dpp.BackBufferHeight,
					D3DFMT_D24S8, l_d3dpp.MultiSampleType,
					l_d3dpp.MultiSampleQuality, 0, &m_depthstencil_p, 0
				)))
			{
				m_backbuffer_p->Release(); m_backbuffer_p = 0;
				break;
			}

			update_version();
		}
		while(false);
	}

	if (valid())
	{
		if (SUCCEEDED(get_video().get_direct3ddevice9().BeginScene()))
		{
			IDirect3DSurface9 *l_backbuffer_p = 0;
			if (SUCCEEDED(m_backbuffer_p->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p)))
			{
				if (SUCCEEDED(get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p)))
				{
					if (SUCCEEDED(get_video().get_direct3ddevice9().SetDepthStencilSurface(m_depthstencil_p)))
					{
							get_video().get_direct3ddevice9().Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
					}
				}
				l_backbuffer_p->Release();
			}
			get_video().get_direct3ddevice9().EndScene();
			m_backbuffer_p->Present(0, 0, 0, 0, 0);
		}
	}

	return true;
}
long _stdcall window::_wndproc(HWND _window, uint _message, uint _wparam, uint _lparam)
{
	window &l_window = *(window*)GetWindowLong(_window, GWL_USERDATA);
	return l_window.m_wndproc(_message, _wparam, _lparam);
}
long window::m_wndproc(uint _message, uint _wparam, uint _lparam)
{
	switch (_message)
	{
		case WM_ERASEBKGND : return 1;

		case WM_SIZE :
		case WM_SIZING : {
			m_size = sint2_0;
		} break;
	}
	return CallWindowProc(m_oldwndproc, m_window, _message, _wparam, _lparam);
}
/*

// screen::info

screen::info::info() :
	video::resource::info(video::rt::screen)
{}

// screen

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
screen::~screen() {
	destroy();
}
bool screen::create() {
	destroy();
	if(lock l = lock(section())) {
		if(!get_video().ready()) return false;
#		if defined(XBOX)
		if(get_video().screen_ID() != bad_ID) return false;
		get_video().set_screen_ID(ID());
#		elif defined(WIN32)
		if(m_width == 0 || m_height == 0) return false;
		D3DPRESENT_PARAMETERS l_d3dpresent_parameters;
		memset(&l_d3dpresent_parameters, 0, sizeof(l_d3dpresent_parameters));
		l_d3dpresent_parameters.hDeviceWindow = m_window;
		l_d3dpresent_parameters.Windowed = !m_fullscreen;
		l_d3dpresent_parameters.BackBufferWidth = m_width;
		l_d3dpresent_parameters.BackBufferHeight = m_height;
		l_d3dpresent_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
		l_d3dpresent_parameters.FullScreen_RefreshRateInHz = 0;
		l_d3dpresent_parameters.MultiSampleType = (D3DMULTISAMPLE_TYPE)4;
		l_d3dpresent_parameters.MultiSampleQuality = 0;
		l_d3dpresent_parameters.EnableAutoDepthStencil = false;
		l_d3dpresent_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		l_d3dpresent_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		if(m_fullscreen) {
			if(FAILED(get_video().get_direct3ddevice9().Reset(&l_d3dpresent_parameters))) {
				std::cerr << "ERROR: Can't reset device\n";
				return false;
			}
			if(FAILED(get_video().get_direct3ddevice9().GetSwapChain(0, &m_backbuffer_p))) {
				std::cerr << "ERROR: Can't get device fullscreen swap chain\n";
				return false;
			}
			MoveWindow(m_window, 0, 0, m_width, m_height, false);
		} else {
			if(FAILED(get_video().get_direct3ddevice9().CreateAdditionalSwapChain(&l_d3dpresent_parameters, &m_backbuffer_p))) {
				std::cerr << "ERROR: Can't create swap chain\n";
				return false;
			}
		}
		if(FAILED(get_video().get_direct3ddevice9().CreateDepthStencilSurface(m_width, m_height, D3DFMT_D24S8, l_d3dpresent_parameters.MultiSampleType, l_d3dpresent_parameters.MultiSampleQuality, 0, &m_depthstencil_p, 0))) {
			m_backbuffer_p->Release(); m_backbuffer_p = 0;
			std::cerr << "ERROR: Can't create depth buffer\n";
			return false;
		}
#		endif
	}
	return super::create();
}
void screen::destroy() {
#	if defined(WIN32)
	if(active()) end();
#	endif
	thread::locker l_locker(section());
#	if defined(XBOX)
	assert(get_video().screen_ID() == ID());
	get_video().set_screen_ID(bad_ID);
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
	thread::locker l_locker(section());
	if(!valid() || !get_video().ready()) return false;
#	if defined(XBOX)
	if(FAILED(get_video().get_direct3ddevice9().BeginScene())) return false;
#	elif defined(WIN32)
	if(get_video().screen_ID() != bad_ID) return false;
	HRESULT l_result = S_OK;
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = m_backbuffer_p->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(m_depthstencil_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().BeginScene(); if(FAILED(l_result)) return false;
	get_video().set_screen_ID(ID());
#	endif
	return true;
}
bool screen::clear(uint _flags, const color &_color, real _depth, uint _stencil) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
	uint l_save_screen_ID = get_video().screen_ID();
	if(l_save_screen_ID != ID()) {
		if(get_video().exists(l_save_screen_ID)) {
			assert(get_video().get(l_save_screen_ID).type() == video::rt::screen);
			get_video().get<screen>(l_save_screen_ID).end();
		}
		begin();
	}
	DWORD l_flags = 0;
	if(_flags&cf::color) l_flags |= D3DCLEAR_TARGET;
	if(_flags&cf::depth) l_flags |= D3DCLEAR_ZBUFFER;
	if(_flags&cf::stencil) l_flags |= D3DCLEAR_STENCIL;
	if(FAILED(get_video().get_direct3ddevice9().Clear(0, 0, l_flags, _color, (float)_depth, (DWORD)_stencil))) return false;
	if(l_save_screen_ID != ID()) {
		end();
		if(get_video().exists(l_save_screen_ID)) {
			assert(get_video().get(l_save_screen_ID).type() == video::rt::screen);
			get_video().get<screen>(l_save_screen_ID).begin();
		}
	}
	return true;
}
bool screen::set_scissor(uint _x0, uint _y0, uint _x1, uint _y1) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || !active()) return false;
	RECT l_r = { _x0, _y0, _x1, _y1 };
	if(FAILED(get_video().get_direct3ddevice9().SetScissorRect(&l_r))) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE))) return false;
	return true;
}
bool screen::remove_scissor() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || !active()) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE))) return false;
	return true;
}
bool screen::draw_primitive(uint _start, uint _count) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || !active()) return false;
	if(FAILED(get_video().get_direct3ddevice9().DrawPrimitive(D3DPT_TRIANGLELIST, _start, _count))) return false;
	return true;
}
bool screen::end() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || !active()) return false;
	if(FAILED(get_video().get_direct3ddevice9().EndScene())) return false;
#	if defined(WIN32)
	get_video().set_screen_ID(bad_ID);
	HRESULT l_result = S_OK;
	IDirect3DSurface9 *l_backbuffer_p = 0;
	l_result = get_video().get_direct3ddevice9().GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &l_backbuffer_p); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetRenderTarget(0, l_backbuffer_p); l_backbuffer_p->Release(); if(FAILED(l_result)) return false;
	l_result = get_video().get_direct3ddevice9().SetDepthStencilSurface(0); if(FAILED(l_result)) return false;
#	endif
	return true;
}
bool screen::present() {
	thread::locker l_locker(section());
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

vbuffer::vbuffer(const info &_info, video &_video) :
	video::resource(_info, _video)
{}
vbuffer::~vbuffer() {
	destroy();
}
bool vbuffer::create() {
	destroy();
	thread::locker l_locker(section());
	if(!get_video().ready()) return false;
	HRESULT l_result = S_OK;
	const info &l_info = get_info();
	assert(!l_info.descs.empty());
	for(uint i = 0, s = l_info.descs.size(); i < s; ++i) {
		const desc &l_desc = l_info.descs[i];
		IDirect3DVertexBuffer9 *l_buffer_p;
#		if defined(XBOX)
		DWORD l_usege = 0;
#		elif defined(WIN32)
		DWORD l_usege = l_desc.dynamic ? (D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY) : 0;
#		endif
		l_result = get_video().get_direct3ddevice9().CreateVertexBuffer(
			l_desc.size, l_usege, 0, D3DPOOL_DEFAULT, &l_buffer_p, 0
		);
		if(FAILED(l_result)) break;
		m_buffers.push_back(l_buffer_p);
	}
	if(FAILED(l_result)) {
		while(!m_buffers.empty()) {
			m_buffers.back()->Release();
			m_buffers.pop_back();
		}
		std::cerr << "ERROR: Can't create vertex buffer\n";
		return false;
	}
	return super::create();
}
handle vbuffer::lock(uint _index) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return 0;
	assert(_index < m_buffers.size());
	handle l_handle = 0;
	if(FAILED(m_buffers[_index]->Lock(0, 0, &l_handle, D3DLOCK_NOOVERWRITE))) {
		std::cerr << "ERROR: Can't lock vertex buffer\n";
		return 0;
	}
	return l_handle;
}
bool vbuffer::unlock(uint _index) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
	assert(_index < m_buffers.size());
	if(FAILED(m_buffers[_index]->Unlock())) {
		std::cerr << "ERROR: Can't unlock vertex buffer\n";
		return false;
	}
	return true;
}
bool vbuffer::begin(uint _offset, uint _stride) {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || get_video().vbuffer_ID() != bad_ID) return false;
	assert((_offset == 0 && _stride == 0) || m_buffers.size() == 1);
	HRESULT l_result = S_OK;
	const info &l_info = get_info();
	for(uint i = 0, s = m_buffers.size(); i < s; ++i) {
		const desc &l_desc = l_info.descs[i];
		l_result = get_video().get_direct3ddevice9().SetStreamSource(
			i, m_buffers[i], _offset, _stride ? _stride : l_desc.stride
		);
		if(FAILED(l_result)) break;
	}
	if(FAILED(l_result)) {
		for(uint i = 0, s = m_buffers.size(); i < s; ++i) {
			get_video().get_direct3ddevice9().SetStreamSource(i, 0, 0, 0);
		}
		std::cerr << "ERROR: Can't set stream source\n";
		return false;
	}
	return true;
}
bool vbuffer::end() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid() || !active()) return false;
	get_video().set_vbuffer_ID(bad_ID);
	for(uint i = 0, s = m_buffers.size(); i < s; ++i) {
		get_video().get_direct3ddevice9().SetStreamSource(i, 0, 0, 0);
	}
	return true;
}
void vbuffer::destroy() {
	if(active()) end();
	thread::locker l_locker(section());
	while(!m_buffers.empty()) {
		m_buffers.back()->Release();
		m_buffers.pop_back();
	}
	super::destroy();
}

// vformat::info

vformat::info::info() :
	video::resource::info(video::rt::vformat)
{}

// vformat

const vformat::element vformat::end(0xff, 0, D3DDECLTYPE_UNUSED, 0, 0, 0);

vformat::vformat(const info &_info, video &_video) :
	video::resource(_info, _video),
	m_format_p(0)
{}
vformat::~vformat() {
	destroy();
}
bool vformat::create() {
	destroy();
	thread::locker l_locker(section());
	if(!get_video().ready()) return false;
	if(get_info().format.empty() || memcmp(&get_info().format.back(), &end, sizeof(end)) != 0) return false;
	if(FAILED(get_video().get_direct3ddevice9().CreateVertexDeclaration((D3DVERTEXELEMENT9*)&get_info().format[0], &m_format_p))) {
		std::cerr << "ERROR: Can't create vertex declaration\n";
		return false;
	}
	return super::create();
}
bool vformat::set() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetVertexDeclaration(m_format_p))) {
		std::cerr << "ERROR: Can't set vertex declaration\n";
		return false;
	}
	return true;
}
void vformat::destroy() {
	thread::locker l_locker(section());
	if(m_format_p != 0) {
		m_format_p->Release();
		m_format_p = 0;
	}
	super::destroy();
}

// rstates::info

rstates::info::info() :
	video::resource::info(video::rt::rstates)
{}

// rstates

rstates::rstates(const info &_info, video &_video) :
	video::resource(_info, _video),
	m_block_p(0)
{}
rstates::~rstates() {
	destroy();
}
bool rstates::create() {
	destroy();
	thread::locker l_locker(section());
	if(!get_video().ready()) return false;
#	if defined(WIN32)
	if(FAILED(get_video().get_direct3ddevice9().BeginStateBlock())) {
		std::cerr << "ERROR: Can't start state block capture\n";
		return false;
	}
	m_set_states();
	if(FAILED(get_video().get_direct3ddevice9().EndStateBlock(&m_block_p))) {
		std::cerr << "ERROR: Can't create state block\n";
		return false;
	}
#	endif
	return super::create();
}
bool rstates::set() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
#	if defined(XBOX)
	m_set_states();
#	elif defined(WIN32)
	if(FAILED(m_block_p->Apply())) {
		std::cerr << "ERROR: Can't apply state block\n";
		return false;
	}
#	endif
	return true;
}
void rstates::destroy() {
	thread::locker l_locker(section());
#	if defined(WIN32)
	if(m_block_p != 0) {
		m_block_p->Release();
		m_block_p = 0;
	}
#	endif
	super::destroy();
}
bool rstates::m_set_states() {
	const info &l_info = get_info();
	for(uint i = 0, s = l_info.states.size(); i < s; ++i) {
		const state &l_state = l_info.states[i];
		if(l_state.index == bad_ID) {
			get_video().get_direct3ddevice9().SetRenderState((D3DRENDERSTATETYPE)l_state.name, l_state.value);
		} else {
			get_video().get_direct3ddevice9().SetSamplerState(l_state.index, (D3DSAMPLERSTATETYPE)l_state.name, l_state.value);
		}
	}
	return true;
}

// vshader::info

vshader::info::info() :
	video::resource::info(video::rt::vshader), function(0)
{}

// vshader

vshader::vshader(const info &_info, video &_video) :
	video::resource(_info, _video),
	m_shader_p(0)
{}
vshader::~vshader() {
	destroy();
}
bool vshader::create() {
	destroy();
	thread::locker l_locker(section());
	if(!get_video().ready()) return false;
	assert(get_info().function != 0);
	if(FAILED(get_video().get_direct3ddevice9().CreateVertexShader((const DWORD*)get_info().function, &m_shader_p))) {
		std::cerr << "ERROR: Can't create vertex shader\n";
		return false;
	}
	return super::create();
}
bool vshader::set() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetVertexShader(m_shader_p))) {
		std::cerr << "ERROR: Can't set vertex shader\n";
		return false;
	}
	return true;
}
void vshader::destroy() {
	thread::locker l_locker(section());
	if(m_shader_p != 0) {
		m_shader_p->Release();
		m_shader_p = 0;
	}
	super::destroy();
}

// pshader::info

pshader::info::info() :
	video::resource::info(video::rt::pshader), function(0)
{}

// pshader

pshader::pshader(const info &_info, video &_video) :
	video::resource(_info, _video),
	m_shader_p(0)
{}
pshader::~pshader() {
	destroy();
}
bool pshader::create() {
	destroy();
	thread::locker l_locker(section());
	if(!get_video().ready()) return false;
	assert(get_info().function != 0);
	if(FAILED(get_video().get_direct3ddevice9().CreatePixelShader((const DWORD*)get_info().function, &m_shader_p))) {
		std::cerr << "ERROR: Can't create pixel shader\n";
		return false;
	}
	return super::create();
}
bool pshader::set() {
	thread::locker l_locker(section());
	if(!get_video().ready() || !valid()) return false;
	if(FAILED(get_video().get_direct3ddevice9().SetPixelShader(m_shader_p))) {
		std::cerr << "ERROR: Can't set pixel shader\n";
		return false;
	}
	return true;
}
void pshader::destroy() {
	thread::locker l_locker(section());
	if(m_shader_p != 0) {
		m_shader_p->Release();
		m_shader_p = 0;
	}
	super::destroy();
}
*/

} /* video resources ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
