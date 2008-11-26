/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// movie

// movie::info

inline uint movie::info::define_count() const {
	return m_defines.size();
}
inline uint movie::info::define_type(uint _i) const {
	return (*m_defines[_i]).type();
}
template<typename _T>
inline const typename _T::info& movie::info::get_define(uint _i) const {
	return static_cast<const typename _T::info&>(*m_defines[_i]);
}
