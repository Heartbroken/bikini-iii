/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// manager

manager::manager() : m_counter(0) {
}

manager::~manager() {
	for(u32 i = 0, s = m_objects.size(); i < s; i++) if(m_objects[i] != 0) {
		delete m_objects[i];
	}
}

uint manager::add(object &_object) {
	uint l_index;
	if(m_free_IDs.empty()) {
		assert(m_objects.size() < index_mask);
		l_index = m_objects.size();
		m_objects.push_back(&_object);
	} else {
		l_index = m_free_IDs.back(); m_free_IDs.pop_back();
		assert(l_index < m_objects.size());
		m_objects[l_index] = &_object;
	}
	uint l_ID = (++m_counter << ID_half_size) | l_index;
	return l_ID;
}

bool manager::exists(uint _ID) const {
	uint l_index = _ID & index_mask;
	if(l_index >= m_objects.size() || m_objects[l_index] == 0) return false;
	object &l_object = *m_objects[l_index];
	if(l_object.ID() != _ID) return false;
	return true;
}

manager::object& manager::get(uint _ID) const {
	assert(exists(_ID));
	return *m_objects[_ID & index_mask];
}

void manager::remove(uint _ID) {
	assert(exists(_ID));
	m_objects[_ID & index_mask] = 0;
	m_free_IDs.push_back(_ID & index_mask);
}

uint manager::get_first_ID(uint _type /*= bad_ID*/) const {
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		object &l_object = *m_objects[i];
		if(&l_object != 0 && (l_object.type() == _type || _type == bad_ID)) {
			return l_object.ID();
		}
	}
	return bad_ID;
}

uint manager::get_next_ID(uint _prev_ID, uint _type /*= bad_ID*/) const {
	assert((_prev_ID & index_mask) < m_objects.size());
	for(uint i = (_prev_ID & index_mask) + 1, s = m_objects.size(); i < s; ++i) {
		object &l_object = *m_objects[i];
		if(&l_object != 0 && (l_object.type() == _type || _type == bad_ID)) {
			return m_objects[i]->ID();
		}
	}
	return bad_ID;
}

void manager::kill(uint _ID) {
	assert(exists(_ID) && get(_ID).ref_count() == 0);
	delete m_objects[_ID & index_mask];
}

uint manager::release(uint _ID) {
	if(exists(_ID) && get(_ID).ref_count() > 0) return get(_ID).release();
	return 0;
}

bool manager::update(real _dt) {
	for(uint i = m_shared.size(); i-- > 0;) {
		uint l_ID = m_shared[i];
		assert(exists(l_ID));
		if(get(l_ID).ref_count() == 0) {
			kill(l_ID);
			m_shared.erase(m_shared.begin() + i);
		}
	}
	if(m_objects.size() - m_free_IDs.size() != m_update_order.size()) {
		m_build_update_order();
	}
	for(uint i = 0, s = m_update_order.size(); i < s; ++i) {
		get(m_update_order[i]).update(_dt);
	}
	return true;
}

void manager::clear() {
	for(u32 i = 0, s = m_objects.size(); i < s; i++) if(m_objects[i] != 0) {
		delete m_objects[i];
	}
	m_objects.resize(0);
	m_free_IDs.resize(0);
	m_counter = 0;
}

void manager::destroy() {
	clear();
}

void manager::m_build_update_order() {
	m_update_order.resize(0);
	static std::vector<uint> l_queue; l_queue.resize(0);
	static std::vector<uint> l_objects; l_objects.resize(m_objects.size());
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		if(m_objects[i] != 0) l_objects[i] = m_objects[i]->ID();
		else l_objects[i] = bad_ID;
	}
	for(uint i = 0, s = l_objects.size(); i < s; ++i) {
		if(!exists(l_objects[i])) continue;
		l_queue.push_back(l_objects[i]); l_objects[i] = bad_ID;
		while(!l_queue.empty()) {
			if(!exists(l_queue.back())) { l_queue.pop_back(); continue; }
			object &l_object = get(l_queue.back());
			if(l_object.has_dependency()) {
				bool l_continue = false;
				for(uint i = 0, s = l_object.dependency_count(); i < s; ++i) {
					uint l_dependency_ID = l_object.dependency(i);
					uint l_index = (l_dependency_ID & index_mask);
					if(exists(l_dependency_ID) && l_objects[l_index] != bad_ID) {
						l_continue = true;
						l_queue.push_back(l_dependency_ID);
						l_objects[l_index] = bad_ID;
						break;
					}
				}
				if(l_continue) continue;
			}
			m_update_order.push_back(l_object.ID());
			l_queue.pop_back();
		}
	}
}

// manager::object

manager::object::object(const info &_info, manager &_manager) : m_info(_info), m_manager(_manager), m_ref_count(0) {
	m_ID = m_manager.add(*this);
}

manager::object::~object() {
	m_manager.remove(m_ID);
}

bool manager::object::update(real _dt) {
	return false;
}

// manager::object::info

manager::object::info::info(uint _type) : m_type(_type) {
}

manager::object::info::~info() {
}

} /* namespace bk -------------------------------------------------------------------------------*/
