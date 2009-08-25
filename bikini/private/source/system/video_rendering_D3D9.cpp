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

// _video_rendering_helper

struct _video_rendering_helper
{
	static HWND create_dummy_window()
	{
		HINSTANCE l_instance = GetModuleHandle(0);
		wchar_t* l_window_class_name = L"bikini-iii video dummy window";
		WNDCLASSW l_window_class = { 0, DefWindowProcW, 0, 0, l_instance, 0, 0, 0, 0, l_window_class_name };
		RegisterClassW(&l_window_class);
		HWND l_handle = CreateWindowExW(0, l_window_class_name, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 10, 10, 0, 0, l_instance, 0);
		if(l_handle == 0) std::cerr << "ERROR: Can't create dummy window\n";
		return l_handle;
	}
};

// rendering_D3D9

struct rendering_D3D9 : video::rendering
{
	rendering_D3D9(video &_video);
	~rendering_D3D9();
	bool create();
	void destroy();
	bool execute(const command &_command);
private:
	//
	static IDirect3D9 *sm_D3D9_p;
	IDirect3DDevice9 *m_D3DDevice9_p;
	D3DPRESENT_PARAMETERS m_D3DPP;
	//
	bool execute(const create_schain &_command);
	bool execute(const destroy_resource &_command);
	bool execute(const begin_scene &_command);
	bool execute(const end_scene &_command);
	//
	struct schain {};
	struct vbuffer {};
	struct ibuffer {};
	struct vformat {};
	struct texture {};
	struct vshader {};
	struct pshader {};
	struct consts {};
	struct ststes {};
	struct viewport {};
	struct rtarget {};
	struct material {};
	struct primitive {};
};

IDirect3D9 *rendering_D3D9::sm_D3D9_p = 0;

rendering_D3D9::rendering_D3D9(video &_video)
:
	video::rendering(_video),
	m_D3DDevice9_p(0)
{}
rendering_D3D9::~rendering_D3D9()
{
}
bool rendering_D3D9::create()
{
	if (sm_D3D9_p == 0)
	{
		sm_D3D9_p = Direct3DCreate9(D3D_SDK_VERSION);
		if(sm_D3D9_p == 0) {
			std::cerr << "ERROR: Can't create Direct3D object.\n";
			return false;
		}
	}
	else
	{
		sm_D3D9_p->AddRef();
	}

	memset(&m_D3DPP, 0, sizeof(m_D3DPP));
	m_D3DPP.hDeviceWindow = _video_rendering_helper::create_dummy_window();
	m_D3DPP.Windowed = true;
	m_D3DPP.BackBufferWidth = 10;
	m_D3DPP.BackBufferHeight = 10;
	m_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_D3DPP.FullScreen_RefreshRateInHz = 0;
    m_D3DPP.EnableAutoDepthStencil = false;
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	DWORD l_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE|D3DCREATE_PUREDEVICE/*|D3DCREATE_MULTITHREADED*/;
	if(FAILED(sm_D3D9_p->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_D3DPP.hDeviceWindow,
		l_flags,
		&m_D3DPP,
		&m_D3DDevice9_p
	))) {
		std::cerr << "ERROR: Can't create D3D device\n";
		return false;
	}
	
	return super::create();
}
void rendering_D3D9::destroy()
{
	if (m_D3DDevice9_p && m_D3DDevice9_p->Release() == 0) m_D3DDevice9_p = 0;
	if (sm_D3D9_p && sm_D3D9_p->Release() == 0) sm_D3D9_p = 0;

	super::destroy();
}
bool rendering_D3D9::execute(const command &_command)
{
	switch (_command.type())
	{
		case command_types::type_<create_schain>::index : return execute(_command.get_<create_schain>());
		case command_types::type_<destroy_resource>::index : return execute(_command.get_<destroy_resource>());
		case command_types::type_<begin_scene>::index : return execute(_command.get_<begin_scene>());
		case command_types::type_<end_scene>::index : return execute(_command.get_<end_scene>());
	}
	return false;
}
bool rendering_D3D9::execute(const create_schain &_command)
{
	return true;
}
bool rendering_D3D9::execute(const destroy_resource &_command)
{
	return true;
}
bool rendering_D3D9::execute(const begin_scene &_command)
{
	return true;
}
bool rendering_D3D9::execute(const end_scene &_command)
{
	return true;
}

// video

video::rendering& video::new_rendering(video &_video)
{
	return * new rendering_D3D9(_video);
}


} /* namespace bk -------------------------------------------------------------------------------*/
