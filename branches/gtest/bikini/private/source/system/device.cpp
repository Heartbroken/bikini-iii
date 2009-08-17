/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

//device

// device::resource

device::resource::resource(const info &_info, device &_device) :
	manager::object(_info, _device),
	m_version(0)
{}
//device::resource::~resource() {
//	if(m_version != 0) {
//		std::cerr << "ERROR: Destroy device resource before deleting\n";
//		assert(m_version == 0);
//	}
//}
//bool device::resource::create() {
//	m_version = 0;
//	return true;
//}
//bool device::resource::load() {
//	return true;
//}
//void device::resource::destroy() {
//	m_version = 0;
//}

// device::resource::info

device::resource::info::info(uint _type) :
	manager::object::info(_type)
{}

} /* namespace bk -------------------------------------------------------------------------------*/
