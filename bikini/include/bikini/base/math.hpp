#pragma once

// constants
const real pi = real(3.1415926535897932384626433832795);
const real infinity = real(1e38);
const real eps = real(1e-5);

// functions
inline real sqrt(real _a);
inline real rsqrt(real _a);
inline real abs(real _a);
inline real sin(real _a);
inline real cos(real _a);
inline real tan(real _a);
inline real asin(real _a);
inline real acos(real _a);
inline real cot(real _a);
inline void sincos(real _a, real &_s, real &_c);
inline real d2r(real _d);
inline real r2d(real _r);
inline real pow(real _a, real _b);
inline bool is_tiny(real _a);
inline u32 next_pow2(u32 _a);
inline real random();
inline real random(real _max);
inline real random(real _min, real _max);
template<typename _T> inline const _T& min(const _T &_a, const _T &_b);
template<typename _T> inline const _T& max(const _T &_a, const _T &_b);
template<typename _T> inline const _T& clamp(const _T &_a, const _T &_min, const _T &_max);
template<typename _T> inline _T wrap(const _T &_a, const _T &_min, const _T &_max);
template<typename _T> inline void swap(_T &_a, _T &_b);
template<uint _A, uint _B> struct c_min { static const uint result = _A > _B ? _B : _A; };
template<uint _A, uint _B> struct c_max { static const uint result = _A > _B ? _A : _B; };

// types

// _matrix_row_
template<uint _Size, typename _Type>
struct _matrix_row_ : _matrix_row_<_Size - 1, _Type> {
	typedef _matrix_row_<_Size - 1, _Type> parent_type;
	typedef _Type cell_type;
	inline _matrix_row_();
	inline _matrix_row_(const _matrix_row_ &_r);
	inline _matrix_row_(const parent_type &_r);
	inline _matrix_row_(_Type _cell0);
	inline _matrix_row_(_Type _cell0, _Type _cell1);
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2);
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	inline const _Type& cell() const;
	inline _Type& cell();
	template<uint _I> inline const _Type& cell() const;
	template<uint _I> inline _Type& cell();
	inline const _Type& operator [] (uint _i) const;
	inline _Type& operator [] (uint _i);
	inline _matrix_row_& operator = (const _matrix_row_ &_r);
	inline const _matrix_row_ operator + (const _matrix_row_ &_r) const;
	inline _matrix_row_& operator += (const _matrix_row_ &_r);
	inline const _matrix_row_ operator - (const _matrix_row_ &_r) const;
	inline _matrix_row_& operator -= (const _matrix_row_ &_r);
	inline const _matrix_row_ operator * (_Type _s) const;
	inline _matrix_row_& operator *= (_Type _s);
	inline const _matrix_row_ operator / (_Type _s) const;
	inline _matrix_row_& operator /= (_Type _s);
	inline operator _Type () const { c_assert(_Size == 1); return m_cell; }
	inline void add(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void sub(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void mul(_Type _s, _matrix_row_ &_c) const;
	inline void div(_Type _s, _matrix_row_ &_c) const;
private:
	cell_type m_cell;
};
template<typename _Type>
struct _matrix_row_<0, _Type> {
	inline void add(const _matrix_row_&, _matrix_row_&) const {}
	inline void sub(const _matrix_row_&, _matrix_row_&) const {}
	inline void mul(_Type, _matrix_row_&) const {}
	inline void div(_Type, _matrix_row_&) const {}
};
// matrix
template<uint _Height, uint _Width, typename _Type>
struct matrix_ : matrix_<_Height - 1, _Width, _Type> {
	typedef matrix_<_Height - 1, _Width, _Type> parent_type;
	typedef _matrix_row_<_Width, _Type> row_type;
	inline matrix_();
	inline matrix_(const matrix_ &_m);
	inline matrix_(const parent_type &_m);
	inline matrix_(_Type _cell0);
	inline matrix_(_Type _cell0, _Type _cell1);
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2);
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	typedef matrix_<1, _Width, _Type> row_matrix;
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1);
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2);
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2, const row_matrix &_row3);
	inline const row_type& row() const;
	inline row_type& row();
	template<uint _I> inline const row_type& row() const;
	template<uint _I> inline row_type& row();
	template<uint _I, uint _J> inline const _Type& cell() const;
	template<uint _I, uint _J> inline _Type& cell();
	inline const row_type& operator [] (uint _i) const;
	inline row_type& operator [] (uint _i);
	inline matrix_& operator = (const matrix_ &_m);
	inline const matrix_ operator + (const matrix_ &_m) const;
	inline matrix_& operator += (const matrix_ &_m);
	inline const matrix_ operator - (const matrix_ &_m) const;
	inline matrix_& operator -= (const matrix_ &_m);
	inline const matrix_ operator * (_Type _s) const;
	inline matrix_& operator *= (_Type _s);
	inline const matrix_ operator / (_Type _s) const;
	inline matrix_& operator /= (_Type _s);
	inline void add(const matrix_ &_b, matrix_ &_c) const;
	inline void sub(const matrix_ &_b, matrix_ &_c) const;
	inline void mul(_Type _s, matrix_ &_c) const;
	inline void div(_Type _s, matrix_ &_c) const;
private:
	row_type m_row;
};
template<uint _Width, typename _Type>
struct matrix_<0, _Width, _Type> {
	inline void add(const matrix_ &_b, matrix_ &_c) const {}
	inline void sub(const matrix_ &_b, matrix_ &_c) const {}
	inline void mul(_Type _s, matrix_ &_c) const {}
	inline void div(_Type _s, matrix_ &_c) const {}
};

//// vector
//template<uint _Dimention, typename _Type = real> struct vector_ : vector_<_Dimention - 1, _Type> {
//	static const uint dimention = _Dimention;
//	static const uint last = dimention - 1;
//	typedef _Type type;
//	inline vector_();
//	inline vector_(const vector_ &_v);
//	inline vector_(const vector_<_Dimention - 1, _Type> &_v);
//	inline vector_(_Type _cell0);
//	inline vector_(_Type _cell0, _Type _cell1);
//	inline vector_(_Type _cell0, _Type _cell1, _Type _cell2);
//	inline vector_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
//	inline const _Type& cell() const;
//	inline _Type& cell();
//	template<uint _I> inline const _Type& cell() const;
//	template<uint _I> inline _Type& cell();
//	inline const _Type operator [] (uint _i) const;
//	inline _Type& operator [] (uint _i);
//	inline vector_& operator = (const vector_ &_v);
//	inline const vector_ operator + (const vector_ &_v) const;
//	inline vector_& operator += (const vector_ &_v);
//	inline const vector_ operator - (const vector_ &_v) const;
//	inline vector_& operator -= (const vector_ &_v);
//	inline const vector_ operator * (_Type _s) const;
//	inline vector_& operator *= (_Type _s);
//	inline const vector_ operator / (_Type _s) const;
//	inline vector_& operator /= (_Type _s);
//private:
//	type m_cell;
//};
//template<typename _Type> struct vector_<0, _Type> {
//	typedef _Type type;
//	inline vector_() {}
//	inline vector_(const vector_ &_v) {}
//	inline const _Type operator [] (uint _i) const {}
//	inline _Type& operator [] (uint _i) {}
//	inline vector_& operator = (const vector_ &_v) { return *this; }
//	inline const vector_ operator + (const vector_ &_v) const { return *this; }
//	inline vector_& operator += (const vector_ &_v) { return *this; }
//	inline const vector_ operator - (const vector_ &_v) const { return *this; }
//	inline vector_& operator -= (const vector_ &_v) { return *this; }
//	inline const vector_ operator * (_Type _s) const { return *this; }
//	inline vector_& operator *= (_Type _s) { return *this; }
//	inline const vector_ operator / (_Type _s) const { return *this; }
//	inline vector_& operator /= (_Type _s) {}
//};

typedef matrix_<1, 2, real> real2;
typedef matrix_<1, 3, real> real3;
typedef matrix_<1, 4, real> real4;
typedef matrix_<3, 3, real> real3x3;
typedef matrix_<4, 3, real> real4x3;
typedef matrix_<4, 4, real> real4x4;

const real2 r2_0(r_0, r_0);
const real2 r2_1(r_1, r_1);
const real2 r2_x(r_1, r_0);
const real2 r2_y(r_0, r_1);
const real3 r3_0(r_0, r_0, r_0);
const real3 r3_1(r_1, r_1, r_1);
const real3 r3_x(r_1, r_0, r_0);
const real3 r3_y(r_0, r_1, r_0);
const real3 r3_z(r_0, r_0, r_1);
const real4 r4_0(r_0, r_0, r_0, r_0);
const real4 r4_1(r_1, r_1, r_1, r_1);
const real4 r4_x(r_1, r_0, r_0, r_0);
const real4 r4_y(r_0, r_1, r_0, r_0);
const real4 r4_z(r_0, r_0, r_1, r_0);
const real4 r4_w(r_0, r_0, r_0, r_1);
const real4 q_1(r_0, r_0, r_0, r_1);
const real3x3 r3x3_0(r3_0, r3_0, r3_0);
const real3x3 r3x3_1(r3_x, r3_y, r3_z);
const real4x3 r4x3_0(r3_0, r3_0, r3_0, r3_0);
const real4x3 r4x3_1(r3_x, r3_y, r3_z, r3_0);
const real4x4 r4x4_0(r4_0, r4_0, r4_0, r4_0);
const real4x4 r4x4_1(r4_x, r4_y, r4_z, r4_w);

// v2
template<typename _Type, bool _Const = false> struct v2_r_ {
	typedef typename select<_Const, const _Type, _Type>::type type;
	typedef typename select<_Const, const matrix_<1, 2, _Type>, matrix_<1, 2, _Type> >::type vector;
	type &x, &y;
	inline v2_r_(vector &_v);
};
template<typename _Type> v2_r_<_Type, false> v2(typename v2_r_<_Type, false>::vector &_v);
template<typename _Type> v2_r_<_Type, true> v2(typename v2_r_<_Type, true>::vector &_v);
typedef v2_r_<real> v2_r;

// v3
template<typename _Type, bool _Const = false> struct v3_r_ {
	typedef typename select<_Const, const _Type, _Type>::type type;
	typedef typename select<_Const, const matrix_<1, 3, _Type>, matrix_<1, 3, _Type> >::type vector;
	type &x, &y, &z;
	inline v3_r_(vector &_v);
};
template<typename _Type> v3_r_<_Type, false> v3(typename v3_r_<_Type, false>::vector &_v);
template<typename _Type> v3_r_<_Type, true> v3(typename v3_r_<_Type, true>::vector &_v);
typedef v3_r_<real> v3_r;

// v4
template<typename _Type, bool _Const = false> struct v4_r_ {
	typedef typename select<_Const, const _Type, _Type>::type type;
	typedef typename select<_Const, const matrix_<1, 4, _Type>, matrix_<1, 4, _Type> >::type vector;
	type &x, &y, &z, &w;
	inline v4_r_(vector &_v);
};
template<typename _Type> v4_r_<_Type, false> v4(typename v4_r_<_Type, false>::vector &_v);
template<typename _Type> v4_r_<_Type, true> v4(typename v4_r_<_Type, true>::vector &_v);
typedef v4_r_<real> v4_r;

// quat
template<typename _Type, bool _Const = false> struct quat_r_ {
	typedef typename select<_Const, const _Type, _Type>::type type;
	typedef typename select<_Const, const matrix_<1, 4, _Type>, matrix_<1, 4, _Type> >::type vector;
	type &i, &j, &k, &r;
	inline quat_r_(vector &_v);
};
template<typename _Type> quat_r_<_Type, false> quat(typename quat_r_<_Type, false>::vector &_v);
template<typename _Type> quat_r_<_Type, true> quat(typename quat_r_<_Type, true>::vector &_v);
typedef quat_r_<real> quat_r;




//// matrix
//template<uint _Height, uint _Width, typename _Type = real> struct matrix_ : vector_<_Height, vector_<_Width, _Type> > {
//	static const uint height = _Height;
//	static const uint width = _Width;
//	typedef _Type type;
//	typedef vector_<_Width, _Type> vector;
//	inline matrix_();
//	//inline matrix_(const matrix_ &_m);
//	//inline matrix_(const matrix_<_Height - 1, _Width, _Type> &_m);
//	inline const vector& row() const;
//	inline vector& row();
//	template<uint _I> inline const vector& row() const;
//	template<uint _I> inline vector& row();
//	template<uint _I, uint _J> inline const _Type& cell() const;
//	template<uint _I, uint _J> inline _Type& cell();
//
//	//inline const vector& operator [] (uint _i) const;
//	//inline vector& operator [] (uint _i);
//	//inline matrix_& operator = (const matrix_ &_v);
//	//inline const matrix_ operator + (const matrix_ &_v) const;
//	//inline matrix_& operator += (const matrix_ &_v);
//	//inline const matrix_ operator - (const matrix_ &_v) const;
//	//inline matrix_& operator -= (const matrix_ &_v);
//	//inline const matrix_ operator * (_Type _s) const;
//	//inline matrix_& operator *= (_Type _s);
//	//inline const matrix_ operator / (_Type _s) const;
//	//inline matrix_& operator /= (_Type _s);
////protected:
////	vector m_row;
//};

//typedef matrix_<3, 3, real> real3x3;
//typedef matrix_<4, 4, real> real4x4;
//typedef matrix_<4, 3, real> real4x3;

#include "math.inl"
