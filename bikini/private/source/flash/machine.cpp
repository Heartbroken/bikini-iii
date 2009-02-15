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
static inline uint U8(const byte* &_d) {
	u8 l_v = *(u8*)_d; _d += sizeof(u8);
	return uint(l_v);
}
static inline uint U16(const byte* &_d) {
	u16 l_v = *(u16*)_d; _d += sizeof(u16);
	return uint(l_v);
}
static inline sint S16(const byte* &_d) {
	byte l_b0 = *(_d++), l_b1 = *(_d++), l_b2 = *(_d++);
	return sint(l_b0) | sint(l_b1 << 8) | sint(l_b2 << 16) | ((l_b2 & 0x80) ? sint(0xff << 24) : sint(0x00 << 24));
}
static inline uint U30(const byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint U32(const byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint S32(const byte* &_d) {
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
static inline rbig F64(const byte* &_d) {
	f64 l_v = *(f64*)_d; _d += sizeof(f64);
	return rbig(l_v);
}
static inline wstring STRING(const byte* &_d) {
	uint l_s0 = U30(_d);
	uint l_s1 = MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, 0, 0);
	wchar* l_w = (wchar*)calloc(l_s1, sizeof(wchar*));
	MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, l_w, (int)l_s1); _d += l_s0;
	return wstring(l_w, l_s1);
}
static inline machine::ns NAMESPACE(const byte* &_d) {
	machine::ns l_ns;
	l_ns.kind = (machine::ns::nsk::namespace_kind)U8(_d);
	l_ns.string = U30(_d);
	return l_ns;
}
static inline machine::ns_set NSSET(const byte* &_d) {
	machine::ns_set l_ns_set;
	uint l_count = U30(_d); l_ns_set.nss.resize(l_count);
	for(uint i = 0; i < l_count; ++i) l_ns_set.nss[i] = U32(_d);
	return l_ns_set;
}
static inline machine::multiname MULTINAME(const byte* &_d) {
	machine::multiname l_multiname;
	l_multiname.kind = (machine::multiname::mnk::multiname_kind)U8(_d);
	l_multiname.ns = l_multiname.name = l_multiname.ns_set = 0;
	switch(l_multiname.kind) {
		case machine::multiname::mnk::QName :
		case machine::multiname::mnk::QNameA :
			l_multiname.ns = U30(_d); l_multiname.name = U30(_d);
			break;
		case machine::multiname::mnk::RTQName :
		case machine::multiname::mnk::RTQNameA :
			l_multiname.name = U30(_d);
			break;
		case machine::multiname::mnk::RTQNameL :
		case machine::multiname::mnk::RTQNameLA :
			break;
		case machine::multiname::mnk::Multiname :
		case machine::multiname::mnk::MultinameA :
			l_multiname.name = U30(_d); l_multiname.ns_set = U30(_d);
			break;
		case machine::multiname::mnk::MultinameL :
		case machine::multiname::mnk::MultinameLA :
			l_multiname.ns_set = U30(_d);
			break;
	};
	return l_multiname;
}
static inline machine::method METHOD(const byte* &_d) {
	machine::method l_method;
	uint l_param_count = U30(_d);
	l_method.return_type = U30(_d);
	l_method.param_types.resize(l_param_count);
	for(uint i = 0; i < l_param_count; ++i) l_method.param_types[i] = U30(_d);
	l_method.name = U30(_d);
	l_method.flags = U8(_d);
	if(l_method.flags & machine::method::mf::HAS_OPTIONAL) {
		uint l_option_count = U30(_d); l_method.options.resize(l_option_count);
		for(uint i = 0; i < l_option_count; ++i) {
			l_method.options[i].val = U30(_d);
			l_method.options[i].kind = (machine::method::option::mok::kind)U8(_d);
		}
	}
	if(l_method.flags & machine::method::mf::HAS_PARAM_NAMES) {
		l_method.param_names.resize(l_param_count);
		for(uint i = 0; i < l_param_count; ++i) l_method.param_names[i] = U30(_d);
	}
	return l_method;
}
static inline machine::metadata METADATA(const byte* &_d) {
	machine::metadata l_metadata;
	l_metadata.name = U30(_d);
	uint l_item_count = U30(_d); l_metadata.items.resize(l_item_count);
	for(uint i = 0; i < l_item_count; ++i) {
		l_metadata.items[i].key = U30(_d);
		l_metadata.items[i].value = U30(_d);
	}
	return l_metadata;
}
static inline machine::trait TRAIT(const byte* &_d) {
	machine::trait l_trait;
	l_trait.name = U30(_d);
	l_trait.kind = U8(_d);
	switch(l_trait.kind & 0xf) {
		case machine::trait::itt::Slot :
		case machine::trait::itt::Const :
			l_trait.slot_id = U30(_d);
			l_trait.type_name = U30(_d);
			l_trait.vindex = U30(_d);
			l_trait.vkind = U8(_d);
			break;
		case machine::trait::itt::Class :
			l_trait.slot_id = U30(_d);
			l_trait.classi = U30(_d);
			break;
		case machine::trait::itt::Function :
			l_trait.slot_id = U30(_d);
			l_trait.function = U30(_d);
			break;
		case machine::trait::itt::Method :
		case machine::trait::itt::Getter :
		case machine::trait::itt::Setter :
			l_trait.disp_id = U30(_d);
			l_trait.method = U30(_d);
			break;
	}
	return l_trait;
}
static inline machine::instance INSTANCE(const byte* &_d) {
	machine::instance l_instance;
	l_instance.name = U30(_d);
	l_instance.super_name = U30(_d);
	l_instance.flags = U8(_d);
	l_instance.protected_ns = U30(_d);
	uint l_intrf_count = U30(_d); l_instance.interfaces.resize(l_intrf_count);
	for(uint i = 0; i < l_intrf_count; ++i) l_instance.interfaces[i] = U30(_d);
	l_instance.iinit = U30(_d);
	uint l_trait_count = U30(_d); l_instance.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_instance.traits[i] = TRAIT(_d);
	return l_instance;
}
static inline machine::classinfo CLASS(const byte* &_d) {
	machine::classinfo l_classinfo;
	l_classinfo.cinit = U30(_d);
	uint l_trait_count = U30(_d); l_classinfo.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_classinfo.traits[i] = TRAIT(_d);
	return l_classinfo;
}
static inline machine::script SCRIPT(const byte* &_d) {
	machine::script l_script;
	l_script.init = U30(_d);
	uint l_trait_count = U30(_d); l_script.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_script.traits[i] = TRAIT(_d);
	return l_script;
}
static inline machine::methodbody METHODBODY(const byte* &_d) {
	machine::methodbody l_methodbody;
	l_methodbody.method = U30(_d);
	l_methodbody.max_stack = U30(_d);
	l_methodbody.local_count = U30(_d);
	l_methodbody.init_scope_depth = U30(_d);
	l_methodbody.max_scope_depth = U30(_d);
	uint l_code_length = U30(_d); l_methodbody.code.resize(l_code_length);
	for(uint i = 0; i < l_code_length; ++i) l_methodbody.code[i] = (byte)U8(_d);
	uint l_exception_count = U30(_d); l_methodbody.exceptions.resize(l_exception_count);
	for(uint i = 0; i < l_exception_count; ++i) {
		machine::methodbody::exception &l_exception = l_methodbody.exceptions[i];
		l_exception.from = U30(_d);
		l_exception.to = U30(_d);
		l_exception.target = U30(_d);
		l_exception.exc_type = U30(_d);
		l_exception.var_name = U30(_d);
	}
	uint l_trait_count = U30(_d); l_methodbody.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_methodbody.traits[i] = TRAIT(_d);
	return l_methodbody;
}
//

bool machine::do_ABC(pointer _data, uint _size) {
	segment l_segment(*this, _data, _size);
	l_segment.run(0);
	return true;
}
void machine::map_ints(const sint* _ints, uint* _map, uint _count) {
	for(uint i = 0; i < _count; ++i) {
		sint l_int = _ints[i];
		uint &l_index = _map[i]; l_index = bad_ID;
		for(uint i = 0, s = m_ints.size(); i < s; ++i) {
			if(l_int == m_ints[i]) { l_index = i; break; }
		}
		if(l_index == bad_ID) {
			l_index = m_ints.size();
			m_ints.push_back(l_int);
		}
	}
}
void machine::map_uints(const uint* _uints, uint* _map, uint _count) {
	for(uint i = 0; i < _count; ++i) {
		uint l_uint = _uints[i];
		uint &l_index = _map[i]; l_index = bad_ID;
		for(uint i = 0, s = m_uints.size(); i < s; ++i) {
			if(l_uint == m_uints[i]) { l_index = i; break; }
		}
		if(l_index == bad_ID) {
			l_index = m_uints.size();
			m_uints.push_back(l_uint);
		}
	}
}
void machine::map_doubles(const rbig* _doubles, uint* _map, uint _count) {
	for(uint i = 0; i < _count; ++i) {
		rbig l_double = _doubles[i];
		uint &l_index = _map[i]; l_index = bad_ID;
		for(uint i = 0, s = m_doubles.size(); i < s; ++i) {
			if(l_double == m_doubles[i]) { l_index = i; break; }
		}
		if(l_index == bad_ID) {
			l_index = m_doubles.size();
			m_doubles.push_back(l_double);
		}
	}
}
void machine::map_strings(const wstring* _strings, uint* _map, uint _count) {
	for(uint i = 0; i < _count; ++i) {
		const wstring &l_string = _strings[i];
		uint &l_index = _map[i]; l_index = bad_ID;
		for(uint i = 0, s = m_strings.size(); i < s; ++i) {
			if(l_string == m_strings[i]) { l_index = i; break; }
		}
		if(l_index == bad_ID) {
			l_index = m_strings.size();
			m_strings.push_back(l_string);
		}
	}
}

// machine::segment

machine::segment::segment(machine &_machine, pointer _data, uint _size) : m_machine(_machine) {
	const byte* l_data = (byte*)_data;
	uint l_minor = U16(l_data);
	uint l_major = U16(l_data);
	if(l_major > 46) {
		std::cerr << "ERROR: Wrong ActionScript 3.0 Byte Code version. Version 46.16 is expected\n";
		return;
	}
	// int constants
	uint l_int_count = U30(l_data); if(l_int_count > 0) --l_int_count;
	sint_array l_ints; l_ints.resize(l_int_count); m_int_map.resize(l_int_count);
	for(uint i = 0; i < l_int_count; ++i) l_ints[i] = S32(l_data);
	if(l_int_count > 0) m_machine.map_ints(&l_ints[0], &m_int_map[0], l_int_count);
	// uint constants
	uint l_uint_count = U30(l_data); if(l_uint_count > 0) --l_uint_count;
	uint_array l_uints; l_uints.resize(l_uint_count); m_uint_map.resize(l_uint_count);
	for(uint i = 0; i < l_uint_count; ++i) l_uints[i] = U32(l_data);
	if(l_uint_count > 0) m_machine.map_uints(&l_uints[0], &m_uint_map[0], l_uint_count);
	// double constants
	uint l_double_count = U30(l_data); if(l_double_count > 0) --l_double_count;
	rbig_array l_doubles; l_doubles.resize(l_double_count); m_double_map.resize(l_double_count);
	for(uint i = 0; i < l_double_count; ++i) l_doubles[i] = F64(l_data);
	if(l_double_count > 0) m_machine.map_doubles(&l_doubles[0], &m_double_map[0], l_double_count);
	// string constants
	uint l_string_count = U30(l_data); if(l_string_count > 0) --l_string_count;
	wstring_array l_strings; l_strings.resize(l_string_count); m_string_map.resize(l_string_count);
	for(uint i = 0; i < l_string_count; ++i) l_strings[i] = STRING(l_data);
	if(l_string_count > 0) m_machine.map_strings(&l_strings[0], &m_string_map[0], l_string_count);
	// namespace constants
	uint l_namespace_count = U30(l_data); if(l_namespace_count > 0) --l_namespace_count;
	/*namespaces l_namespaces;*/ m_namespaces.resize(l_namespace_count);
	for(uint i = 0; i < l_namespace_count; ++i) m_namespaces[i] = NAMESPACE(l_data);
	// ns_set constants
	uint l_ns_set_count = U30(l_data); if(l_ns_set_count > 0) --l_ns_set_count;
	/*ns_sets l_ns_sets;*/ m_ns_sets.resize(l_ns_set_count);
	for(uint i = 0; i < l_ns_set_count; ++i) m_ns_sets[i] = NSSET(l_data);
	// multiname constants
	uint l_multiname_count = U30(l_data); if(l_multiname_count > 0) --l_multiname_count;
	/*multinames l_multinames;*/ m_multinames.resize(l_multiname_count);
	for(uint i = 0; i < l_multiname_count; ++i) m_multinames[i] = MULTINAME(l_data);
	// methods
	uint l_method_count = U30(l_data);
	/*methods l_methods;*/ m_methods.resize(l_method_count);
	for(uint i = 0; i < l_method_count; ++i) m_methods[i] = METHOD(l_data);
	// metadata
	uint l_metadata_count = U30(l_data);
	metadatas l_metadatas; l_metadatas.resize(l_metadata_count);
	for(uint i = 0; i < l_metadata_count; ++i) l_metadatas[i] = METADATA(l_data);
	// classes
	uint l_class_count = U30(l_data);
	/*instances l_instances;*/ m_instances.resize(l_class_count);
	for(uint i = 0; i < l_class_count; ++i) m_instances[i] = INSTANCE(l_data);
	/*classinfos l_classinfos;*/ m_classinfos.resize(l_class_count);
	for(uint i = 0; i < l_class_count; ++i) m_classinfos[i] = CLASS(l_data);
	// scripts
	uint l_script_count = U30(l_data);
	/*scripts l_scripts;*/ m_scripts.resize(l_script_count);
	for(uint i = 0; i < l_script_count; ++i) m_scripts[i] = SCRIPT(l_data);
	// methods bodies
	uint l_methodbody_count = U30(l_data);
	/*methodbodys l_methodbodys;*/ m_methodbodys.resize(l_methodbody_count);
	for(uint i = 0; i < l_methodbody_count; ++i) m_methodbodys[i] = METHODBODY(l_data);
	//
	int a=0;
	//// test
	//if(!m_scripts.empty()) {
	//	uint l_s = m_scripts.back().init;
	//	if(l_s < m_methodbodys.size()) {
	//		const byte* l_d = &m_methodbodys[l_s].code[0];
	//		bool l_run = true;
	//		while(l_run) {
	//			opcode::opcodes l_code = (opcode::opcodes)U8(l_d);
	//			switch(l_code) {
	//				case opcode::getlocal_0 : {
	//				} break;
	//				case opcode::pushscope : {
	//				} break;
	//				case opcode::getscopeobject : {
	//					uint l_index = U8(l_d);
	//				} break;
	//				case opcode::getlex : {
	//					uint l_index = U8(l_d);
	//				} break;
	//				default:
	//					l_run = false;
	//			}
	//		}
	//	}
	//}
}
void machine::segment::run(uint _method) {
	if(_method >= m_methodbodys.size()) return;
	const byte* l_code = &m_methodbodys[_method].code[0];
	bool l_run = true;
	while(l_run) {
		opcode::opcodes l_op = (opcode::opcodes)U8(l_code);
		switch(l_op) {
			case opcode::add : {} break;
			case opcode::add_i : {} break;
			case opcode::astype : {} break;
			case opcode::astypelate : {} break;
			case opcode::bitand : {} break;
			case opcode::bitnot : {} break;
			case opcode::bitor : {} break;
			case opcode::bitxor : {} break;
			case opcode::call : {} break;
			case opcode::callmethod : {} break;
			case opcode::callproperty : {} break;
			case opcode::callproplex : {} break;
			case opcode::callpropvoid : {} break;
			case opcode::callstatic : {} break;
			case opcode::callsuper : {} break;
			case opcode::callsupervoid : {} break;
			case opcode::checkfilter : {} break;
			case opcode::coerce : {} break;
			case opcode::coerce_a : {} break;
			case opcode::coerce_s : {} break;
			case opcode::construct : {} break;
			case opcode::constructprop : {} break;
			case opcode::constructsuper : {} break;
			case opcode::convert_b : {} break;
			case opcode::convert_i : {} break;
			case opcode::convert_d : {} break;
			case opcode::convert_o : {} break;
			case opcode::convert_u : {} break;
			case opcode::convert_s : {} break;
			case opcode::debug : {} break;
			case opcode::debugfile : {} break;
			case opcode::debugline : {} break;
			case opcode::declocal : {} break;
			case opcode::declocal_i : {} break;
			case opcode::decrement : {} break;
			case opcode::decrement_i : {} break;
			case opcode::deleteproperty : {} break;
			case opcode::divide : {} break;
			case opcode::dup : {} break;
			case opcode::dxns : {} break;
			case opcode::dxnslate : {} break;
			case opcode::equals : {} break;
			case opcode::esc_xattr : {} break;
			case opcode::esc_xelem : {} break;
			case opcode::findproperty : {} break;
			case opcode::findpropstrict : {} break;
			case opcode::getdescendants : {} break;
			case opcode::getglobalscope : {} break;
			case opcode::getglobalslot : {} break;
			case opcode::getlex : {
				uint l_index = U8(l_code);
			} break;
			case opcode::getlocal : {} break;
			case opcode::getlocal_0 : {} break;
			case opcode::getlocal_1 : {} break;
			case opcode::getlocal_2 : {} break;
			case opcode::getlocal_3 : {} break;
			case opcode::getproperty : {} break;
			case opcode::getscopeobject : {
				uint l_index = U8(l_code);
			} break;
			case opcode::getslot : {} break;
			case opcode::getsuper : {} break;
			case opcode::greaterequals : {} break;
			case opcode::greaterthan : {} break;
			case opcode::hasnext : {} break;
			case opcode::hasnext2 : {} break;
			case opcode::ifeq : {} break;
			case opcode::iffalse : {} break;
			case opcode::ifge : {} break;
			case opcode::ifgt : {} break;
			case opcode::ifle : {} break;
			case opcode::iflt : {} break;
			case opcode::ifnge : {} break;
			case opcode::ifngt : {} break;
			case opcode::ifnle : {} break;
			case opcode::ifnlt : {} break;
			case opcode::ifne : {} break;
			case opcode::ifstricteq : {} break;
			case opcode::ifstrictne : {} break;
			case opcode::iftrue : {} break;
			case opcode::in : {} break;
			case opcode::inclocal : {} break;
			case opcode::inclocal_i : {} break;
			case opcode::increment : {} break;
			case opcode::increment_i : {} break;
			case opcode::initproperty : {} break;
			case opcode::instanceof : {} break;
			case opcode::istype : {} break;
			case opcode::istypelate : {} break;
			case opcode::jump : {} break;
			case opcode::kill : {} break;
			case opcode::label : {} break;
			case opcode::lessequals : {} break;
			case opcode::lessthan : {} break;
			case opcode::lookupswitch : {} break;
			case opcode::lshift : {} break;
			case opcode::modulo : {} break;
			case opcode::multiply : {} break;
			case opcode::multiply_i : {} break;
			case opcode::negate : {} break;
			case opcode::negate_i : {} break;
			case opcode::newactivation : {} break;
			case opcode::newarray : {} break;
			case opcode::newcatch : {} break;
			case opcode::newclass : {} break;
			case opcode::newfunction : {} break;
			case opcode::newobject : {} break;
			case opcode::nextname : {} break;
			case opcode::nextvalue : {} break;
			case opcode::nop : {} break;
			case opcode::not : {} break;
			case opcode::pop : {} break;
			case opcode::popscope : {} break;
			case opcode::pushbyte : {} break;
			case opcode::pushdouble : {} break;
			case opcode::pushfalse : {} break;
			case opcode::pushint : {} break;
			case opcode::pushnamespace : {} break;
			case opcode::pushnan : {} break;
			case opcode::pushnull : {} break;
			case opcode::pushscope : {} break;
			case opcode::pushshort : {} break;
			case opcode::pushstring : {} break;
			case opcode::pushtrue : {} break;
			case opcode::pushuint : {} break;
			case opcode::pushundefined : {} break;
			case opcode::pushwith : {} break;
			case opcode::returnvalue : {
				l_run = false;
			} break;
			case opcode::returnvoid : {
				l_run = false;
			} break;
			case opcode::rshift : {} break;
			case opcode::setlocal : {} break;
			case opcode::setlocal_0 : {} break;
			case opcode::setlocal_1 : {} break;
			case opcode::setlocal_2 : {} break;
			case opcode::setlocal_3 : {} break;
			case opcode::setglobalslot : {} break;
			case opcode::setproperty : {} break;
			case opcode::setslot : {} break;
			case opcode::setsuper : {} break;
			case opcode::strictequals : {} break;
			case opcode::subtract : {} break;
			case opcode::subtract_i : {} break;
			case opcode::swap : {} break;
			case opcode::throw_ : {} break;
			case opcode::typeof : {} break;
			case opcode::urshift : {} break;
			default : {
				assert(0);
				l_run = false;
			}
		}
	}
}

} /* namespace as -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
