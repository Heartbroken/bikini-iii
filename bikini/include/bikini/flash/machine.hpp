/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine {
	bool do_ABC(pointer _data, uint _size);
private:
	//
	struct nsk { enum namespace_kind {
		Namespace			= 0x08,
		PackageNamespace	= 0x16,
		PackageInternalNs	= 0x17,
		ProtectedNamespace	= 0x18,
		ExplicitNamespace	= 0x19,
		StaticProtectedNs	= 0x1A,
		PrivateNs			= 0x05,
	};};
	struct ns {
		nsk::namespace_kind kind;
		uint string;
	};
	friend ns NAMESPACE(byte*&);
	typedef array_<ns> namespaces;
	//
	struct ns_set {
		uint_array nss;
	};
	friend ns_set NSSET(byte*&);
	typedef array_<ns_set> ns_sets;
	//
	struct mnk { enum multiname_kind {
		QName		= 0x07,
		QNameA		= 0x0D,
		RTQName		= 0x0F,
		RTQNameA	= 0x10,
		RTQNameL	= 0x11,
		RTQNameLA	= 0x12,
		Multiname	= 0x09,
		MultinameA	= 0x0E,
		MultinameL	= 0x1B,
		MultinameLA	= 0x1C,
	};};
	struct multiname {
		mnk::multiname_kind kind;
		uint ns, name, ns_set;
	};
	friend multiname MULTINAME(byte*&);
	typedef array_<multiname> multinames;
	//
	struct segment {
		segment(machine &_machine, pointer _data, uint _size);
	private:
		machine &m_machine;
		uint_array m_int_map, m_uint_map, m_double_map, m_string_map;
		uint_array m_namespace_map, m_ns_set_map, m_multiname_map;
	};
	typedef array_<segment> segments;
	sint_array m_ints;
	uint_array m_uints;
	rbig_array m_doubles;
	wstring_array m_strings;
	segments m_segments;
};
