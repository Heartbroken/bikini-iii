#include "header.hpp"

namespace bk { ////////////////////////////////////////////////////////////////////////////////////

void test() {
	vector2 a(v2_0), b(v3_1);
	vector2 c = a + b;
	c += v3_1;
	a = b - c;
	a -= b;
	matrix3 m3;
}

} // namespace bk /////////////////////////////////////////////////////////////////////////////////
