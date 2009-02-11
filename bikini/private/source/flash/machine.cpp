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
static inline machine::ns NAMESPACE(byte* &_d) {
	machine::ns l_ns;
	l_ns.kind = (machine::nsk::namespace_kind)U8(_d);
	l_ns.string = U30(_d);
	return l_ns;
}
static inline machine::ns_set NSSET(byte* &_d) {
	machine::ns_set l_ns_set;
	uint l_count = U30(_d); l_ns_set.nss.resize(l_count);
	for(uint i = 0; i < l_count; ++i) l_ns_set.nss[i] = U32(_d);
	return l_ns_set;
}
static inline machine::multiname MULTINAME(byte* &_d) {
	machine::multiname l_multiname;
	l_multiname.kind = (machine::mnk::multiname_kind)U8(_d);
	l_multiname.ns = l_multiname.name = l_multiname.ns_set = 0;
	switch(l_multiname.kind) {
		case machine::mnk::QName :
		case machine::mnk::QNameA :
			l_multiname.ns = U30(_d); l_multiname.name = U30(_d);
			break;
		case machine::mnk::RTQName :
		case machine::mnk::RTQNameA :
			l_multiname.name = U30(_d);
			break;
		case machine::mnk::RTQNameL :
		case machine::mnk::RTQNameLA :
			break;
		case machine::mnk::Multiname :
		case machine::mnk::MultinameA :
			l_multiname.name = U30(_d); l_multiname.ns_set = U30(_d);
			break;
		case machine::mnk::MultinameL :
		case machine::mnk::MultinameLA :
			l_multiname.ns_set = U30(_d);
			break;
	};
	return l_multiname;
}
static inline machine::method METHOD(byte* &_d) {
	machine::method l_method;
	uint l_param_count = U30(_d);
	l_method.param_types.resize(l_param_count);
	l_method.param_names.resize(l_param_count);
	l_method.return_type = U30(_d);
	for(uint i = 0; i < l_param_count; ++i) l_method.param_types[i] = U30(_d);
	l_method.name = U30(_d);
	l_method.flags = U8(_d);
	uint l_option_count = U30(_d); l_method.options.resize(l_option_count);
	for(uint i = 0; i < l_option_count; ++i) {
		l_method.options[i].val = U30(_d);
		l_method.options[i].kind = (machine::method::option::mok::kind)U8(_d);
	}
	for(uint i = 0; i < l_param_count; ++i) l_method.param_names[i] = U30(_d);
	return l_method;
}
static inline machine::metadata METADATA(byte* &_d) {
	machine::metadata l_metadata;
	l_metadata.name = U30(_d);
	uint l_item_count = U30(_d); l_metadata.items.resize(l_item_count);
	for(uint i = 0; i < l_item_count; ++i) {
		l_metadata.items[i].key = U30(_d);
		l_metadata.items[i].value = U30(_d);
	}
	return l_metadata;
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
	uint l_namespace_count = U30(l_data);
	namespaces l_namespaces; if(l_namespace_count) while(--l_namespace_count) l_namespaces.push_back(NAMESPACE(l_data));
	uint l_ns_set_count = U30(l_data);
	ns_sets l_ns_sets; if(l_ns_set_count) while(--l_ns_set_count) l_ns_sets.push_back(NSSET(l_data));
	uint l_multiname_count = U30(l_data);
	multinames l_multinames; if(l_multiname_count) while(--l_multiname_count) l_multinames.push_back(MULTINAME(l_data));
	uint l_method_count = U30(l_data);
	methods l_methods; if(l_method_count) while(--l_method_count) l_methods.push_back(METHOD(l_data));
	uint l_metadata_count = U30(l_data);
	metadatas l_metadatas; if(l_metadata_count) while(--l_metadata_count) l_metadatas.push_back(METADATA(l_data));
	int a=0;
}

} /* namespace as -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
