/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///
struct video {
	//
	struct resource : render::resource<video> {
		inline resource(video &_video) : render::resource<video>(_video) {}
		inline video& get_video() const { return get_owner(); }
	};

	inline IDirect3DDevice9& get_device() const { return *m_direct3ddevice9_p; }

	video();
	~video();

	bool create();
	void destroy();
	bool activate(HWND _window);
	bool reset();

	bool begin_scene();
	bool end_scene();
	bool present();
	bool clear_viewport(/*uint _flags = cf::target|cf::zbuffer, const rgba &_color = black, real _depth = 1.f, uint _stencil = 0*/);

private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
};