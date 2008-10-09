/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _variant_helper_
template<typename _L, bool _D>
struct _variant_helper_ {
	static inline void construct(handle &_h, uint _t, pointer _v) { _h = _L::construct(_t, _v); }
	static inline void destruct(handle &_h, uint _t) { _L::destruct(_h, _t, true); }
};
template<typename _L>
struct _variant_helper_<_L, false> {
	static inline void construct(handle &_h, uint _t, pointer _v) { _L::construct(_h, _t, _v); }
	static inline void destruct(handle &_h, uint _t) { _L::destruct(_h, _t, false); }
};

template<typename _L, bool _D>
inline variant_<_L, _D>::variant_() : m_type(bad_ID)
{}
template<typename _L, bool _D>
inline variant_<_L, _D>::variant_(const variant_ &_v) {
	construct(_v.type(), _v.data());
}
template<typename _L, bool _D> template<typename _T>
inline variant_<_L, _D>::variant_(const _T &_v) {
	c_assert(_L::type<_T>::exists);
	construct(_L::type<_T>::index, &_v);
}
template<typename _L, bool _D> template<typename _O>
inline variant_<_L, _D>::variant_(const variant_<_O> &_v) {
	construct(_L::otherlist<_O>::remap(_v.type()), _v.data());
}
template<typename _L, bool _D>
inline variant_<_L, _D>::~variant_() {
	destruct();
}
template<typename _L, bool _D>
inline uint variant_<_L, _D>::type() const {
	return m_type;
}
template<typename _L, bool _D>
inline pointer variant_<_L, _D>::data() const {
	return m_data;
}
template<typename _L, bool _D>
inline void variant_<_L, _D>::construct(u32 _type, pointer _data) {
	assert(_type < _L::count);
	destruct();
	m_type = _type;
	_variant_helper_<_L, _D>::construct(m_data, _type, _data);
}
template<typename _L, bool _D>
inline void variant_<_L, _D>::destruct() {
	if(m_type == bad_ID) return;
	_variant_helper_<_L, _D>::destruct(m_data, m_type);
	m_type = bad_ID;
}
template<typename _L, bool _D>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const variant_ &_v) {
	construct(_v.type(), _v.data());
	return *this;
}
template<typename _L, bool _D> template<typename _T>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const _T &_v) {
	c_assert(_L::type<_T>::exists);
	construct(_L::type<_T>::index, &_v);
	return *this;
}
template<typename _L, bool _D> template<typename _O>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const variant_<_O> &_v) {
	construct(_L::otherlist<_O>::remap(_v.type()), _v.data());
	return *this;
}
