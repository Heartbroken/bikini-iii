// test_watch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct A
{
	bk::sint2 b;
	void set_c(bk::sint2 _c) { m_c = _c; }
	bk::sint2 get_c() const { return m_c; }
	static bk::sint d;
	static bk::sint get_e() { return m_e; }
private:
	bk::sint2 m_c;
	static bk::sint m_e;
};
bk::sint A::d = 0;
bk::sint A::m_e = 0;

struct F : A
{
};

bk::sint2 get_g()
{
	return bk::sint2(3, 4);
}

int _tmain(int argc, _TCHAR* argv[])
{
	bk::watch l_watch;

	l_watch.add_type_<bk::sint>("sint");

	struct _sint2_helper {
		static inline bk::sint get_sint2_x(const bk::sint2 &_o) { return _o.x(); }
		static inline void set_sint2_x(bk::sint2 &_o, const bk::sint &_v) { _o.x() = _v; }
		static inline bk::sint get_sint2_y(const bk::sint2 &_o) { return _o.y(); }
		static inline void set_sint2_y(bk::sint2 &_o, const bk::sint &_v) { _o.y() = _v; }
	};
	l_watch.add_type_<bk::sint2>("sint2")
		.add_member(&_sint2_helper::get_sint2_x, "x")
		.add_member(&_sint2_helper::set_sint2_x, "x")
		.add_member(&_sint2_helper::get_sint2_y, "y")
		.add_member(&_sint2_helper::set_sint2_y, "y")
	;

	l_watch.add_type_<A>("A")
		.add_member(&A::b, "b")
		.add_member(&A::get_c, "c")
		.add_member(&A::set_c, "c")
		.add_member(&A::d, "d")
		.add_member(&A::get_e, "e")
	;

	l_watch.add_type_<F>("F")
		.add_base_<A>()
	;

	F f; f.b = bk::sint2(5, 6); f.set_c(bk::sint2(7, 8));
	bk::sint i = 2;

	bk::watch::varaible l_vi = l_watch.add_global(&i, "i");
	bk::watch::varaible l_vf = l_watch.add_global(&f, "f");
	bk::watch::varaible l_vg = l_watch.add_global(&get_g, "g");

	bk::sint i0 = l_vi.get_<bk::sint>();
	F f0 = l_vf.get_<F>();
	bk::sint2 g0 = l_vg.get_<bk::sint2>();

	bk::watch::varaible l_vf_c = l_vf["c"];

	bk::sint2 fc0 = l_vf_c.get_<bk::sint2>();

	bk::watch::varaible l_vf_c_x = l_watch.find_varaible("f::c::x");

	bk::sint fb0 = l_vf_c_x.get_<bk::sint>();

	return 0;
}

