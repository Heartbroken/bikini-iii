/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace as { /*--------------------------------------------------------------------------------*/

//
static inline uint U8(byte* &_d) {
	u8 l_v = *(u8*)_d; _d += sizeof(u8);
	return uint(l_v);
}
static inline uint U16(byte* &_d) {
	u16 l_v = *(u16*)_d; _d += sizeof(u16);
	return uint(l_v);
}
static inline sint S16(byte* &_d) {
	byte l_b0 = *(_d++), l_b1 = *(_d++), l_b2 = *(_d++);
	return sint(l_b0) | sint(l_b1 << 8) | sint(l_b2 << 16) | ((l_b2 & 0x80) ? sint(0xff << 24) : sint(0x00 << 24));
}
static inline uint U30(byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint U32(byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint S32(byte* &_d) {
	sint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) {
			if((l_b & 0x40) != 0) l_v |= 0xffffff80 << l_s;
			return l_v;
		}
	}
	return l_v;
}
static inline rbig F64(byte* &_d) {
	f64 l_v = *(f64*)_d; _d += sizeof(f64);
	return rbig(l_v);
}
static inline wstring STRING(byte* &_d) {
	uint l_s0 = U30(_d);
	uint l_s1 = MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, 0, 0);
	wchar* l_w = (wchar*)calloc(l_s1, sizeof(wchar*));
	MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, l_w, (int)l_s1); _d += l_s0;
	return wstring(l_w, l_s1);
}
//

bool machine::do_ABC(pointer _data, uint _size) {
	segment l_segment(*this, _data, _size);
	return true;
}

// machine::segment

machine::segment::segment(machine &_machine, pointer _data, uint _size) : m_machine(_machine) {
	byte* l_data = (byte*)_data;
	uint l_minor = U16(l_data);
	uint l_major = U16(l_data);
	if(l_major > 46) {
		std::cerr << "ERROR: Wrong ActionScript 3.0 Byte Code version. Version 46.16 is expected\n";
		return;
	}
	uint l_int_count = U30(l_data);
	sint_array l_ints; if(l_int_count) while(--l_int_count) l_ints.push_back(S32(l_data));
	uint l_uint_count = U30(l_data);
	uint_array l_uints; if(l_uint_count) while(--l_uint_count) l_uints.push_back(U32(l_data));
	uint l_double_count = U30(l_data);
	rbig_array l_doubles; if(l_double_count) while(--l_double_count) l_doubles.push_back(F64(l_data));
	uint l_string_count = U30(l_data);
	wstring_array l_strings; if(l_string_count) while(--l_string_count) l_strings.push_back(STRING(l_data));
	int a=0;
}

} /* namespace as -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
