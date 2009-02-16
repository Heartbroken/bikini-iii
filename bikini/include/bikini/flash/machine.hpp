/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine {
	~machine();
	bool do_ABC(pointer _data, uint _size, bool _run = true);
private:
	//
	struct ns {
		struct nsk { enum namespace_kind {
			Namespace			= 0x08,
			PackageNamespace	= 0x16,
			PackageInternalNs	= 0x17,
			ProtectedNamespace	= 0x18,
			ExplicitNamespace	= 0x19,
			StaticProtectedNs	= 0x1A,
			PrivateNs			= 0x05,
		};};
		nsk::namespace_kind kind;
		uint string;
	};
	friend ns NAMESPACE(const byte*&);
	typedef array_<ns> namespaces;
	//
	struct ns_set {
		uint_array nss;
	};
	friend ns_set NSSET(const byte*&);
	typedef array_<ns_set> ns_sets;
	//
	struct multiname {
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
		mnk::multiname_kind kind;
		uint ns, name, ns_set;
	};
	friend multiname MULTINAME(const byte*&);
	typedef array_<multiname> multinames;
	//
	struct method {
		uint return_type;
		uint_array param_types;
		uint name;
		struct mf { enum flags {
			NEED_ARGUMENTS		= 0x01,
			NEED_ACTIVATION		= 0x02,
			NEED_REST			= 0x04,
			HAS_OPTIONAL		= 0x08,
			SET_DXNS			= 0x40,
			HAS_PARAM_NAMES		= 0x80,
		};};
		uint flags;
		struct option {
			struct mok { enum kind {
				Int					= 0x03,
				UInt				= 0x04,
				Double				= 0x06,
				Utf8				= 0x01,
				True				= 0x0B,
				False				= 0x0A,
				Null				= 0x0C,
				Undefined			= 0x00,
				Namespace			= 0x08,
				PackageNamespace	= 0x16,
				PackageInternalNs	= 0x17,
				ProtectedNamespace	= 0x18,
				ExplicitNamespace	= 0x19,
				StaticProtectedNs	= 0x1A,
				PrivateNs			= 0x05,
			};};
			mok::kind kind;
			uint val;
		};
		array_<option> options;
		uint_array param_names;
	};
	friend method METHOD(const byte*&);
	typedef array_<method> methods;
	//
	struct metadata {
		uint name;
		struct item {
			uint key, value;
		};
		array_<item> items;
	};
	friend metadata METADATA(const byte*&);
	typedef array_<metadata> metadatas;
	//
	struct trait {
		struct itt { enum types {
			Slot		= 0,
			Method		= 1,
			Getter		= 2,
			Setter		= 3,
			Class		= 4,
			Function	= 5,
			Const		= 6,
		};};
		uint name, kind;
		uint slot_id, type_name, vindex, vkind, classi, function, disp_id, method;
		uint_array metadata;
	};
	//
	struct instance {
		uint name, super_name;
		struct oif { enum flags {
			ClassSealed			= 0x01,
			ClassFinal			= 0x02,
			ClassInterface		= 0x04,
			ClassProtectedNs	= 0x08,
		};};
		uint flags;
		uint protected_ns;
		uint_array interfaces;
		uint iinit;
		array_<trait> traits;
	};
	friend trait TRAIT(const byte*&);
	friend instance INSTANCE(const byte*&);
	typedef array_<instance> instances;
	//
	struct classinfo {
		uint cinit;
		array_<trait> traits;
	};
	friend classinfo CLASS(const byte*&);
	typedef array_<classinfo> classinfos;
	//
	struct script {
		uint init;
		array_<trait> traits;
	};
	friend script SCRIPT(const byte*&);
	typedef array_<script> scripts;
	//
	struct methodbody {
		uint method, max_stack, local_count, init_scope_depth, max_scope_depth;
		byte_array code;
		struct exception { uint from, to, target, exc_type, var_name; };
		array_<exception> exceptions;
		array_<trait> traits;
	};
	friend methodbody METHODBODY(const byte*&);
	typedef array_<methodbody> methodbodys;
	struct opcode { enum opcodes {
		add				= 0xA0,
		add_i			= 0xC5,
		astype			= 0x86,
		astypelate		= 0x87,
		bitand			= 0xA8,
		bitnot			= 0x97,
		bitor			= 0xA9,
		bitxor			= 0xAA,
		call			= 0x41,
		callmethod		= 0x43,
		callproperty	= 0x46,
		callproplex		= 0x4C,
		callpropvoid	= 0x4F,
		callstatic		= 0x44,
		callsuper		= 0x45,
		callsupervoid	= 0x4E,
		checkfilter		= 0x78,
		coerce			= 0x80,
		coerce_a		= 0x82,
		coerce_s		= 0x85,
		construct		= 0x42,
		constructprop	= 0x4A,
		constructsuper	= 0x49,
		convert_b		= 0x76,
		convert_i		= 0x73,
		convert_d		= 0x75,
		convert_o		= 0x77,
		convert_u		= 0x74,
		convert_s		= 0x70,
		debug			= 0xEF,
		debugfile		= 0xF1,
		debugline		= 0xF0,
		declocal		= 0x94,
		declocal_i		= 0xC3,
		decrement		= 0x93,
		decrement_i		= 0xC1,
		deleteproperty	= 0x6A,
		divide			= 0xA3,
		dup				= 0x2A,
		dxns			= 0x06,
		dxnslate		= 0x07,
		equals			= 0xAB,
		esc_xattr		= 0x72,
		esc_xelem		= 0x71,
		findproperty	= 0x5E,
		findpropstrict	= 0x5D,
		getdescendants	= 0x59,
		getglobalscope	= 0x64,
		getglobalslot	= 0x6E,
		getlex			= 0x60,
		getlocal		= 0x62,
		getlocal_0		= 0xD0,
		getlocal_1		= 0xD1,
		getlocal_2		= 0xD2,
		getlocal_3		= 0xD3,
		getproperty		= 0x66,
		getscopeobject	= 0x65,
		getslot			= 0x6C,
		getsuper		= 0x04,
		greaterequals	= 0xB0, // ??? // ERROR: in specs this opcode is 0xAF, the same as greaterthan
		greaterthan		= 0xAF,
		hasnext			= 0x1F,
		hasnext2		= 0x32,
		ifeq			= 0x13,
		iffalse			= 0x12,
		ifge			= 0x18,
		ifgt			= 0x17,
		ifle			= 0x16,
		iflt			= 0x15,
		ifnge			= 0x0F,
		ifngt			= 0x0E,
		ifnle			= 0x0D,
		ifnlt			= 0x0C,
		ifne			= 0x14,
		ifstricteq		= 0x19,
		ifstrictne		= 0x1A,
		iftrue			= 0x11,
		in				= 0xB4,
		inclocal		= 0x92,
		inclocal_i		= 0xC2,
		increment		= 0x91,
		increment_i		= 0xC0,
		initproperty	= 0x68,
		instanceof		= 0xB1,
		istype			= 0xB2,
		istypelate		= 0xB3,
		jump			= 0x10,
		kill			= 0x08,
		label			= 0x09,
		lessequals		= 0xAE,
		lessthan		= 0xAD,
		lookupswitch	= 0x1B,
		lshift			= 0xA5,
		modulo			= 0xA4,
		multiply		= 0xA2,
		multiply_i		= 0xC7,
		negate			= 0x90,
		negate_i		= 0xC4,
		newactivation	= 0x57,
		newarray		= 0x56,
		newcatch		= 0x5A,
		newclass		= 0x58,
		newfunction		= 0x40,
		newobject		= 0x55,
		nextname		= 0x1E,
		nextvalue		= 0x23,
		nop				= 0x01,
		not				= 0x96,
		pop				= 0x29,
		popscope		= 0x1D,
		pushbyte		= 0x24,
		pushdouble		= 0x2F,
		pushfalse		= 0x27,
		pushint			= 0x2D,
		pushnamespace	= 0x31,
		pushnan			= 0x28,
		pushnull		= 0x20,
		pushscope		= 0x30,
		pushshort		= 0x25,
		pushstring		= 0x2C,
		pushtrue		= 0x26,
		pushuint		= 0x2E,
		pushundefined	= 0x21,
		pushwith		= 0x1C,
		returnvalue		= 0x48,
		returnvoid		= 0x47,
		rshift			= 0xA6,
		setlocal		= 0x63,
		setlocal_0		= 0xD4,
		setlocal_1		= 0xD5,
		setlocal_2		= 0xD6,
		setlocal_3		= 0xD7,
		setglobalslot	= 0x6F,
		setproperty		= 0x61,
		setslot			= 0x6D,
		setsuper		= 0x05,
		strictequals	= 0xAC,
		subtract		= 0xA1,
		subtract_i		= 0xC6,
		swap			= 0x2B,
		throw_			= 0x03,
		typeof			= 0x95,
		urshift			= 0xA7,
	};};
	//
	struct segment {
		segment(machine &_machine, pointer _data, uint _size);
		void run(uint _method);
	private:
		machine &m_machine;
		sint_array m_ints; uint_array m_uints; rbig_array m_doubles; wstring_array m_strings;
		//uint_array m_int_map, m_uint_map, m_double_map, m_string_map;
		//uint_array m_namespace_map, m_ns_set_map, m_multiname_map;
		namespaces m_namespaces; ns_sets m_ns_sets; multinames m_multinames;
		methods m_methods; instances m_instances; classinfos m_classinfos;
		scripts m_scripts; methodbodys m_methodbodys;
	};
	typedef array_<segment*> segments;
	//
	//void map_ints(const sint* _ints, uint* _map, uint _count);
	//void map_uints(const uint* _uints, uint* _map, uint _count);
	//void map_doubles(const rbig* _doubles, uint* _map, uint _count);
	//void map_strings(const wstring* _strings, uint* _map, uint _count);
	//
	sint_array m_ints;
	uint_array m_uints;
	rbig_array m_doubles;
	wstring_array m_strings;
	segments m_segments;
};
