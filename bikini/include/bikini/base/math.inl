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
template<uint _S, typename _T>
inline bool _matrix_row_<_S, _T>::cmp(const _matrix_row_ &_b) const {
	return m_cell == _b.cell() && parent_type::cmp(_b);
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
template<uint _H, uint _W, typename _T> template<uint _J>
inline const _T& matrix_<_H, _W, _T>::cell() const {
	c_assert(1 == _H && _J < _W);
	return row<0>().cell<_J>();
}
template<uint _H, uint _W, typename _T> template<uint _J>
inline _T& matrix_<_H, _W, _T>::cell() {
	c_assert(1 == _H && _J < _W);
	return row<0>().cell<_J>();
}
template<uint _H, uint _W, typename _T> struct _component_access_helper_ {
	template<uint _I> static inline typename matrix_<_H, _W, _T>::component_type& get(matrix_<_H, _W, _T> &_m) { return _m.row<_I>(); }
	template<uint _I> static inline const typename matrix_<_H, _W, _T>::component_type& get(const matrix_<_H, _W, _T> &_m) { return _m.row<_I>(); }
};
template<uint _H, typename _T> struct _component_access_helper_<_H, 1, _T> {
	template<uint _I> static inline typename matrix_<_H, 1, _T>::component_type& get(matrix_<_H, 1, _T> &_m) { return _m.cell<_I, 0>(); }
	template<uint _I> static inline const typename matrix_<_H, 1, _T>::component_type& get(const matrix_<_H, 1, _T> &_m) { return _m.cell<_I, 0>(); }
};
template<uint _W, typename _T> struct _component_access_helper_<1, _W, _T> {
	template<uint _I> static inline typename matrix_<1, _W, _T>::component_type& get(matrix_<1, _W, _T> &_m) { return _m.cell<0, _I>(); }
	template<uint _I> static inline const typename matrix_<1, _W, _T>::component_type& get(const matrix_<1, _W, _T> &_m) { return _m.cell<0, _I>(); }
};
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::x() const {
	return _component_access_helper_<_H, _W, _T>::get<0>(*this);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::x() {
	return _component_access_helper_<_H, _W, _T>::get<0>(*this);
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::y() const {
	return _component_access_helper_<_H, _W, _T>::get<1>(*this);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::y() {
	return _component_access_helper_<_H, _W, _T>::get<1>(*this);
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::z() const {
	return _component_access_helper_<_H, _W, _T>::get<2>(*this);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::z() {
	return _component_access_helper_<_H, _W, _T>::get<2>(*this);
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::w() const {
	return _component_access_helper_<_H, _W, _T>::get<3>(*this);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::w() {
	return _component_access_helper_<_H, _W, _T>::get<3>(*this);
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
inline bool matrix_<_H, _W, _T>::operator == (const matrix_ &_m) const {
	return cmp(_m);
}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::operator typename matrix_<_H, _W, _T>::row_type () {
//	c_assert(_H == 1);
//	return m_row;
//}
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::operator const typename matrix_<_H, _W, _T>::row_type () const {
	c_assert(_H == 1);
	return m_row;
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
}};
template<uint _W, typename _T> struct _matrix_row_mul_helper_<1, _W, _T> { static inline void mul(const _matrix_row_<_W, _T> &_a, const _matrix_row_<1, _T> &_b, _matrix_row_<_W, _T> &_c) {
	_a.mul(_b.cell(), _c);
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
template<uint _H, uint _W, typename _T>
inline bool matrix_<_H, _W, _T>::cmp(const matrix_ &_b) const {
	return m_row.cmp(_b.row()) && parent_type::cmp(_b);
}

// matrix minor
template<uint _W, uint _J, typename _T>
struct _matrix_minor_row_helper_ { static inline void get(const _matrix_row_<_W + 1, _T> &_a, _matrix_row_<_W, _T> &_c) {
	_matrix_minor_row_helper_<_W - 1, _J, _T>::get(_a, _c);
	_c.cell() = _a.cell<_J >= _W ? _W - 1 : _W>();
}};
template<uint _J, typename _T>
struct _matrix_minor_row_helper_<1, _J, _T> { static inline void get(const _matrix_row_<2, _T> &_a, _matrix_row_<1, _T> &_c) {
	_c.cell() = _a.cell<_J >= 1 ? 0 : 1>();
}};
template<uint _H, uint _W, uint _I, uint _J, typename _T>
struct _matrix_minor_helper_ { static inline void get(const matrix_<_H + 1, _W + 1, _T> &_a, matrix_<_H, _W, _T> &_c) {
	_matrix_minor_helper_<_H - 1, _W, _I, _J, _T>::get(_a, _c);
	_matrix_minor_row_helper_<_W, _J, _T>::get(_a.row<_I >= _H ? _H - 1 : _H>(), _c.row());
}};
template<uint _W, uint _I, uint _J, typename _T>
struct _matrix_minor_helper_<1, _W, _I, _J, _T> { static inline void get(const matrix_<2, _W + 1, _T> &_a, matrix_<1, _W, _T> &_c) {
	_matrix_minor_row_helper_<_W, _J, _T>::get(_a.row<_I >= 1 ? 0 : 1>(), _c.row());
}};
template<uint _I, uint _J, uint _S, typename _T>
inline const matrix_<_S - 1, _S - 1, _T> minor(const matrix_<_S, _S, _T> &_m) {
	matrix_<_S - 1, _S - 1, _T> l_m;
	_matrix_minor_helper_<_S - 1, _S - 1, _I, _J, _T>::get(_m, l_m);
	return l_m;
}

// matrix determinant
template<uint _I, typename _T> struct _matrix_determinant_sign_ {
	static inline _T value() { return _T(-1); }
};
template<typename _T> struct _matrix_determinant_sign_<0, _T> {
	static inline _T value() { return _T(1); }
};
template<uint _C, uint _S, typename _T>
struct _matrix_determinant_helper_ { static inline _T get(const matrix_<_S, _S, _T> &_a) {
	return _matrix_determinant_helper_<_C - 1, _S, _T>::get(_a) + determinant(minor<_C - 1, _S - 1>(_a)) * _a.cell<_C - 1, _S - 1>() * _matrix_determinant_sign_<(_C - 1 + _S - 1) % 2, _T>::value();
}};
template<uint _S, typename _T>
struct _matrix_determinant_helper_<1, _S, _T> { static inline _T get(const matrix_<_S, _S, _T> &_a) {
	return determinant(minor<0, _S - 1>(_a)) * _a.cell<0, _S - 1>() * _matrix_determinant_sign_<(_S - 1) % 2, _T>::value();
}};
template<typename _T>
struct _matrix_determinant_helper_<1, 1, _T> { static inline _T get(const matrix_<1, 1, _T> &_a) {
	return _a.cell<0, 0>();
}};
template<uint _S, typename _T>
inline const _T determinant(const matrix_<_S, _S, _T> &_m) {
	return _matrix_determinant_helper_<_S, _S, _T>::get(_m);
}

// matrix inverse
template<uint _I, typename _T> struct _matrix_inverse_sign_ {
	static inline _T value() { return _T(-1); }
};
template<typename _T> struct _matrix_inverse_sign_<0, _T> {
	static inline _T value() { return _T(1); }
};
template<uint _I, uint _J, uint _S, typename _T>
struct _matrix_inverse_row_helper_ { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, _T _d) {
	_matrix_inverse_row_helper_<_I, _J - 1, _S, _T>::get(_a, _c, _d);
	_c.cell<_J - 1, _I - 1>() = determinant(minor<_I - 1, _J - 1>(_a)) * _d * _matrix_inverse_sign_<(_I - 1 + _J - 1) % 2, _T>::value();
}};
template<uint _I, uint _S, typename _T>
struct _matrix_inverse_row_helper_<_I, 0, _S, _T> { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, _T _d) {
}};
template<uint _I, uint _J, uint _S, typename _T>
struct _matrix_inverse_helper_ { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, _T _d) {
		_matrix_inverse_helper_<_I - 1, _J, _S, _T>::get(_a, _c, _d);
		_matrix_inverse_row_helper_<_I, _J, _S, _T>::get(_a, _c, _d);
}};
template<uint _J, uint _S, typename _T>
struct _matrix_inverse_helper_<0, _J, _S, _T> { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, _T _d) {
}};
template<uint _S, typename _T>
inline bool inverse(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c) {
	_T l_d = determinant(_a);
	if(l_d < eps && l_d > -eps) return false;
	_matrix_inverse_helper_<_S, _S, _S, _T>::get(_a, _c, r_1 / l_d);
	return true;
}
template<uint _S, typename _T>
inline const matrix_<_S, _S, _T> inverse(const matrix_<_S, _S, _T> &_m) {
	matrix_<_S, _S, _T> l_m;
	if(!inverse(_m, l_m)) return _m;
	return l_m;
}

//// v2
//template<typename _T, bool _C>
//inline v2_r_<_T, _C>::v2_r_(typename v2_r_<_T, _C>::vector &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()) {
//}
//template<typename _T> v2_r_<_T, false> v2(typename v2_r_<_T, false>::vector &_v) {
//	return v2_r_<_T, false>(_v);
//}
//template<typename _T> v2_r_<_T, true> v2(typename v2_r_<_T, true>::vector &_v) {
//	return v2_r_<_T, true>(_v);
//}
//
//// v3
//template<typename _V>
//inline v3<_V>::v3(_V &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()), z(_v.cell<0, 2>()) {
//}
//
//// v4
//template<typename _T, bool _C>
//inline v4_r_<_T, _C>::v4_r_(typename v4_r_<_T, _C>::vector &_v) : x(_v.cell<0, 0>()), y(_v.cell<0, 1>()), z(_v.cell<0, 2>()), w(_v.cell<0, 3>()) {
//}
//template<typename _T> v4_r_<_T, false> v4(typename v4_r_<_T, false>::vector &_v) {
//	return v4_r_<_T, false>(_v);
//}
//template<typename _T> v4_r_<_T, true> v4(typename v4_r_<_T, true>::vector &_v) {
//	return v4_r_<_T, true>(_v);
//}
//
//// quat
//template<typename _T, bool _C>
//inline quat_r_<_T, _C>::quat_r_(typename quat_r_<_T, _C>::vector &_v) : i(_v.cell<0, 0>()), j(_v.cell<0, 1>()), k(_v.cell<0, 2>()), r(_v.cell<0, 3>()) {
//}
//template<typename _T> quat_r_<_T, false> quat(typename quat_r_<_T, false>::vector &_v) {
//	return quat_r_<_T, false>(_v);
//}
//template<typename _T> quat_r_<_T, true> quat(typename quat_r_<_T, true>::vector &_v) {
//	return quat_r_<_T, true>(_v);
//}

// color
template<typename _T>
inline color_<_T>::color_()
{}
template<typename _T>
inline color_<_T>::color_(_T _r, _T _g, _T _b, _T _a) :
	matrix_<1, 4, _T>(_r, _g, _b, _a)
{}
template<typename _T>
inline color_<_T>::color_(u32 _c) :
	matrix_<1, 4, _T>(_T((_c>>16)&0xff)/_T(255), _T((_c>>8)&0xff)/_T(255), _T((_c>>0)&0xff)/_T(255), _T((_c>>24)&0xff)/_T(255))
{}
template<typename _T>
inline const _T color_<_T>::r() const {
	return x();
}
template<typename _T>
inline _T& color_<_T>::r() {
	return x();
}
template<typename _T>
inline const _T color_<_T>::g() const {
	return y();
}
template<typename _T>
inline _T& color_<_T>::g() {
	return y();
}
template<typename _T>
inline const _T color_<_T>::b() const {
	return z();
}
template<typename _T>
inline _T& color_<_T>::b() {
	return z();
}
template<typename _T>
inline const _T color_<_T>::a() const {
	return w();
}
template<typename _T>
inline _T& color_<_T>::a() {
	return w();
}
template<typename _T>
inline color_<_T>::operator u32 () const {
	return (u32(a()*_T(255))<<24)|(u32(r()*_T(255))<<16)|(u32(g()*_T(255))<<8)|(u32(b()*_T(255))<<0);
}

// quat
template<typename _T>
inline quat_<_T>::quat_()
{}
template<typename _T>
inline quat_<_T>::quat_(_T _i, _T _j, _T _k, _T _r) :
	matrix_<1, 4, _T>(_i, _j, _k, _r)
{}
template<typename _T>
inline const _T quat_<_T>::i() const {
	return x();
}
template<typename _T>
inline _T& quat_<_T>::i() {
	return x();
}
template<typename _T>
inline const _T quat_<_T>::j() const {
	return y();
}
template<typename _T>
inline _T& quat_<_T>::j() {
	return y();
}
template<typename _T>
inline const _T quat_<_T>::k() const {
	return z();
}
template<typename _T>
inline _T& quat_<_T>::k() {
	return z();
}
template<typename _T>
inline const _T quat_<_T>::r() const {
	return w();
}
template<typename _T>
inline _T& quat_<_T>::r() {
	return w();
}

// random
template<uint _ID>
uint random_<_ID>::seed = 0;
template<uint _ID>
inline uint random_<_ID>::get(uint _max /*= max*/) {
	seed = seed * 1103515245 + 12345;
	return uint(seed / 65536) % _max;
}
template<uint _ID>
inline real random_<_ID>::get(real _max) {
	return real(get(max)) / real(max) * _max;
}
template<uint _ID>
inline real random_<_ID>::get(real _min, real _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(_max - _min);
}

// create random GUID
inline GUID new_GUID() {
	GUID l_guid;
	l_guid.Data1 = (unsigned long)((random::get() << 16) | random::get());
	l_guid.Data2 = (unsigned short)random::get();
	l_guid.Data3 = (unsigned short)(0x4000 | (0x0fff & random::get()));
	for(uint i = 0; i < 8; ++i) l_guid.Data4[i] = (unsigned char)random::get();
	return l_guid;
}
