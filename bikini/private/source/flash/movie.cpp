/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// movie

movie::movie() : m_loader_p(0) {
}
movie::~movie() {
	delete m_loader_p;
}
bool movie::load(const wchar* _path) {
	if(0 == &get_loader()) set_loader(m_def_loader);
	uint l_file_ID = get_loader().open(_path);
	if(l_file_ID != bad_ID) {
	}
	return true;
}


} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
