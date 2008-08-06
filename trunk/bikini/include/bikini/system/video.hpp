/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct video : device {
	struct rt { enum resource_type {
		screen, vbuffer, vformat, rstates, vshader, pshader, ibuffer, texture
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
	inline uint vbuffer_ID() const { return m_vbuffer_ID; }
	inline void set_vbuffer_ID(uint _ID) { m_vbuffer_ID = _ID; }

	inline IDirect3DDevice9& get_direct3ddevice9() const { return *m_direct3ddevice9_p; }

private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	uint m_screen_ID, m_vbuffer_ID;
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
	inline bool active() const { return get_video().screen_ID() == ID(); }
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
	struct desc {
		uint size; uint stride; bool dynamic;
		inline desc(uint _size, uint _stride = 0, bool _dynamic = false) : size(_size), stride(_stride), dynamic(_dynamic) {}
		inline desc(const desc &_d) : size(_d.size), stride(_d.stride), dynamic(_d.dynamic) {}
		inline desc& operator = (const desc &_d) { this->~desc(); new(this) desc(_d); return *this; }
	};
	struct info : video::resource::info {
		typedef vbuffer object;
		std::vector<desc> descs;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	inline bool active() const { return get_video().vbuffer_ID() == ID(); }
	vbuffer(const info &_info, video &_video);
	bool create();
	handle lock(uint _index = 0, uint _offset = 0, uint _size = 0, bool _discard = false);
	bool unlock(uint _index = 0);
	bool begin(uint _offset = bad_ID, uint _stride = bad_ID);
	bool end();
	void destroy();
private:
	std::vector<IDirect3DVertexBuffer9*> m_buffers;
};

/// vformat
struct vformat : video::resource {
	struct element {
#		if defined(XBOX)
		u16 stream, offset; u32 type; u8 method, usage, uindex;
		inline element(u16 _stream, u16 _offset, u32 _type, u8 _method, u8 _usage, u8 _uindex) : stream(_stream), offset(_offset), type(_type), method(_method), usage(_usage), uindex(_uindex) {}
#		elif defined(WIN32)
		u16 stream, offset; u8 type, method, usage, uindex;
		inline element(u16 _stream, u16 _offset, u8 _type, u8 _method, u8 _usage, u8 _uindex) : stream(_stream), offset(_offset), type(_type), method(_method), usage(_usage), uindex(_uindex) {}
#		endif
		inline element(const element &_e) : stream(_e.stream), offset(_e.offset), type(_e.type), method(_e.method), usage(_e.usage), uindex(_e.uindex) {}
		inline element& operator = (const element &_e) { this->~element(); new(this) element(_e); return *this; }
	};
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

/// rstates
struct rstates : video::resource {
	struct state {
		uint index, name, value;
		inline state(uint _index, uint _name, uint _value) : index(_index), name(_name), value(_value) {}
		inline state(uint _name, uint _value) : index(bad_ID), name(_name), value(_value) {}
	};
	struct info : video::resource::info {
		typedef rstates object;
		std::vector<state> states;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	rstates(const info &_info, video &_video);
	bool create();
	bool set();
	void destroy();
private:
	IDirect3DStateBlock9 *m_block_p;
	bool m_set_states();
};

/// vshader
struct vshader : video::resource {
	struct info : video::resource::info {
		typedef vshader object;
		pointer function;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	vshader(const info &_info, video &_video);
	bool create();
	bool set();
	void destroy();
private:
	IDirect3DVertexShader9 *m_shader_p;
};

/// pshader
struct pshader : video::resource {
	struct info : video::resource::info {
		typedef pshader object;
		pointer function;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	pshader(const info &_info, video &_video);
	bool create();
	bool set();
	void destroy();
private:
	IDirect3DPixelShader9 *m_shader_p;
};

} /* video resources ----------------------------------------------------------------------------*/