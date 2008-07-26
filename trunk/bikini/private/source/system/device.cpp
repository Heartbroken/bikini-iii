/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

//device

device::device()
{}

device::~device() {
}

// device::resource

device::resource::resource(device &_device, uint _type) :
	m_device(_device),
	m_version(bad_ID),
	m_type(_type)
{}
device::resource::~resource() {
	if(m_version != bad_ID) {
		std::cerr << "ERROR: Destroy device resource before deleting\n";
		assert(m_version == bad_ID);
	}
}
bool device::resource::create() {
	m_version = 0;
	return true;
}
bool device::resource::load() {
	return true;
}
void device::resource::destroy() {
	m_version = bad_ID;
}

} /* namespace bk -------------------------------------------------------------------------------*/
