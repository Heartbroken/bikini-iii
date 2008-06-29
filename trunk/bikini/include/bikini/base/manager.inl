/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _Type>
inline _Type& manager::get(uint _ID) const {
	return static_cast<_Type&>(get(_ID));
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this)); return l_o.ID();
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info, typename _Info::a0 _a0) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this), _a0); return l_o.ID();
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this), _a0, _a1); return l_o.ID();
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this), _a0, _a1, _a2); return l_o.ID();
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this), _a0, _a1, _a2, _a3); return l_o.ID();
}
template<typename _Info>
inline uint manager::spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3, typename _Info::a4 _a4) {
	_Info::object &l_o = * new _Info::object(_info, static_cast<typename _Info::manager&>(*this), _a0, _a1, _a2, _a3, _a4); return l_o.ID();
}

