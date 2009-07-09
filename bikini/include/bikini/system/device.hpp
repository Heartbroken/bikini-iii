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
		virtual ~resource();
		virtual bool create();
		virtual bool load();
		virtual void destroy();
		inline device& get_device() const { return static_cast<device&>(get_manager()); }
		inline bool valid() const { return m_version != bad_ID; }
	protected:
		typedef thread::locker _lock;
		inline thread::section& section() { return m_section; }
	private:
		thread::section m_section;
		uint m_version;
	};
	device();
	virtual ~device();
};