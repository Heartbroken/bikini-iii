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

template<uint _D1, uint _D2, uint _D3, typename _T>
inline void multiply(const vector_<_D1, vector_<_D2, _T> > &_a, const vector_<_D2, vector_<_D3, _T> > &_b, vector_<_D1, vector_<_D3, _T> > &_c) {
}
template<uint _D1, uint _D2, typename _T>
inline void multiply(const vector_<_D1, _T> &_a, const vector_<_D1, vector_<_D2, _T> > &_b, vector_<1, vector_<_D1, _T> > &_c) {
	multiply(vector_<1, vector_<_D1, _T> >(_a), _b, _c);
}
template<uint _D1, uint _D2, typename _T>
inline void multiply(const vector_<_D1, vector_<_D2, _T> > &_a, const vector_<_D1, _T> &_b, vector_<_D1, vector_<1, _T> > &_c) {
	multiply(_a, vector_<_D1, vector_<1, _T> >(_b), _c);
}
template<uint _D, typename _T>
inline void multiply(const vector_<_D, _T> &_a, const vector_<_D, _T> &_b, vector_<1, vector_<1, _T> > &_c) {
	multiply(vector_<1, vector_<_D, _T> >(_a), vector_<_D, vector_<1, _T> >(_b), _c);
}

// types

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
	return static_cast<matrix_<1, _W, _T>&>(*this);
}
template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
inline const _T& matrix_<_H, _W, _T>::cell() const {
	c_assert(_I < _H && _J < _W);
	return static_cast<const matrix_<1, _J + 1, _T>&>(row<_I>()).row();
}
template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
inline _T& matrix_<_H, _W, _T>::cell() {
	c_assert(_I < _H && _J < _W);
	return static_cast<matrix_<1, _J + 1, _T>&>(row<_I>()).row();
}
template<uint _H, uint _W, typename _T>
inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) const {
	assert(_i < _H || (_H == 1 && _i < _W));
	typedef typename select<_H == 1, matrix_<1, 1, _T>, matrix_<1, _W, _T> >::type aux_type;
	return *(&static_cast<const aux_type&>(*this).row() + _i);
}
template<uint _H, uint _W, typename _T>
inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) {
	assert(_i < _H || (_H == 1 && _i < _W));
	typedef typename select<_H == 1, matrix_<1, 1, _T>, matrix_<1, _W, _T> >::type aux_type;
	return *(&static_cast<aux_type&>(*this).row() + _i);
}

template<uint _H, uint _W, typename _T>
inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator = (const matrix_ &_m) {
	parent_type::operator = (_m);
	m_row = _m.row();
	return *this;
}

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

// v2
template<typename _T, bool _C>
inline v2_reference<_T, _C>::v2_reference(typename v2_reference<_T, _C>::vector &_v) : x(_v.cell<0>()), y(_v.cell<1>()) {
}
template<typename _T> v2_reference<_T, false> v2(vector_<2, _T> &_v) {
	return v2_reference<_T, false>(_v);
}
template<typename _T> v2_reference<_T, true> v2(const vector_<2, _T> &_v) {
	return v2_reference<_T, true>(_v);
}

// v3
template<typename _T, bool _C>
inline v3_reference<_T, _C>::v3_reference(typename v3_reference<_T, _C>::vector &_v) : x(_v.cell<0>()), y(_v.cell<1>()), z(_v.cell<2>()) {
}
template<typename _T> v3_reference<_T, false> v3(vector_<3, _T> &_v) {
	return v3_reference<_T, false>(_v);
}
template<typename _T> v3_reference<_T, true> v3(const vector_<3, _T> &_v) {
	return v3_reference<_T, true>(_v);
}

// v4
template<typename _T, bool _C>
inline v4_reference<_T, _C>::v4_reference(typename v4_reference<_T, _C>::vector &_v) : x(_v.cell<0>()), y(_v.cell<1>()), z(_v.cell<2>()), w(_v.cell<3>()) {
}
template<typename _T> v4_reference<_T, false> v4(vector_<4, _T> &_v) {
	return v4_reference<_T, false>(_v);
}
template<typename _T> v4_reference<_T, true> v4(const vector_<4, _T> &_v) {
	return v4_reference<_T, true>(_v);
}

// quat
template<typename _T, bool _C>
inline quat_reference<_T, _C>::quat_reference(typename quat_reference<_T, _C>::vector &_v) : i(_v.cell<0>()), j(_v.cell<1>()), k(_v.cell<2>()), r(_v.cell<3>()) {
}
template<typename _T> quat_reference<_T, false> quat(vector_<4, _T> &_v) {
	return quat_reference<_T, false>(_v);
}
template<typename _T> quat_reference<_T, true> quat(const vector_<4, _T> &_v) {
	return quat_reference<_T, true>(_v);
}

//// matrix
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_() {
//}
////template<uint _H, uint _W, typename _T>
////inline matrix_<_H, _W, _T>::matrix_(const matrix_ &_m) : matrix_<_H - 1, _W, _T>(_m), m_row(_m.row()) {
////}
////template<uint _H, uint _W, typename _T>
////inline matrix_<_H, _W, _T>::matrix_(const matrix_<_H - 1, _W, _T> &_m) : matrix_<_H - 1, _W, _T>(_m) {
////}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() const {
//	return super::cell();
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() {
//	return super::cell();
//}
//template<uint _H, uint _W, typename _T> template<uint _I>
//inline const typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() const {
//	return static_cast<const matrix_<_H - 1, _W, _T>&>(*this).row();
//}
//template<uint _H, uint _W, typename _T> template<uint _I>
//inline typename matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::row() {
//	return static_cast<matrix_<_H - 1, _W, _T>&>(*this).row();
//}
//template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
//inline const _T& matrix_<_H, _W, _T>::cell() const {
//	c_assert(_I < _H && _J < _W);
//	return row<_I>().cell<_J>();
//}
//template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
//inline _T& matrix_<_H, _W, _T>::cell() {
//	c_assert(_I < _H && _J < _W);
//	return row<_I>().cell<_J>();
//}

//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::operator [] (uint _i) const {
//	assert(_i < _H);
//	return *(&static_cast<const matrix_<1, _W, _T>&>(*this) + _i);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::vector& matrix_<_H, _W, _T>::operator [] (uint _i) {
//	assert(_i < _H);
//	return *(&static_cast<matrix_<1, _W, _T>&>(*this) + _i);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator = (const matrix_ &_v) {
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator + (const matrix_ &_v) const {
//	matrix_ l_m = super::operator + (_v);
//	l_m.row() = row() + _v.row();
//	return l_m;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator += (const matrix_ &_v) {
//	super::operator += (_v);
//	row() += _v.row();
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator - (const matrix_ &_v) const {
//	matrix_ l_m = super::operator - (_v);
//	l_m.row() = row() - _v.row();
//	return l_m;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator -= (const matrix_ &_v) {
//	super::operator -= (_v);
//	row() -= _v.row();
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator * (_Type _s) const {
//	matrix_ l_m = super::operator * (_s);
//	l_m.row() = row() * _s;
//	return l_m;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator *= (_Type _s) {
//	super::operator *= (_s);
//	row() *= _s;
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator / (_Type _s) const {
//	matrix_ l_m = super::operator / (_s);
//	l_m.row() = row() / _s;
//	return l_m;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator /= (_Type _s) {
//	super::operator /= (_s);
//	row() /= _s;
//	return *this;
//}
