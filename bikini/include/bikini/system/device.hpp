/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct device : uncopyble {
	struct resource : uncopyble {
		resource(device &_device, uint _type);
		virtual ~resource();
		bool create();
		virtual bool load();
		virtual void destroy();
		inline device& get_device() const { return m_device; }
		inline uint type() const { return m_type; }
	private:
		device &m_device;
		uint m_version;
		uint m_type;
	};
	device();
	virtual ~device();
};