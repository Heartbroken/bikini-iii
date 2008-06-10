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
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_() {
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(const vector_ &_v) : vector_<_D - 1, _T>(_v), m_cell(_v.cell<_D - 1>()) {
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(const typename vector_<_D - 1, _T> &_v) : vector_<_D - 1, _T>(_v) {
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(_T _cell0) : m_cell(_cell0) {
	c_assert(_D == 1);
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(_T _cell0, _T _cell1) : vector_<_D - 1, _T>(_cell0), m_cell(_cell1) {
	c_assert(_D == 2);
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(_T _cell0, _T _cell1, _T _cell2) : vector_<_D - 1, _T>(_cell0, _cell1), m_cell(_cell2){
	c_assert(_D == 3);
}
template<uint _D, typename _T>
inline vector_<_D, _T>::vector_(_T _cell0, _T _cell1, _T _cell2, _T _cell3) : vector_<_D - 1, _T>(_cell0, _cell1, _cell2), m_cell(_cell3){
	c_assert(_D == 4);
}
template<uint _D, typename _T>
inline const typename vector_<_D, _T>::type& vector_<_D, _T>::cell() const {
	return m_cell;
}
template<uint _D, typename _T>
inline typename vector_<_D, _T>::type& vector_<_D, _T>::cell() {
	return m_cell;
}
template<uint _D, typename _T> template<uint _I>
inline const typename vector_<_D, _T>::type& vector_<_D, _T>::cell() const {
	c_assert(_I < dimention);
	return static_cast<const vector_<_I + 1, _T>&>(*this).cell();
}
template<uint _D, typename _T> template<uint _I>
inline typename vector_<_D, _T>::type& vector_<_D, _T>::cell() {
	c_assert(_I < dimention);
	return static_cast<vector_<_I + 1, _T>&>(*this).cell();
}
template<uint _D, typename _T>
inline const typename vector_<_D, _T>::type vector_<_D, _T>::operator [] (uint _i) const {
	assert(_i < dimention);
	return *(&static_cast<const vector_<1, _T>&>(*this).cell() + _i);
}
template<uint _D, typename _T>
inline typename vector_<_D, _T>::type& vector_<_D, _T>::operator [] (uint _i) {
	assert(_i < dimention);
	return *(&static_cast<vector_<1, _T>&>(*this).cell() + _i);
}
template<uint _D, typename _T>
inline vector_<_D, _T>& vector_<_D, _T>::operator = (const vector_ &_v) {
	super::operator = (_v);
	m_cell = _v.cell();
	return *this;
}
template<uint _D, typename _T>
inline const vector_<_D, _T> vector_<_D, _T>::operator + (const vector_ &_v) const {
	vector_ l_v = super::operator + (_v);
	l_v.cell() = m_cell + _v.cell();
	return l_v;
}
template<uint _D, typename _T>
inline vector_<_D, _T>& vector_<_D, _T>::operator += (const vector_ &_v) {
	super::operator += (_v);
	m_cell += _v.cell();
	return *this;
}
template<uint _D, typename _T>
inline const vector_<_D, _T> vector_<_D, _T>::operator - (const vector_ &_v) const {
	vector_ l_v = super::operator - (_v);
	l_v.cell() = m_cell - _v.cell();
	return l_v;
}
template<uint _D, typename _T>
inline vector_<_D, _T>& vector_<_D, _T>::operator -= (const vector_ &_v) {
	super::operator -= (_v);
	m_cell -= _v.cell();
	return *this;
}
template<uint _D, typename _T>
inline const vector_<_D, _T> vector_<_D, _T>::operator * (_T _s) const {
	vector_ l_v = super::operator * (_s);
	l_v.cell() = m_cell * _s;
	return l_v;
}
template<uint _D, typename _T>
inline vector_<_D, _T>& vector_<_D, _T>::operator *= (_T _s) {
	super::operator *= (_s);
	m_cell *= _s;
	return *this;
}
template<uint _D, typename _T>
inline const vector_<_D, _T> vector_<_D, _T>::operator / (_T _s) const {
	vector_ l_v = super::operator / (_s);
	l_v.cell() = m_cell / _s;
	return l_v;
}
template<uint _D, typename _T>
inline vector_<_D, _T>& vector_<_D, _T>::operator /= (_T _s) {
	super::operator /= (_s);
	m_cell /= _s;
	return *this;
}

//// vector2
//template<typename _T>
//inline vector2_<_T>::vector2_() : x(cell<0>()), y(cell<1>()) {
//}
//template<typename _T>
//inline vector2_<_T>::vector2_(real _x, real _y) : x(cell<0>()), y(cell<1>())  {
//	x = _x; y = _y;
//}
//template<typename _T> template<uint _D>
//inline vector2_<_T>::vector2_(const vector_<_D, _T> &_v) : vector_<2, _T>(_v), x(cell<0>()), y(cell<1>()) {
//}
//template<typename _T> template<uint _D>
//inline vector2_<_T>& vector2_<_T>::operator = (const vector_<_D, _T> &_v) {
//	x = _v.cell<0>(); y = _v.cell<1>();
//	return *this;
//}

//// vector3
//template<typename _T>
//inline vector3_<_T>::vector3_() : x(cell<0>()), y(cell<1>()), z(cell<2>()) {
//}
//template<typename _T>
//inline vector3_<_T>::vector3_(real _x, real _y, real _z) : x(cell<0>()), y(cell<1>()), z(cell<2>())  {
//	x = _x; y = _y; z = _z;
//}
//template<typename _T> template<uint _D>
//inline vector3_<_T>::vector3_(const vector_<_D, _T> &_v) : vector_<3, _T>(_v), x(cell<0>()), y(cell<1>()), z(cell<2>()) {
//}
//template<typename _T> template<uint _D>
//inline vector3_<_T>& vector3_<_T>::operator = (const vector_<_D, _T> &_v) {
//	x = _v.cell<0>(); y = _v.cell<1>(); z = _v.cell<2>();
//	return *this;
//}

// matrix
template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>::matrix_() {
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() const {
	return m_row;
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() {
	return m_row;
}
template<uint _H, uint _W, typename _T> template<uint _I>
inline const typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() const {
	return static_cast<const matrix_<_H - 1, _W, _T>&>(*this).row();
}
template<uint _H, uint _W, typename _T> template<uint _I>
inline typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() {
	return static_cast<matrix_<_H - 1, _W, _T>&>(*this).row();
}

//// matrix3
//template<typename _T>
//inline matrix3_<_T>::matrix3_() :
//	m11(row<0>().cell<0>()), m12(row<0>().cell<1>()), m13(row<0>().cell<2>()),
//	m21(row<1>().cell<0>()), m22(row<1>().cell<1>()), m23(row<1>().cell<2>()),
//	m31(row<2>().cell<0>()), m32(row<2>().cell<1>()), m33(row<2>().cell<2>())
//{}
//template<typename _T>
//inline matrix3_<_T>::matrix3_(
//	real _m11, real _m12, real _m13,
//	real _m21, real _m22, real _m23,
//	real _m31, real _m32, real _m33
//) :
//	m11(row<0>().cell<0>()), m12(row<0>().cell<1>()), m13(row<0>().cell<2>()),
//	m21(row<1>().cell<0>()), m22(row<1>().cell<1>()), m23(row<1>().cell<2>()),
//	m31(row<2>().cell<0>()), m32(row<2>().cell<1>()), m33(row<2>().cell<2>())
//{
//	m11 = _m11; m12 = _m12; m13 = _m13;
//	m21 = _m21; m22 = _m22; m23 = _m23;
//	m31 = _m31; m32 = _m32; m33 = _m33;
//}