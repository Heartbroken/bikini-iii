/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if defined(BIKNI_VARIANT_DYNAMIC)
#	define VARIANT_DYN_ALOC
#endif

template<typename _Typelist> struct variant {
	typedef _Typelist typelist;

	inline variant() : m_type(bad_ID) {
#ifdef VARIANT_DYN_ALOC
		m_data = 0;
#endif
	}
	inline variant(const variant &_v) : m_type(bad_ID) {
		construct(_v.type(), _v.data());
	}
	template<typename _Type> inline variant(const _Type &_v) : m_type(bad_ID) {
		__bk_c_assert(typelist::type<_Type>::exists);
		construct(typelist::type<_Type>::index, &_v);
	}
	template<typename _Otherlist> inline variant(const variant<_Otherlist> &_v) : m_type(bad_ID) {
		__bk_c_assert(typelist::otherlist<_Otherlist>::belong);
		construct(typelist::otherlist<_Otherlist>::remap(_v.type()), _v.data());
	}
	inline ~variant() {
		destruct();
	}

	inline variant& operator = (const variant &_v) {
		construct(_v.type(), _v.data());
		return *this;
	}
	template<typename _Type> inline variant& operator = (const _Type &_v) {
		__bk_c_assert(typelist::type<_Type>::exists);
		construct(typelist::type<_Type>::index, &_v);
		return *this;
	}
	template<typename _Otherlist> inline variant& operator = (const variant<_Otherlist> &_v) {
		construct(typelist::otherlist<_Otherlist>::remap(_v.type()), _v.data());
		return *this;
	}

	inline bool operator == (const variant &_v) const {
		//return m_type != bad_ID && m_type == _v.type() && memcmp(m_data, _v.data(), typelist::size(m_type)) == 0;
		return m_type != bad_ID && m_type == _v.type() && typelist::compare(m_type, m_data, _v.data());
	}
	template<typename _Type> inline bool operator == (const _Type &_v) {
		//return typelist::type<_Type>::exists && m_type == typelist::type<_Type>::index && memcmp(m_data, &_v, typelist::size(m_type)) == 0;
		return m_type != bad_ID && m_type == m_type == typelist::type<_Type>::index && typelist::compare(m_type, m_data, &_v);
	}
	template<typename _Otherlist> inline bool operator == (const variant<_Otherlist> &_v) {
		//return m_type != bad_ID && m_type == typelist::otherlist<_Otherlist>::remap(_v.type()) && memcmp(m_data, _v.data(), typelist::size(m_type)) == 0;
		return m_type != bad_ID && m_type == typelist::otherlist<_Otherlist>::remap(_v.type()) && typelist::compare(m_type, m_data, _v.data());
	}
	template<typename _Type> inline bool operator != (const _Type &_v) {
		return !(*this == _v);
	}

	inline void construct(uint _type) {
		destruct();
		m_type = _type;
#ifdef VARIANT_DYN_ALOC
		m_data = 0;
#endif
		if(m_type < typelist::count) {
#ifdef VARIANT_DYN_ALOC
			m_data = typelist::construct(m_type);
#else
			typelist::construct(m_data, m_type);
#endif
		}
	}
	inline void construct(u32 _type, pointer _data) {
		destruct();
		m_type = _type;
#ifdef VARIANT_DYN_ALOC
		m_data = 0;
#endif
		if(m_type < typelist::count) {
#ifdef VARIANT_DYN_ALOC
			m_data = typelist::construct(m_type, _data);
#else
			typelist::construct(m_data, m_type, _data);
#endif
		}
	}
	inline void destruct() {
		if(m_type != bad_ID) {
#ifdef VARIANT_DYN_ALOC
			typelist::destruct(m_data, m_type, true); m_data = 0;
#else
			typelist::destruct(m_data, m_type, false);
#endif
			m_type = bad_ID;
		}
	}

	template<typename _Type> inline static bool can_take(const _Type &_v) {
		return typelist::type<_Type>::exists;
	}
	template<typename _Otherlist> inline static bool can_take(const variant<_Otherlist> &_v) {
		return typelist::otherlist<_Otherlist>::remap(_v.type()) != bad_ID;
	}
	inline bool is_none() const {
		return m_type == bad_ID;
	}
	inline bool is_nothing() const {
		return m_type == bad_ID;
	}
	template<typename _Type> inline bool is() const {
		return !is_none() && typelist::type<_Type>::index == m_type;
	}
	template<typename _Type> inline const _Type& to() const {
		return *reinterpret_cast<const _Type*>(m_data);
	}
	template<typename _Type> inline const _Type& get() const {
		return to<_Type>();
	}
	template<typename _Type> inline const _Type& def(const _Type &_def) const {
		return is<_Type>() ? to<_Type>() : _def;
	}

	inline uint type() const {
		return m_type;
	}
	inline pointer data() const {
		return m_data;
	}
private:
	uint m_type;
#ifdef VARIANT_DYN_ALOC
	handle m_data;
#else
	u8 m_data[typelist::max_size];
#endif
};

#ifdef VARIANT_DYN_ALOC
#	undef VARIANT_DYN_ALOC
#endif