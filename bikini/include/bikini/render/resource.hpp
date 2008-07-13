/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace render { /*----------------------------------------------------------------------------*/

template<typename _Owner> struct resource {
	typedef _Owner owner;
	inline resource(owner &_owner) : m_owner(_owner) {}
	virtual ~resource() {}
	inline owner& get_owner() const { return m_owner; }
private:
	owner &m_owner;
};

} /* namespace render ---------------------------------------------------------------------------*/