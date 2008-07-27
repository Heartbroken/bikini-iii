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

	bool create();
	bool update(real _dt);
	void destroy();

	inline bool ready() const { return m_fsm.state_is(m_ready); }
	inline bool failed() const { return m_fsm.state_is(m_failed); }
	inline bool lost() const { return m_fsm.state_is(m_lost); }

	inline IDirect3DDevice9& get_direct3ddevice9() const { return *m_direct3ddevice9_p; }

	inline void lock() { m_section.enter(); }
	inline void unlock() { m_section.leave(); }

private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	thread::section m_section;
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
		HWND window; bool fullscreen; uint width, height;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	screen(const info &_info, video &_video);
	bool create();
	void destroy();
	bool begin();
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0);
	bool end();
	bool present();
private:
	IDirect3DSwapChain9 *m_swapchain_p;
	IDirect3DSurface9 *m_depthstencil_p;
	static screen *sm_activescreen_p;
	//bool m_is_current() const;
	//bool m_set_current() const;
};

//struct dbuffer : video::resource {
//	struct info : video::resource::info {
//		typedef dbuffer object;
//		uint width, height;
//		info();
//	};
//	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
//	dbuffer(const info &_info, video &_video);
//	bool create();
//	void destroy();
//	bool set();
//private:
//	IDirect3DSurface9 *m_direct3dsurface9_p;
//};

} /* video resources ----------------------------------------------------------------------------*/