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

// video::rendering

struct rendering_D3D9 : video::rendering
{
	rendering_D3D9(video &_video);
	~rendering_D3D9();
	bool create();
	void destroy();
	bool command(const rendering_command &_command);
private:
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

rendering_D3D9::rendering_D3D9(video &_video)
:
	video::rendering(_video)
{}
rendering_D3D9::~rendering_D3D9()
{
}
bool rendering_D3D9::create()
{
	return super::create();
}
void rendering_D3D9::destroy()
{
	super::destroy();
}
bool rendering_D3D9::command(const rendering_command &_command)
{
	return true;
}

// video

video::rendering& video::new_rendering(video &_video)
{
	return * new rendering_D3D9(_video);
}


} /* namespace bk -------------------------------------------------------------------------------*/
