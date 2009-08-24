/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct video : device {
	
	/* video object -----------------------------------------------------------------------------*/

	struct object : device::object
	{
		struct info : device::object::info
		{
			typedef video manager;
			info(uint _type);
		};
		inline video& get_video() const { return static_cast<video&>(get_device()); }
		object(const info &_info, video &_video);
	protected:
		template<typename _Command> inline void add_command(const _Command &_command) { get_video().add_command(_command); }
		inline uint obtain_resource_ID() const { return get_video().obtain_resource_ID(); }
		inline void release_resource_ID(uint _ID) const { get_video().release_resource_ID(_ID); }
		inline bool resource_exists(uint _ID) const { return get_video().resource_exists(_ID); }
		inline bool resource_valid(uint _ID) const { return get_video().resource_valid(_ID); }
		inline void set_resource_valid(uint _ID) const { get_video().set_resource_valid(_ID); }
	};

	struct ot { enum object_type {
		window, screen, vbuffer, vformat, rstates, vshader, pshader, ibuffer, texture
	};};

	/* rendering interface ----------------------------------------------------------------------*/

	struct rendering
	{
		/* rendering commands -------------------------------------------------------------------*/

		struct rc { enum rendering_command {
			create_resource, destroy_resource, begin_scene, draw_primitive, end_scene, present_schain, last_command
		};};

		struct rr { enum rendering_resource {
			schain, vbuffer, ibuffer, vformat, texture, vshader, pshader, consts, states, viewport, rtarget, material, primitive
		};};

		struct rendering_command {
			rc::rendering_command command; uint size;
		protected:
			inline rendering_command(rc::rendering_command _command, uint _size) : command(_command), size(_size) {}
		};
		struct create_resource : rendering_command {
			rr::rendering_resource resource; uint ID;
		protected:
			inline create_resource(rr::rendering_resource _resource, uint _size) : rendering_command(rc::create_resource, _size), resource(_resource), ID(bad_ID) {}
		};
		struct destroy_resource : rendering_command {
			uint ID;
			inline destroy_resource() : rendering_command(rc::destroy_resource, sizeof(destroy_resource)), ID(bad_ID) {}
		};
		struct begin_scene : rendering_command {
			inline begin_scene() : rendering_command(rc::begin_scene, sizeof(begin_scene)) {}
		};
		struct draw_primitive : rendering_command {
			inline draw_primitive() : rendering_command(rc::draw_primitive, sizeof(draw_primitive)) {}
		};
		struct end_scene : rendering_command {
			inline end_scene() : rendering_command(rc::end_scene, sizeof(end_scene)) {}
		};
		struct present_schain : rendering_command {
			inline present_schain() : rendering_command(rc::present_schain, sizeof(present_schain)) {}
		};
		struct last_command : rendering_command {
			inline last_command() : rendering_command(rc::last_command, sizeof(last_command)) {}
		};
		struct create_schain : create_resource {
			handle window;
			inline create_schain() : create_resource(rr::schain, sizeof(create_schain)), window(0) {}
		};

		/* rendering commands -------------------------------------------------------------------*/

		rendering(video &_video);
		virtual ~rendering();
		virtual bool create();
		virtual void destroy();
		virtual bool command(const rendering_command &_command) = 0;

	private:
		friend video;
		video &m_video;
		thread::task m_task;
		bool m_run;
		void m_proc();
		static const uint max_cbuffer_count = 2;
		byte_array m_cbuffer[max_cbuffer_count];
		uint m_current_cbuffer;
		void swap_cbuffer(byte_array &_cbuffer);
		void process_cbuffer(const byte_array &_cbuffer);
		thread::flag m_cbuffer_ready;
		thread::section m_cbuffer_lock;
	};

	video();
	~video();

	bool create();
	bool update(real _dt);
	void destroy();

	//inline bool ready() const { return m_fsm.state_is(m_ready); }
	//inline bool failed() const { return m_fsm.state_is(m_failed); }
	//inline bool lost() const { return m_fsm.state_is(m_lost); }

	//inline uint screen_ID() const { return m_screen_ID; }
	//inline void set_screen_ID(uint _ID) { m_screen_ID = _ID; }
	//inline uint vbuffer_ID() const { return m_vbuffer_ID; }
	//inline void set_vbuffer_ID(uint _ID) { m_vbuffer_ID = _ID; }

	//inline IDirect3DDevice9& get_direct3ddevice9() const { return *m_direct3ddevice9_p; }
	//inline HWND get_focus_window() const { return m_d3dpresent_parameters.hDeviceWindow; }

private:
	rendering &m_rendering;
	rendering& new_rendering(video &_video);
	inline rendering& get_rendering() const { return m_rendering; }
	//
	byte_array m_cbuffer;
	template<typename _Command> inline void add_command(const _Command &_command) { m_cbuffer.insert(m_cbuffer.end(), (byte*)&_command, (byte*)&_command + sizeof(_command)); }
	//
	struct resource { bool valid; };
	pool_<resource> m_resources;
	uint obtain_resource_ID();
	void release_resource_ID(uint _ID);
	bool resource_exists(uint _ID);
	bool resource_valid(uint _ID);
	void set_resource_valid(uint _ID);

	//static IDirect3D9 *sm_direct3d9_p;
	//IDirect3DDevice9 *m_direct3ddevice9_p;
	//D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	//uint m_screen_ID, m_vbuffer_ID;
	//typedef fsm_<video> fsm; fsm m_fsm;
	//fsm::state m_void; void m_void_b(); void m_void_u(real _dt); void m_void_e();
	//fsm::state m_ready; void m_ready_b(); void m_ready_u(real _dt); void m_ready_e();
	//fsm::state m_failed; void m_failed_b(); void m_failed_u(real _dt); void m_failed_e();
	//fsm::state m_lost; void m_lost_b(); void m_lost_u(real _dt); void m_lost_e();
};

namespace cf { enum clear_flags {
	color = 1<<0,
	depth = 1<<1,
	stencil = 1<<2,
	all = color|depth|stencil,
};}

namespace vr { /* video objects -----------------------------------------------------------------*/

/// window
struct window : video::object {
	struct info : video::object::info {
		typedef window object;
		typedef HWND a0;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	window(const info &_info, video &_video, HWND _window);
	~window();
	//bool create();
	bool update(real _dt);
	//void destroy();
private:
	HWND m_window;
	uint m_schain_resource_ID;
	//IDirect3DSwapChain9 *m_backbuffer_p;
	//IDirect3DSurface9 *m_depthstencil_p;
	static long _stdcall _wndproc(HWND _window, uint _message, uint _wparam, uint _lparam);
	long m_wndproc(uint _message, uint _wparam, uint _lparam);
	WNDPROC m_oldwndproc;
	LONG m_oldusrdata;
	//sint2 m_size;
};
/*
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
	~screen();
	bool create();
	void destroy();
	bool begin();
	bool clear(uint _flags = cf::all, const color &_color = black, real _depth = 1.f, uint _stencil = 0);
	bool set_scissor(uint _x0, uint _y0, uint _x1, uint _y1);
	bool remove_scissor();
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
		array_<desc> descs;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	inline bool active() const { return get_video().vbuffer_ID() == ID(); }
	vbuffer(const info &_info, video &_video);
	~vbuffer();
	bool create();
	handle lock(uint _index = 0);
	bool unlock(uint _index = 0);
	bool begin(uint _offset = bad_ID, uint _stride = bad_ID);
	bool end();
	void destroy();
private:
	array_<IDirect3DVertexBuffer9*> m_buffers;
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
		array_<element> format;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	vformat(const info &_info, video &_video);
	~vformat();
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
		array_<state> states;
		info();
	};
	inline const info& get_info() const { return static_cast<const info&>(super::get_info()); }
	rstates(const info &_info, video &_video);
	~rstates();
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
	~vshader();
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
	~pshader();
	bool create();
	bool set();
	void destroy();
private:
	IDirect3DPixelShader9 *m_shader_p;
};
*/
} /* video resources ----------------------------------------------------------------------------*/