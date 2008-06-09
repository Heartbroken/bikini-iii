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
inline vector<_D, _R>::vector() {
}
template<uint _D, typename _R>
inline vector<_D, _R>::vector(const vector &_v) : vector<_D - 1, _R>(_v), m_cell(_v.cell<_D - 1>()) {
}
template<uint _D, typename _R>
inline vector<_D, _R>::vector(const typename vector<_D - 1, _R> &_v) : vector<_D - 1, _R>(_v) {
}
template<uint _D, typename _R>
inline const typename vector<_D, _R>::real vector<_D, _R>::cell() const {
	return m_cell;
}
template<uint _D, typename _R>
inline typename vector<_D, _R>::real& vector<_D, _R>::cell() {
	return m_cell;
}
template<uint _D, typename _R> template<uint _I>
inline const typename vector<_D, _R>::real vector<_D, _R>::cell() const {
	c_assert(_I < dimention);
	return static_cast<const vector<_I + 1, _R>&>(*this).cell();
}
template<uint _D, typename _R> template<uint _I>
inline typename vector<_D, _R>::real& vector<_D, _R>::cell() {
	c_assert(_I < dimention);
	return static_cast<vector<_I + 1, _R>&>(*this).cell();
}
template<uint _D, typename _R>
inline const typename vector<_D, _R>::real vector<_D, _R>::operator [] (uint _i) const {
	assert(_i < dimention);
	return _i == last ? m_cell : super::operaor [] (_i);
}
template<uint _D, typename _R>
inline typename vector<_D, _R>::real& vector<_D, _R>::operator [] (uint _i) {
	assert(_i < dimention);
	return _i == last ? m_cell : vector<_D - 1, _R>::operaor [] (_i);
}
template<uint _D, typename _R>
inline vector<_D, _R>& vector<_D, _R>::operator = (const vector &_v) {
	vector<_D - 1, _R>::operator = (_v);
	m_cell = _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector<_D, _R> vector<_D, _R>::operator + (const vector &_v) const {
	vector l_v = vector<_D - 1, _R>::operator + (_v);
	l_v.cell() = m_cell + _v.cell();
	return l_v;
}
template<uint _D, typename _R>
inline vector<_D, _R>& vector<_D, _R>::operator += (const vector &_v) {
	vector<_D - 1, _R>::operator += (_v);
	m_cell += _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector<_D, _R> vector<_D, _R>::operator - (const vector &_v) const {
	vector l_v = vector<_D - 1, _R>::operator - (_v);
	l_v.cell() = m_cell - _v.cell();
	return l_v;
}
template<uint _D, typename _R>
inline vector<_D, _R>& vector<_D, _R>::operator -= (const vector &_v) {
	vector<_D - 1, _R>::operator -= (_v);
	m_cell -= _v.cell();
	return *this;
}
template<uint _D, typename _R>
inline const vector<_D, _R> vector<_D, _R>::operator * (real _s) const {
	vector l_v = vector<_D - 1, _R>::operator * (_s);
	l_v.cell() = m_cell * _s;
	return l_v;
}
template<uint _D, typename _R>
inline vector<_D, _R>& vector<_D, _R>::operator *= (real _s) {
	vector<_D - 1, _R>::operator *= (_s);
	m_cell *= _s;
	return *this;
}
template<uint _D, typename _R>
inline const vector<_D, _R> vector<_D, _R>::operator / (real _s) const {
	vector l_v = vector<_D - 1, _R>::operator / (_s);
	l_v.cell() = m_cell / _s;
	return l_v;
}
template<uint _D, typename _R>
inline vector<_D, _R>& vector<_D, _R>::operator /= (real _s) {
	vector<_D - 1, _R>::operator /= (_s);
	m_cell /= _s;
	return *this;
}
//template<uint _D, typename _R> template<uint _D2>
//inline vector<_D, _R>::operator vector<_D2, _R> () const {
//	return vector<_D2, real>(*this);
//}

// matrix
template<uint _H, uint _W, typename _R>
inline matrix<_H, _W, _R>::matrix() {
}
template<uint _H, uint _W, typename _R> template<uint _I, uint _J>
inline const typename matrix<_H, _W, _R>::real matrix<_H, _W, _R>::cell() const {
	c_assert(_I < height && _J < width);
	return m_m[_I][_J];
}
template<uint _H, uint _W, typename _R> template<uint _I, uint _J>
inline typename matrix<_H, _W, _R>::real& matrix<_H, _W, _R>::cell() {
	c_assert(_I < height && _J < width);
	return m_m[_I][_J];
}
template<uint _H, uint _W, typename _R> template<uint _J>
inline const typename matrix<_H, _W, _R>::real matrix<_H, _W, _R>::cell() const {
	return cell<0, _J>;
}
template<uint _H, uint _W, typename _R> template<uint _I>
inline typename matrix<_H, _W, _R>::real& matrix<_H, _W, _R>::cell() {
	return cell<0, _J>;
}

// vector2
template<typename _R>
inline vector2_<_R>::vector2_() : x(cell<0>()), y(cell<1>()) {
}
template<typename _R>
inline vector2_<_R>::vector2_(real _x, real _y) : x(cell<0>()), y(cell<1>())  {
	x = _x; y = _y;
}
template<typename _R> template<uint _D2>
inline vector2_<_R>::vector2_(const vector<_D2, real> &_v) : x(cell<0>()), y(cell<1>()) {
	x = _v.cell<0>(); y = _v.cell<1>();
}
template<typename _R> template<uint _D2>
inline vector2_<_R>& vector2_<_R>::operator = (const vector<_D2, real> &_v) {
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
template<typename _R> template<uint _D2>
inline vector3_<_R>::vector3_(const vector<_D2, real> &_v) : x(cell<0>()), y(cell<1>()), z(cell<2>()) {
	x = _v.cell<0>(); y = _v.cell<1>(); z = _v.cell<2>();
}
template<typename _R> template<uint _D2>
inline vector3_<_R>& vector3_<_R>::operator = (const vector<_D2, real> &_v) {
	x = _v.cell<0>(); y = _v.cell<1>(); z = _v.cell<2>();
	return *this;
}
