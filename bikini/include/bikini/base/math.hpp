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

// vector
template<uint _Dimention, typename _Real = real> struct vector_ : vector_<_Dimention - 1, _Real> {
	static const uint dimention = _Dimention;
	static const uint last = dimention - 1;
	typedef _Real real;
	inline vector_();
	inline vector_(const vector_ &_v);
	inline vector_(const vector_<_Dimention - 1, real> &_v);
	inline const real cell() const;
	inline real& cell();
	template<uint _I> inline const real cell() const;
	template<uint _I> inline real& cell();
	inline const real operator [] (uint _i) const;
	inline real& operator [] (uint _i);
	inline vector_& operator = (const vector_ &_v);
	inline const vector_ operator + (const vector_ &_v) const;
	inline vector_& operator += (const vector_ &_v);
	inline const vector_ operator - (const vector_ &_v) const;
	inline vector_& operator -= (const vector_ &_v);
	inline const vector_ operator * (real _s) const;
	inline vector_& operator *= (real _s);
	inline const vector_ operator / (real _s) const;
	inline vector_& operator /= (real _s);
private:
	real m_cell;
};
template<typename _Real> struct vector_<0, _Real> {
	typedef _Real real;
	inline vector_() {}
	inline vector_(const vector_ &_v) {}
	inline const real operator [] (uint _i) const {}
	inline real& operator [] (uint _i) {}
	inline vector_& operator = (const vector_ &_v) { return *this; }
	inline const vector_ operator + (const vector_ &_v) const { return *this; }
	inline vector_& operator += (const vector_ &_v) { return *this; }
	inline const vector_ operator - (const vector_ &_v) const { return *this; }
	inline vector_& operator -= (const vector_ &_v) { return *this; }
	inline const vector_ operator * (real _s) const { return *this; }
	inline vector_& operator *= (real _s) { return *this; }
	inline const vector_ operator / (real _s) const { return *this; }
	inline vector_& operator /= (real _s) {}
};

// vector2
template<typename _Real = real> struct vector2_ : vector_<2, _Real> {
	real &x, &y;
	inline vector2_();
	inline vector2_(real _x, real _y);
	template<uint _D> inline vector2_(const vector_<_D, _Real> &_v);
	template<uint _D> inline vector2_& operator = (const vector_<_D, _Real> &_v);
};

typedef vector2_<real> vector2;

const vector2 v2_0(r_0, r_0), v2_1(r_1, r_1), v2_x(r_1, r_0), v2_y(r_0, r_1);

// vector3
template<typename _Real = real> struct vector3_ : vector_<3, _Real> {
	real &x, &y, &z;
	inline vector3_();
	inline vector3_(real _x, real _y, real _z);
	template<uint _D> inline vector3_(const vector_<_D, _Real> &_v);
	template<uint _D> inline vector3_& operator = (const vector_<_D, _Real> &_v);
};

typedef vector3_<real> vector3;

const vector3 v3_0(r_0, r_0, r_0), v3_1(r_1, r_1, r_1), v3_x(r_1, r_0, r_0), v3_y(r_0, r_1, r_0), v3_z(r_0, r_0, r_1);

// matrix
template<uint _Height, uint _Width, typename _Real = real> struct matrix_ : matrix_<_Height - 1, _Width, _Real> {
	static const uint height = _Height;
	static const uint width = _Width;
	typedef _Real real;
	typedef vector_<_Width, _Real> vector;
	inline matrix_();
	inline const vector& row() const;
	inline vector& row();
	template<uint _I> inline const vector& row() const;
	template<uint _I> inline vector& row();
protected:
	vector m_row;
};
template<uint _Width, typename _Real> struct matrix_<0, _Width, _Real> {
};

// matrix3
template<typename _Real = real> struct matrix3_ : matrix_<3, 3, _Real> {
	real &m11, &m12, &m13;
	real &m21, &m22, &m23;
	real &m31, &m32, &m33;
	inline matrix3_();
	inline matrix3_(
		real _m11, real _m12, real _m13,
		real _m21, real _m22, real _m23,
		real _m31, real _m32, real _m33
	);
};

typedef matrix3_<real> matrix3;

#include "math.inl"
