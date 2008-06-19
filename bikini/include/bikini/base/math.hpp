/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// constants

/// pi constant
const real pi = real(3.1415926535897932384626433832795);
/// very big real value
const real infinity = real(1e38);
/// very small real value
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
inline uint next_pow2(uint _a);
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

///	Uber-matrix row template. Used internally by matrix_ template.
/**	Each _matrix_row_<_Size, _Type> struct has one member varable m_cell of cell_type type,
 *	and also inherits _Size - 1 cells from it's parent type _matrix_row_<_Size - 1, _Type>
 */
template<uint _Size, typename _Type>
struct _matrix_row_ : _matrix_row_<_Size - 1, _Type> {
	/// parent type
	typedef _matrix_row_<_Size - 1, _Type> parent_type;
	/// cell type
	typedef _Type cell_type;
	/// constructor
	inline _matrix_row_();
	/// copy constructor
	inline _matrix_row_(const _matrix_row_ &_r);
	/// construct from parent type
	inline _matrix_row_(const parent_type &_r);
	/// one cell row constructor
	inline _matrix_row_(_Type _cell0);
	/// two cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1);
	/// three cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2);
	/// four cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	/// last cell accessor
	inline const _Type& cell() const;
	/// last cell accessor
	inline _Type& cell();
	/// i-th cell accessor
	template<uint _I> inline const _Type& cell() const;
	/// i-th cell accessor
	template<uint _I> inline _Type& cell();
	/// get i-th row cell
	inline const _Type& operator [] (uint _i) const;
	/// get i-th row cell
	inline _Type& operator [] (uint _i);
	// some aux functions
	inline void set(const _matrix_row_ &_b);
	inline void get(_matrix_row_ &_c) const;
	inline void neg(_matrix_row_ &_c) const;
	inline void add(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void sub(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void mul(_Type _s, _matrix_row_ &_c) const;
	inline void div(_Type _s, _matrix_row_ &_c) const;
private:
	cell_type m_cell;
};
template<typename _Type>
struct _matrix_row_<0, _Type> {
	inline void set(const _matrix_row_ &_b) {}
	inline void get(_matrix_row_ &_c) const {}
	inline void neg(_matrix_row_ &_c) const {}
	inline void add(const _matrix_row_&, _matrix_row_&) const {}
	inline void sub(const _matrix_row_&, _matrix_row_&) const {}
	inline void mul(_Type, _matrix_row_&) const {}
	inline void div(_Type, _matrix_row_&) const {}
};

///	Uber-matrix template
/**	This template is used for all matrices and vectors types.
 *	Each matrix_<_Height, _Width, _Type> struct has one member varable m_row of row_type type,
 *	and also inherits _Height - 1 rows from it's parent type matrix_<_Height - 1, _Width, _Type>
 */
template<uint _Height, uint _Width, typename _Type>
struct matrix_ : matrix_<_Height - 1, _Width, _Type> {
	/// parent type
	typedef matrix_<_Height - 1, _Width, _Type> parent_type;
	/// row type
	typedef _matrix_row_<_Width, _Type> row_type;
	/// cell type
	typedef _Type cell_type;
	/// constructor
	inline matrix_();
	/// copy constructor
	inline matrix_(const matrix_ &_m);
	/// construct from parent type
	inline matrix_(const parent_type &_m);
	/// one row with one cell matrix constructor
	inline matrix_(_Type _cell0);
	/// one row with two cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1);
	/// one row with three cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2);
	/// one row with four cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	/// one row same width matrix
	typedef matrix_<1, _Width, _Type> row_matrix;
	/// two rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1);
	/// three rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2);
	/// four rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2, const row_matrix &_row3);
	/// last row accessor
	inline const row_type& row() const;
	/// last row accessor
	inline row_type& row();
	/// i-th row accessor
	template<uint _I> inline const row_type& row() const;
	/// i-th row accessor
	template<uint _I> inline row_type& row();
	/// (i,j)-th cell accessor
	template<uint _I, uint _J> inline const _Type& cell() const;
	/// (i,j)-th cell accessor
	template<uint _I, uint _J> inline _Type& cell();
	/// get i-th matrix row
	inline const row_type& operator [] (uint _i) const;
	/// get i-th matrix row
	inline row_type& operator [] (uint _i);
	/// assign matrix
	inline matrix_& operator = (const matrix_ &_m);
	/// unary minus
	inline const matrix_ operator - () const;
	/// add
	inline const matrix_ operator + (const matrix_ &_m) const;
	/// add assign
	inline matrix_& operator += (const matrix_ &_m);
	/// subtract
	inline const matrix_ operator - (const matrix_ &_m) const;
	/// subtract assign
	inline matrix_& operator -= (const matrix_ &_m);
	/// multiply
	inline const matrix_ operator * (_Type _s) const;
	/// multiply assign
	inline matrix_& operator *= (_Type _s);
	/// divide
	inline const matrix_ operator / (_Type _s) const;
	/// divide assign
	inline matrix_& operator /= (_Type _s);
	/// multiply martices
	template<uint _W2> inline const matrix_<_Height, _W2, _Type> operator * (const matrix_<_Width, _W2, _Type> &_m) const;
	/// get transposed matrix
	inline const matrix_<_Width, _Height, _Type> operator ~ () const; // transpose
	// some aux functions
	inline void set(const matrix_ &_b);
	inline void get(matrix_ &_c) const;
	inline void neg(matrix_ &_c) const;
	inline void add(const matrix_ &_b, matrix_ &_c) const;
	inline void sub(const matrix_ &_b, matrix_ &_c) const;
	inline void mul(_Type _s, matrix_ &_c) const;
	inline void div(_Type _s, matrix_ &_c) const;
	template<uint _W2> inline void mul(const matrix_<_Width, _W2, _Type> &_b, matrix_<_Height, _W2, _Type> &_c) const;
	inline void mul(const _matrix_row_<_Height, _Type> &_b, _matrix_row_<_Width, _Type> &_c) const;
	template<uint _W2> inline void xgt(matrix_<_Width, _W2, _Type> &_b) const;
	template<uint _I> inline void cst(const _matrix_row_<_Height, _Type> &_b);
private:
	row_type m_row;
};
template<uint _Width, typename _Type>
struct matrix_<0, _Width, _Type> {
	inline void set(const matrix_ &_b) {}
	inline void get(matrix_ &_c) const {}
	inline void neg(matrix_ &_c) const {}
	inline void add(const matrix_ &_b, matrix_ &_c) const {}
	inline void sub(const matrix_ &_b, matrix_ &_c) const {}
	inline void mul(_Type _s, matrix_ &_c) const {}
	inline void div(_Type _s, matrix_ &_c) const {}
	template<uint _W2> inline void mul(const matrix_<_Width, _W2, _Type> &_b, matrix_<0, _W2, _Type> &_c) const {}
	inline void mul(const _matrix_row_<0, _Type> &_b, _matrix_row_<_Width, _Type> &_c) const {}
	template<uint _W2> inline void xgt(matrix_<_Width, _W2, _Type> &_b) const {}
	template<uint _I> inline void cst(const _matrix_row_<0, _Type> &_b) {}
};

/// matrix minor
template<uint _I, uint _J, uint _Size, typename _Type>
inline const matrix_<_Size - 1, _Size - 1, _Type> minor(const matrix_<_Size, _Size, _Type> &_m);

/// matrix determinant
template<uint _Size, typename _Type>
inline const _Type determinant(const matrix_<_Size, _Size, _Type> &_m);

/// 1x1 matrix type
typedef matrix_<1, 1, real> r1x1;
/// 1x2 matrix type
typedef matrix_<1, 2, real> r1x2;
/// 1x3 matrix type
typedef matrix_<1, 3, real> r1x3;
/// 1x4 matrix type
typedef matrix_<1, 4, real> r1x4;
/// 2x2 matrix type
typedef matrix_<2, 2, real> r2x2;
/// 3x3 matrix type
typedef matrix_<3, 3, real> r3x3;
/// 4x3 matrix type
typedef matrix_<4, 3, real> r4x3;
/// 4x4 matrix type
typedef matrix_<4, 4, real> r4x4;

/// zero 1x1 matrix
const r1x1 r1x1_0(r_0);
/// unit 1x1 matrix
const r1x1 r1x1_1(r_1);
/// [0 0] vector
const r1x2 r1x2_0(r_0, r_0);
/// [1 1] vector
const r1x2 r1x2_1(r_1, r_1);
/// [1 0] vector
const r1x2 r1x2_x(r_1, r_0);
/// [0 1] vector
const r1x2 r1x2_y(r_0, r_1);
/// [0 0 0] vector
const r1x3 r1x3_0(r_0, r_0, r_0);
/// [1 1 1] vector
const r1x3 r1x3_1(r_1, r_1, r_1);
/// [1 0 0] vector
const r1x3 r1x3_x(r_1, r_0, r_0);
/// [0 1 0] vector
const r1x3 r1x3_y(r_0, r_1, r_0);
/// [0 0 1] vector
const r1x3 r1x3_z(r_0, r_0, r_1);
/// [0 0 0 0] vector
const r1x4 r1x4_0(r_0, r_0, r_0, r_0);
/// [1 1 1 1] vector
const r1x4 r1x4_1(r_1, r_1, r_1, r_1);
/// [1 0 0 0] vector
const r1x4 r1x4_x(r_1, r_0, r_0, r_0);
/// [0 1 0 0] vector
const r1x4 r1x4_y(r_0, r_1, r_0, r_0);
/// [0 0 1 0] vector
const r1x4 r1x4_z(r_0, r_0, r_1, r_0);
/// [0 0 0 1] vector
const r1x4 r1x4_w(r_0, r_0, r_0, r_1);
/// zero 2x2 matrix
const r2x2 r2x2_0(r1x2_0, r1x2_0);
/// unit 2x2 matrix
const r2x2 r2x2_1(r1x2_x, r1x2_y);
/// zero 3x3 matrix
const r3x3 r3x3_0(r1x3_0, r1x3_0, r1x3_0);
/// unit 3x3 matrix
const r3x3 r3x3_1(r1x3_x, r1x3_y, r1x3_z);
/// zero 4x3 matrix
const r4x3 r4x3_0(r1x3_0, r1x3_0, r1x3_0, r1x3_0);
/// unit 4x3 matrix
const r4x3 r4x3_1(r1x3_x, r1x3_y, r1x3_z, r1x3_0);
/// zero 4x4 matrix
const r4x4 r4x4_0(r1x4_0, r1x4_0, r1x4_0, r1x4_0);
/// unit 4x4 matrix
const r4x4 r4x4_1(r1x4_x, r1x4_y, r1x4_z, r1x4_w);

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
template<typename _Vector> struct v3 {
	typedef typename select<
		traits<_Vector>::is_const,
		const typename _Vector::cell_type,
		typename _Vector::cell_type
	>::type type;
	type &x, &y, &z;
	inline v3(_Vector &_v);
};

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

#include "math.inl"
