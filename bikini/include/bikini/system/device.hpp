/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct device : manager {
	struct resource : manager::object {
		struct info : manager::object::info {
			typedef resource object;
			typedef device manager;
			info(uint _type);
		};
		resource(const info &_info, device &_device);
		inline device& get_device() const { return static_cast<device&>(get_manager()); }
		inline bool valid() const { return m_version > 0; }
		inline void set_invalid() { m_version = 0; }
		inline real version() const { return m_version; }
	protected:
		typedef thread::locker lock;
		inline thread::section& section() { return m_section; }
		inline void update_version() { m_version = (real)sys_time(); }
	private:
		thread::section m_section;
		real m_version;
	};
};