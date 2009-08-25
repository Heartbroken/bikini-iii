/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _Type> struct pool_
{
	typedef _Type type;
	struct item { uint ID; type value; };
	pool_() : m_counter(0) {}
	uint add(const type &_value)
	{
		uint l_index;
		if (m_free.empty())
		{
			l_index = m_items.size();
			m_items.resize(m_items.size() + 1);
		}
		else
		{
			l_index = m_free.back();
			m_free.pop_back();
		}
		item &l_item = m_items[l_index];
		l_item.ID = l_index | (m_counter++ << half_ID_size);
		l_item.value = _value;
		return l_item.ID;
	}
	type& get(uint _ID)
	{
		assert(exists(_ID));
		uint l_index = _ID & index_mask;
		item &l_item = m_items[l_index];
		return l_item.value;
	}
	const type& get(uint _ID) const
	{
		assert(exists(_ID));
		uint l_index = _ID & index_mask;
		item &l_item = m_items[l_index];
		return l_item.value;
	}
	void remove(uint _ID)
	{
		assert(exists(_ID));
		uint l_index = _ID & index_mask;
		item &l_item = m_items[l_index];
		l_item.ID = bad_ID;
		m_free.push_back(l_index);
	}
	bool exists(uint _ID) const
	{
		uint l_index = _ID & index_mask;
		if (l_index > m_items.size()) return false;
		const item &l_item = m_items[l_index];
		if (l_item.ID != _ID) return false;
		return true;
	}
private:
	static const uint half_ID_size = sizeof(uint) * 8 / 2;
	static const uint index_mask = uint(-1) << half_ID_size;
	array_<item> m_items;
	uint_array m_free;
	uint m_counter;
};
