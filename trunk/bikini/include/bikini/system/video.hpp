/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct video : device {
	struct rt { enum resource_type {
		screen, vbuffer, ibuffer, texture
	};};

	struct resource : device::resource {
		struct info : device::resource::info {
			typedef video manager;
			info(uint _type);
		};
		resource(const info &_info, video &_video);
		inline video& get_video() const { return static_cast<video&>(get_device()); }
	};

	video();
	~video();

	bool create(bool _multithreaded = false);
	bool update(real _dt);
	void destroy();

	inline bool ready() const { return m_fsm.state_is(m_ready); }
	inline bool failed() const { return m_fsm.state_is(m_failed); }
	inline bool lost() const { return m_fsm.state_is(m_lost); }

	inline IDirect3DDevice9& get_direct3ddevice9() const { return *m_direct3ddevice9_p; }

private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	typedef fsm_<video> fsm; fsm m_fsm;
	fsm::state m_void; void m_void_b(); void m_void_u(real _dt); void m_void_e();
	fsm::state m_ready; void m_ready_b(); void m_ready_u(real _dt); void m_ready_e();
	fsm::state m_failed; void m_failed_b(); void m_failed_u(real _dt); void m_failed_e();
	fsm::state m_lost; void m_lost_b(); void m_lost_u(real _dt); void m_lost_e();
};

namespace cf { enum clear_flags {
	color = 1<<0,
	depth = 1<<1,
	stencil = 1<<2,
	all = color|depth|stencil,
};}

namespace vr { /* video resources ---------------------------------------------------------------*/

struct screen : video::resource {
	struct info : video::resource::info {
		typedef screen object;
#if defined(WIN32)
		typedef HWND a0;
		typedef bool a1;
		typedef uint a2;
		typedef uint a3;
#endif
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
#if defined(XBOX)
	screen(const info &_info, video &_video);
#elif defined(WIN32)
	screen(const info &_info, video &_video, HWND _window, bool _fullscreen, uint _width, uint _height);
	inline bool fullscreen() const { return m_fullscreen; }
	inline void set_fullscreen(bool _yes = true) { m_fullscreen = _yes; }
	inline uint width() const { return m_width; }
	inline uint height() const { return m_height; }
	inline void set_size(uint _w, uint _h) { m_width = _w; m_height = _h; }
	inline bool active() const { return sm_activescreen_p == this; }
#endif
	bool create();
	void destroy();
	bool begin();
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0);
	bool end();
	bool present();
private:
#if defined(WIN32)
	HWND m_window; bool m_fullscreen; uint m_width, m_height;
	IDirect3DSwapChain9 *m_backbuffer_p;
	IDirect3DSurface9 *m_depthstencil_p;
#endif
	thread::section m_lock;
	static screen *sm_activescreen_p;
};

} /* video resources ----------------------------------------------------------------------------*/