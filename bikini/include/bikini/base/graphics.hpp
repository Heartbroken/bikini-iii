/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct graphics {
	graphics() :
		m_void(&graphics::m_void_b, &graphics::m_void_u, &graphics::m_void_e),
		m_fsm(*this, m_void)
	{}
private:
	static IDirect3D9 *sm_direct3d9_p;
	IDirect3DDevice9 *m_direct3ddevice9_p;
	D3DPRESENT_PARAMETERS m_d3dpresent_parameters;
	typedef fsm_<graphics> fsm; fsm m_fsm;
	fsm::state m_void; void m_void_b(){} void m_void_u(real _dt){} void m_void_e(){}
};