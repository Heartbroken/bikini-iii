/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct video {
	video();
	~video();

	bool create();
	bool update(real _dt);
	void destroy();

	inline bool ready() const { return m_fsm.state_is(m_ready); }
	inline bool failed() const { return m_fsm.state_is(m_failed); }
	inline bool lost() const { return m_fsm.state_is(m_lost); }

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