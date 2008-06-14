/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// functions
inline real bk::sqrt(real _a) {
	return ::sqrt(_a);
}
inline real bk::rsqrt(real _a) {
	return 1.f / sqrt(_a);
}
inline real bk::abs(real _a) {
	return ::abs(_a);
}
inline real bk::sin(real _a) {
	return ::sin(_a);
}
inline real bk::cos(real _a) {
	return ::cos(_a);
}
inline real bk::asin(real _a) {
	return ::asin(_a);
}
inline real bk::acos(real _a) {
	return ::acos(_a);
}
inline real bk::tan(real _a) {
	return ::tan(_a);
}
inline real bk::cot(real _a) {
	return 1.f / tan(_a);
}
inline void bk::sincos(real _a, real &_s, real &_c) {
	_s = sin(_a); _c = cos(_a);
}
inline real bk::d2r(real _d) {
	return _d * real(0.017453);
}
inline real bk::r2d(real _r) {
	return _r * real(57.29578);
}
inline real bk::pow(real _a, real _b) {
	return ::pow(_a, _b);
}
inline bool is_tiny(real _a) {
	return (_a > -eps && _a < eps);
}
inline uint next_pow2(uint _a) {
	uint l_a = _a; l_a |= l_a>>1; l_a |= l_a>>2; l_a |= l_a>>4; l_a |= l_a>>8; l_a |= l_a>>16;
	return (_a&(l_a>>1)) ? l_a + 1 : _a;
}
inline real random() {
	return (real)rand() / (real)RAND_MAX;
}
inline real random(real _max) {
	return _max * random();
}
inline real random(real _min, real _max) {
	return _min + random(_max - _min);
}
template<typename _T> inline const _T& min(const _T &_a, const _T &_b) {
	return _a <= _b ? _a : _b;
}
template<typename _T> inline const _T& max(const _T &_a, const _T &_b) {
	return _a >= _b ? _a : _b;
}
template<typename _T> inline const _T& clamp(const _T &_a, const _T &_min, const _T &_max) {
	return (_a < _min ? _min : (_a > _max ? _max : _a));
}
template<typename _T> inline _T wrap(const _T &_a, const _T &_min, const _T &_max) {
	return (_a < _min ? _max - (_min - _a) : (_a > _max ? _min + (_a - _max) : _a));
}
template<typename _T> inline void swap(_T &_a, _T &_b) {
	_T l_t = _a; _a = _b; _b = l_t;
}

// types

// _matrix_row_
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_() {
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(const _matrix_row_ &_r) : parent_type(_r), m_cell(_r.cell()) {
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(const parent_type &_r) : parent_type(_r) {
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0) : m_cell(_cell0) {
	c_assert(_S == 1);
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1) : parent_type(_cell0), m_cell(_cell1) {
	c_assert(_S == 2);
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1, _T _cell2) : parent_type(_cell0, _cell1), m_cell(_cell2) {
	c_assert(_S == 3);
}
template<uint _S, typename _T>
inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1, _T _cell2, _T _cell3) : parent_type(_cell0, _cell1, _cell2), m_cell(_cell3) {
	c_assert(_S == 4);
}
template<uint _S, typename _T>
inline const _T& _matrix_row_<_S, _T>::cell() const {
	return m_cell;
}
template<uint _S, typename _T>
inline _T& _matrix_row_<_S, _T>::cell() {
	return m_cell;
}
template<uint _S, typename _T> template<uint _I>
inline const _T& _matrix_row_<_S, _T>::cell() const {
	c_assert(_I < _S);
	return *(&static_cast<const _matrix_row_<_I + 1, _T>&>(*this).cell());
}
template<uint _S, typename _T> template<uint _I>
inline _T& _matrix_row_<_S, _T>::cell() {
	c_assert(_I < _S);
	return *(&static_cast<_matrix_row_<_I + 1, _T>&>(*this).cell());
}
template<uint _S, typename _T>
inline const _T& _matrix_row_<_S, _T>::operator [] (uint _i) const {
	assert(_i < _S);
	return *(&cell<0>() + _i);
}
template<uint _S, typename _T>
inline _T& _matrix_row_<_S, _T>::operator [] (uint _i) {
	assert(_i < _S);
	return *(&cell<0>() + _i);
}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>& _matrix_row_<_S, _T>::operator = (const _matrix_row_ &_r) {
//	parent_type::operator = (_r);
//	m_cell = _r.cell();
//	return *this;
//}
//template<uint _S, typename _T>
//inline const _matrix_row_<_S, _T> _matrix_row_<_S, _T>::operator - () const {
//	_matrix_row_ l_r;
//	neg(l_r);
//	return l_r;
//}
//template<uint _S, typename _T>
//inline const _matrix_row_<_S, _T> _matrix_row_<_S, _T>::operator + (const _matrix_row_ &_r) const {
//	_matrix_row_ l_r;
//	add(_r, l_r);
//	return l_r;
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>& _matrix_row_<_S, _T>::operator += (const _matrix_row_ &_r) {
//	add(_r, *this);
//	return *this;
//}
//template<uint _S, typename _T>
//inline const _matrix_row_<_S, _T> _matrix_row_<_S, _T>::operator - (const _matrix_row_ &_r) const {
//	_matrix_row_ l_r;
//	sub(_r, l_r);
//	return l_r;
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>& _matrix_row_<_S, _T>::operator -= (const _matrix_row_ &_r) {
//	sub(_r, *this);
//	return *this;
//}
//template<uint _S, typename _T>
//inline const _matrix_row_<_S, _T> _matrix_row_<_S, _T>::operator * (_T _s) const {
//	_matrix_row_ l_r;
//	mul(_s, l_r);
//	return l_r;
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>& _matrix_row_<_S, _T>::operator *= (_T _s) {
//	mul(_r, *this);
//	return *this;
//}
//template<uint _S, typename _T>
//inline const _matrix_row_<_S, _T> _matrix_row_<_S, _T>::operator / (_T _s) const {
//	_matrix_row_ l_r;
//	div(_s, l_r);
//	return l_r;
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>& _matrix_row_<_S, _T>::operator /= (_T _s) {
//	div(_r, *this);
//	return *this;
//}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::set(const _matrix_row_ &_b) {
	parent_type::set(_b); m_cell = _b.cell();
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::get(_matrix_row_ &_c) const {
	parent_type::get(_c); _c.cell() = m_cell;
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::neg(_matrix_row_ &_c) const {
	parent_type::neg(_c); _c.cell() = -m_cell;
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::add(const _matrix_row_ &_b, _matrix_row_ &_c) const {
	parent_type::add(_b, _c); _c.cell() = m_cell + _b.cell();
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::sub(const _matrix_row_ &_b, _matrix_row_ &_c) const {
	parent_type::sub(_b, _c); _c.cell() = m_cell - _b.cell();
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::mul(_T _s, _matrix_row_ &_c) const {
	parent_type::mul(_s, _c); _c.cell() = m_cell * _s;
}
template<uint _S, typename _T>
inline void _matrix_row_<_S, _T>::div(_T _s, _matrix_row_ &_c) const {
	parent_type::div(_s, _c); _c.cell() = m_cell + _s;
}

// matrix
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_() {
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(const matrix_ &_m) : parent_type(_m), m_row(_m.row()) {
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(const parent_type &_m) : parent_type(_m) {
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(_T _cell0) : m_row(_cell0) {
	c_assert(_H == 1 && _W == 1);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1) : m_row(_cell0, _cell1) {
	c_assert(_H == 1 && _W == 2);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1, _T _cell2) : m_row(_cell0, _cell1, _cell2) {
	c_assert(_H == 1 && _W == 3);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1, _T _cell2, _T _cell3) : m_row(_cell0, _cell1, _cell2, _cell3) {
	c_assert(_H == 1 && _W == 4);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1) : parent_type(_row0), m_row(_row1.row()) {
	c_assert(_H == 2);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2) : parent_type(_row0, _row1), m_row(_row2.row()) {
	c_assert(_H == 3);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2, const row_matrix &_row3) : parent_type(_row0, _row1, _row2), m_row(_row3.row()) {
	c_assert(_H == 4);
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() const {
	return m_row;
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() {
	return m_row;
}
template<uint _H, uint _W, typename _T> template<uint _I>
inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() const {
	c_assert(_I < _H);
	return static_cast<const matrix_<_I + 1, _W, _T>&>(*this).row();
}
template<uint _H, uint _W, typename _T> template<uint _I>
inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() {
	c_assert(_I < _H);
	return static_cast<matrix_<_I + 1, _W, _T>&>(*this).row();
}
template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
inline const _T& matrix_<_H, _W, _T>::cell() const {
	c_assert(_I < _H && _J < _W);
	return row<_I>().cell<_J>();
}
template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
inline _T& matrix_<_H, _W, _T>::cell() {
	c_assert(_I < _H && _J < _W);
	return row<_I>().cell<_J>();
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) const {
	assert(_i < _H && _i < _W);
	return *(&row<0>() + _i);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) {
	assert(_i < _H && _i < _W);
	return *(&row<0>() + _i);
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator = (const matrix_ &_m) {
	set(_m);
	return *this;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator - () const {
	matrix_ l_m;
	neg(l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator + (const matrix_ &_m) const {
	matrix_ l_m;
	add(_m, l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator += (const matrix_ &_m) {
	add(_m, *this);
	return *this;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator - (const matrix_ &_m) const {
	matrix_ l_m;
	sub(_m, l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator -= (const matrix_ &_m) {
	sub(_m, *this);
	return *this;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator * (_T _s) const {
	matrix_ l_m;
	mul(_s, l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator *= (_T _s) {
	mul(_s, *this);
	return *this;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator / (_T _s) const {
	matrix_ l_m;
	div(_s, l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator /= (_T _s) {
	div(_s, *this);
	return *this;
}
template<uint _H, uint _W, typename _T> template<uint _W2>
inline const matrix_<_H, _W2, _T> matrix_<_H, _W, _T>::operator * (const matrix_<_W, _W2, _T> &_m) const {
	matrix_<_H, _W2, _T> l_m;
	mul(_m, l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline const matrix_<_W, _H, _T> matrix_<_H, _W, _T>::operator ~ () const {
	matrix_<_W, _H, _T> l_m;
	xgt(l_m);
	return l_m;
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::set(const matrix_ &_b) {
	parent_type::set(_b); m_row.set(_b.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::get(matrix_ &_c) const {
	parent_type::get(_c); m_row.get(_c.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::neg(matrix_ &_c) const {
	parent_type::neg(_c); m_row.neg(_c.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::add(const matrix_ &_b, matrix_ &_c) const {
	parent_type::add(_b, _c); m_row.add(_b.row(), _c.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::sub(const matrix_ &_b, matrix_ &_c) const {
	parent_type::sub(_b, _c); m_row.sub(_b.row(), _c.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::mul(_T _s, matrix_ &_c) const {
	parent_type::mul(_s, _c); m_row.mul(_s, _c.row());
}
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::div(_T _s, matrix_ &_c) const {
	parent_type::div(_s, _c); m_row.div(_s, _c.row());
}
template<uint _H, uint _W, typename _T> template<uint _W2>
inline void matrix_<_H, _W, _T>::mul(const matrix_<_W, _W2, _T> &_b, matrix_<_H, _W2, _T> &_c) const {
	parent_type::mul(_b, _c);
	_b.mul(m_row, _c.row());
}
template<uint _H, uint _W, typename _T> struct _matrix_row_mul_helper_ { static inline void mul(const _matrix_row_<_W, _T> &_a, const _matrix_row_<_H, _T> &_b, _matrix_row_<_W, _T> &_c) {
	_matrix_row_<_W, _T> l_c; _a.mul(_b.cell(), l_c); l_c.add(_c, _c);
	//_c += _a * _b.cell();
}};
template<uint _W, typename _T> struct _matrix_row_mul_helper_<1, _W, _T> { static inline void mul(const _matrix_row_<_W, _T> &_a, const _matrix_row_<1, _T> &_b, _matrix_row_<_W, _T> &_c) {
	_a.mul(_b.cell(), _c);
	//_c = _a * _b.cell();
}};
template<uint _H, uint _W, typename _T>
inline void matrix_<_H, _W, _T>::mul(const _matrix_row_<_H, _T> &_b, _matrix_row_<_W, _T> &_c) const {
	parent_type::mul(_b, _c);
	_matrix_row_mul_helper_<_H, _W, _T>::mul(m_row, _b, _c);
}
template<uint _H, uint _W, typename _T> template<uint _W2> 
inline void matrix_<_H, _W, _T>::xgt(matrix_<_W, _W2, _T> &_b) const {
	parent_type::xgt(_b); _b.cst<_H - 1>(m_row);
}
template<uint _H, uint _W, typename _T> template<uint _I>
inline void matrix_<_H, _W, _T>::cst(const _matrix_row_<_H, _T> &_b) {
	parent_type::cst<_I>(_b); m_row.cell<_I>() = _b.cell();
}

// v2
template<typename _T, bool _C>
inline v2_r_<_T, _C>::v2_r_(typename v2_r_<_T, _C>::vector &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()) {
}
template<typename _T> v2_r_<_T, false> v2(typename v2_r_<_T, false>::vector &_v) {
	return v2_r_<_T, false>(_v);
}
template<typename _T> v2_r_<_T, true> v2(typename v2_r_<_T, true>::vector &_v) {
	return v2_r_<_T, true>(_v);
}

// v3
template<typename _V>
inline v3<_V>::v3(_V &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()), z(_v.cell<0, 2>()) {
}

// v4
template<typename _T, bool _C>
inline v4_r_<_T, _C>::v4_r_(typename v4_r_<_T, _C>::vector &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()), z(_v.cell<0, 2>()), w(_v.cell<0, 3>()) {
}
template<typename _T> v4_r_<_T, false> v4(typename v4_r_<_T, false>::vector &_v) {
	return v4_r_<_T, false>(_v);
}
template<typename _T> v4_r_<_T, true> v4(typename v4_r_<_T, true>::vector &_v) {
	return v4_r_<_T, true>(_v);
}

// quat
template<typename _T, bool _C>
inline quat_r_<_T, _C>::quat_r_(typename quat_r_<_T, _C>::vector &_v) : i(_v.cell<0, 0>()), j(_v.cell<0, 1>()), k(_v.cell<0, 2>()), r(_v.cell<0, 3>()) {
}
template<typename _T> quat_r_<_T, false> quat(typename quat_r_<_T, false>::vector &_v) {
	return quat_r_<_T, false>(_v);
}
template<typename _T> quat_r_<_T, true> quat(typename quat_r_<_T, true>::vector &_v) {
	return quat_r_<_T, true>(_v);
}
