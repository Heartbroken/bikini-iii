// test_watch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct A
{
	int b;
	int get_c() { return m_c; }
	static int d;
	static int get_e() { return m_e; }
private:
	int m_c;
	static int m_e;
};
int A::d = 0;
int A::m_e = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	bk::watch l_watch;

	l_watch.add_type<A>("A")
		.add_member(&A::b, "b")
		.add_member(&A::get_c, "c")
		.add_member(&A::d, "d")
		.add_member(&A::get_e, "e")
	;

	return 0;
}

