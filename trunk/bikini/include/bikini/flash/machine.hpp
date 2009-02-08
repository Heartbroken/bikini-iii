/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine {
	bool do_ABC(pointer _data, uint _size);
private:
	struct ns {
		uint string;
	};
	typedef array_<ns> namespaces;
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
