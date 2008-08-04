/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct video : device {
	struct rt { enum resource_type {
		screen, vbuffer, ibuffer, texture, vformat, vshader, pshader
	};};

	struct resource : device::resource {
		struct info : device::resource::info {
			typedef video manager;
			info(uint _type);
		};
		resource(const info &_info, video &_video);
		inline video& get_video() const { return static_cast<video&>(get_device()); }
	protected:
		inline thread::section& section() { return m_section; }
	private:
		thread::section m_section;
	};

	video();
	~video();

	bool create(bool _multithreaded = false);
	bool update(real _dt);
	void destroy();

	inline bool ready() const { return m_fsm.state_is(m_ready); }
	inline bool failed() const { return m_fsm.state_is(m_failed); }
	inline bool lost() const { return m_fsm.state_is(m_lost); }

	inline uint screen_ID() const { return m_screen_ID; }
	inline void set_screen_ID(uint _ID) { m_screen_ID = _ID; }
	inline uint vbuffer_count() const { return sm_vbuffer_count; }
	inline uint vbuffer_ID(uint _i) const { assert(_i < sm_vbuffer_count); return m_vbuffer_ID[_i]; }
	inline void set_vbuffer_ID(uint _i, uint _ID) { assert(_i < sm_vbuffer_count); m_vbuffer_ID[_i] = _ID; }

	inline IDirect3DDevice9& get_direct3ddevice9() const { return *m_direct3ddevice9_p; }

private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	uint m_screen_ID;
	static const uint sm_vbuffer_count = 32; uint m_vbuffer_ID[sm_vbuffer_count];
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

/// screen
struct screen : video::resource {
	struct info : video::resource::info {
		typedef screen object;
#		if defined(WIN32)
		typedef HWND a0;
		typedef bool a1;
		typedef uint a2;
		typedef uint a3;
#		endif
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
#	if defined(XBOX)
	screen(const info &_info, video &_video);
#	elif defined(WIN32)
	screen(const info &_info, video &_video, HWND _window, bool _fullscreen, uint _width, uint _height);
	inline bool fullscreen() const { return m_fullscreen; }
	inline void set_fullscreen(bool _yes = true) { m_fullscreen = _yes; }
	inline uint width() const { return m_width; }
	inline uint height() const { return m_height; }
	inline void set_size(uint _w, uint _h) { m_width = _w; m_height = _h; }
#	endif
	inline bool active() const { return get_video().screen_ID() == ID(); }
	bool create();
	void destroy();
	bool begin();
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0);
	bool draw_primitive(uint _start, uint _count);
	bool end();
	bool present();
private:
#	if defined(WIN32)
	HWND m_window; bool m_fullscreen; uint m_width, m_height;
	IDirect3DSwapChain9 *m_backbuffer_p;
	IDirect3DSurface9 *m_depthstencil_p;
#	endif
};

/// vbuffer
struct vbuffer : video::resource {
	struct info : video::resource::info {
		typedef vbuffer object;
		typedef uint a0;
		typedef bool a1;
		typedef pointer a2;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	vbuffer(const info &_info, video &_video, uint _size, bool _dynamic);
	inline uint size() const { return m_size; }
	inline bool dynamic() const { return m_dynamic; }
	inline uint offset() const { return m_offset; }
	inline void set_offset(uint _offset) { m_offset = _offset; }
	inline uint stride() const { return m_stride; }
	inline void set_stride(uint _stride) { m_stride = _stride; }
	inline bool active() const { return m_index < get_video().vbuffer_count() && get_video().vbuffer_ID(m_index) == ID(); }
	bool create();
	handle lock(uint _offset = 0, uint _size = 0, bool _discard = false);
	bool unlock();
	bool begin(uint _index, uint _offset = bad_ID, uint _stride = bad_ID);
	bool end();
	void destroy();
private:
	uint m_size; bool m_dynamic;
	uint m_index, m_offset, m_stride;
	IDirect3DVertexBuffer9 *m_buffer_p;
};

/// vformat
struct vformat : video::resource {
	typedef D3DVERTEXELEMENT9 element;
	static const element end;
	struct info : video::resource::info {
		typedef vformat object;
		std::vector<element> format;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	vformat(const info &_info, video &_video);
	bool create();
	bool set();
	void destroy();
private:
	IDirect3DVertexDeclaration9 *m_format_p;
};

} /* video resources ----------------------------------------------------------------------------*/