/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _T>
inline _T& manager::get(uint _ID) const {
	return static_cast<_T&>(get(_ID));
}
template<typename _I>
inline uint manager::spawn(const _I &_info) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this));
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I &_info, typename _I::a0 _a0) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this), _a0);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this), _a0, _a1);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this), _a0, _a1, _a2);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this), _a0, _a1, _a2, _a3);
	return l_o.ID();
}
template<typename _I>
inline uint manager::spawn(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3, typename _I::a4 _a4) {
	_I::object &l_o = * new _I::object(_info, static_cast<typename _I::manager&>(*this), _a0, _a1, _a2, _a3, _a4);
	return l_o.ID();
}
template<typename _I>
inline uint manager::m_find_shared(const _I &_info) {
	for(uint i = 0, s = m_shared.size(); i < s; ++i) {
		uint l_ID = m_shared[i];
		if(!exists(l_ID)) continue;
		const object::info &l_info = get(l_ID).get_info();
		if(l_info.type() != _info.type()) continue;
		if(static_cast<const _I&>(l_info) == _info) return l_ID;
	}
	return bad_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info, typename _I::a0 _a0) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2, _a3);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}
template<typename _I>
inline uint manager::spawn_shared(const _I &_info, typename _I::a0 _a0, typename _I::a1 _a1, typename _I::a2 _a2, typename _I::a3 _a3, typename _I::a4 _a4) {
	uint l_ID = m_find_shared(_info);
	if(l_ID == bad_ID) l_ID = spawn(_info, _a0, _a1, _a2, _a3, _a4);
	get(l_ID).add_ref(); m_shared.push_back(l_ID);
	return l_ID;
}

