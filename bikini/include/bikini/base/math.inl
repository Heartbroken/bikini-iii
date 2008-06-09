#pragma once

// functions
inline real bk::sqrt(real _a) {
	return sqrtf(_a);
}
inline real bk::rsqrt(real _a) {
	return 1.f / sqrt(_a);
}
inline real bk::abs(real _a) {
	return fabsf(_a);
}
inline real bk::sin(real _a) {
	return sinf(_a);
}
inline real bk::cos(real _a) {
	return cosf(_a);
}
inline real bk::asin(real _a) {
	return asinf(_a);
}
inline real bk::acos(real _a) {
	return acosf(_a);
}
inline real bk::tan(real _a) {
	return tanf(_a);
}
inline real bk::cot(real _a) {
	return 1.f / tan(_a);
}
inline void bk::sincos(real _a, real &_s, real &_c) {
	_s = sin(_a); _c = cos(_a);
}
inline real bk::d2r(real _d) {
	return _d * 0.017453f;
}
inline real bk::r2d(real _r) {
	return _r * 57.29578f;
}
inline real bk::pow(real _a, real _b) {
	return powf(_a, _b);
}
inline bool is_tiny(real _a) {
	return (_a > -eps && _a < eps);
}
inline u32 next_pow2(u32 _a) {
	u32 l_a = _a; l_a |= l_a>>1; l_a |= l_a>>2; l_a |= l_a>>4; l_a |= l_a>>8; l_a |= l_a>>16;
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

// vector
template<uint _D, typename _R>
inline vector_<_D, _R>::vector_() {
}
template<uint _D, typename _R>
inline vector_<_D, _R>::vector_(const vector_ &_v) : vector_<_D - 1, _R>(_v), m_cell(_v.cell<_D - 1>()) {
}
template<uint _D, typename _R>
inline vector_<_D, _R>::vector_(const typename vector_<_D - 1, _R> &_v) : vector_<_D - 1, _R>(_v) {
}
template<uint _D, typename _R>
inline const typename vector_<_D, _R>::real vector_<_D, _R>::cell() const {
	return m_cell;
}
template<uint _D, typename _R>
inline typename vector_<_D, _R>::real& vector_<_D, _R>::cell() {
	return m_cell;
}
template<uint _D, typename _R> template<uint _I>
inline const typename vector_<_D, _R>::real vector_<_D, _R>::cell() const {
	c_assert(_I < dimention);
	return static_cast<const vector_<_I + 1, _R>&>(*this).cell();
}
template<uint _D, typename _R> template<uint _I>
inline typename vector_<_D, _R>::real& vector_<_D, _R>::cell() {
	c_assert(_I < dimention);
	return static_cast<vector_<_I + 1, _R>&>(*this).cell();
}
template<uint _D, typename _R>
inline const typename vector_<_D, _R>::real vector_<_D, _R>::operator [] (uint _i) const {
	assert(_i < dimention);
	return _i == last ? m_cell : super::operaor [] (_i);
}
template<uint _D, typename _R>
inline typename vector_<_D, _R>::real& vector_<_D, _R>::operator [] (uint _i) {
	assert(_i < dimention);
	return _i == last ? m_cell : super::operaor [] (_i);
}
template<uint _D, typename _R>
inline vector_<_D, _R>& vector_<_D, _R>::operator = (const vector_ &_v) {
	super::operator = (_v);
	m_cell = _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector_<_D, _R> vector_<_D, _R>::operator + (const vector_ &_v) const {
	vector_ l_v = super::operator + (_v);
	l_v.cell() = m_cell + _v.cell();
	return l_v;
}
template<uint _D, typename _R>
inline vector_<_D, _R>& vector_<_D, _R>::operator += (const vector_ &_v) {
	super::operator += (_v);
	m_cell += _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector_<_D, _R> vector_<_D, _R>::operator - (const vector_ &_v) const {
	vector_ l_v = super::operator - (_v);
	l_v.cell() = m_cell - _v.cell();
	return l_v;
}
template<uint _D, typename _R>
inline vector_<_D, _R>& vector_<_D, _R>::operator -= (const vector_ &_v) {
	super::operator -= (_v);
	m_cell -= _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector_<_D, _R> vector_<_D, _R>::operator * (real _s) const {
	vector_ l_v = super::operator * (_s);
	l_v.cell() = m_cell * _s;
	return l_v;
}
template<uint _D, typename _R>
inline vector_<_D, _R>& vector_<_D, _R>::operator *= (real _s) {
	super::operator *= (_s);
	m_cell *= _s;
	return *this;
}
template<uint _D, typename _R>
inline const vector_<_D, _R> vector_<_D, _R>::operator / (real _s) const {
	vector_ l_v = super::operator / (_s);
	l_v.cell() = m_cell / _s;
	return l_v;
}
template<uint _D, typename _R>
inline vector_<_D, _R>& vector_<_D, _R>::operator /= (real _s) {
	super::operator /= (_s);
	m_cell /= _s;
	return *this;
}

// vector2
template<typename _R>
inline vector2_<_R>::vector2_() : x(cell<0>()), y(cell<1>()) {
}
template<typename _R>
inline vector2_<_R>::vector2_(real _x, real _y) : x(cell<0>()), y(cell<1>())  {
	x = _x; y = _y;
}
template<typename _R> template<uint _D>
inline vector2_<_R>::vector2_(const vector_<_D, _R> &_v) : vector_<2, _R>(_v), x(cell<0>()), y(cell<1>()) {
}
template<typename _R> template<uint _D>
inline vector2_<_R>& vector2_<_R>::operator = (const vector_<_D, _R> &_v) {
	x = _v.cell<0>(); y = _v.cell<1>();
	return *this;
}

// vector3
template<typename _R>
inline vector3_<_R>::vector3_() : x(cell<0>()), y(cell<1>()), z(cell<2>()) {
}
template<typename _R>
inline vector3_<_R>::vector3_(real _x, real _y, real _z) : x(cell<0>()), y(cell<1>()), z(cell<2>())  {
	x = _x; y = _y; z = _z;
}
template<typename _R> template<uint _D>
inline vector3_<_R>::vector3_(const vector_<_D, _R> &_v) : vector_<3, _R>(_v), x(cell<0>()), y(cell<1>()), z(cell<2>()) {
}
template<typename _R> template<uint _D>
inline vector3_<_R>& vector3_<_R>::operator = (const vector_<_D, _R> &_v) {
	x = _v.cell<0>(); y = _v.cell<1>(); z = _v.cell<2>();
	return *this;
}

// matrix
template<uint _H, uint _W, typename _R>
inline matrix_<_H, _W, _R>::matrix_() {
}
template<uint _H, uint _W, typename _R>
inline const typename matrix_<_H, _W, _R>::vector& matrix_<_H, _W, _R>::row() const {
	return m_row;
}
template<uint _H, uint _W, typename _R>
inline typename matrix_<_H, _W, _R>::vector& matrix_<_H, _W, _R>::row() {
	return m_row;
}
template<uint _H, uint _W, typename _R> template<uint _I>
inline const typename matrix_<_H, _W, _R>::vector& matrix_<_H, _W, _R>::row() const {
	return static_cast<const matrix_<_H - 1, _W, _R>&>(*this).row();
}
template<uint _H, uint _W, typename _R> template<uint _I>
inline typename matrix_<_H, _W, _R>::vector& matrix_<_H, _W, _R>::row() {
	return static_cast<matrix_<_H - 1, _W, _R>&>(*this).row();
}

// matrix3
template<typename _R>
inline matrix3_<_R>::matrix3_() :
	m11(row<0>().cell<0>()), m12(row<0>().cell<1>()), m13(row<0>().cell<2>()),
	m21(row<1>().cell<0>()), m22(row<1>().cell<1>()), m23(row<1>().cell<2>()),
	m31(row<2>().cell<0>()), m32(row<2>().cell<1>()), m33(row<2>().cell<2>())
{}
template<typename _R>
inline matrix3_<_R>::matrix3_(
	real _m11, real _m12, real _m13,
	real _m21, real _m22, real _m23,
	real _m31, real _m32, real _m33
) :
	m11(row<0>().cell<0>()), m12(row<0>().cell<1>()), m13(row<0>().cell<2>()),
	m21(row<1>().cell<0>()), m22(row<1>().cell<1>()), m23(row<1>().cell<2>()),
	m31(row<2>().cell<0>()), m32(row<2>().cell<1>()), m33(row<2>().cell<2>())
{
	m11 = _m11; m12 = _m12; m13 = _m13;
	m21 = _m21; m22 = _m22; m23 = _m23;
	m31 = _m31; m32 = _m32; m33 = _m33;
}