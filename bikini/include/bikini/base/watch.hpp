/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct watch
{
	// getter
	struct getter
	{
		virtual void operator()(handle _value, pointer _object = 0) const = 0;
	};
	template<typename _Type> struct getter_;
	template<typename _Type> struct getter_<_Type*> : getter
	{
		inline getter_(_Type *_p) : m_p(_p) {}
		void operator()(handle _value, pointer _object = 0) const { *(_Type*)_value = *m_p; }
	private:
		_Type *m_p;
	};
	template<typename _Type, typename _Object> struct getter_<_Type _Object::*> : getter
	{
		inline getter_(_Type _Object:: *_p) : m_p(_p) {}
		void operator()(handle _value, pointer _object = 0) const { *(_Type*)_value = ((_Object*)_object)->*m_p; }
	private:
		_Type _Object:: *m_p;
	};
	template<typename _Type> struct getter_<_Type (*)()> : getter
	{
		inline getter_(_Type (*_p)()) : m_p(_p) {}
		void operator()(handle _value, pointer _object = 0) const { *(_Type*)_value = m_p(); }
	private:
		_Type (*m_p)();
	};
	template<typename _Type, typename _Object> struct getter_<_Type (_Object::*)()> : getter
	{
		inline getter_(_Type (_Object::*_p)()) : m_p(_p) {}
		void operator()(handle _value, pointer _object = 0) const { *(_Type*)_value = (((_Object*)_object)->*m_p)(); }
	private:
		_Type (_Object::*m_p)();
	};

	// type
	struct type
	{
		// member
		struct member
		{
			astring name;
			getter *get;

			member() : get(0)
			{
			}
			~member()
			{
				delete get;
			}
		};

		astring name;
		array_<member*> members;

		~type()
		{
			while (!members.empty())
			{
				delete members.back();
				members.pop_back();
			}
		}
		member& add_member(const astring &_name)
		{
			for (uint i = 0, s = members.size(); i < s; ++i)
			{
				if (members[i]->name == _name) return *members[i];
			}
			members.push_back(new member);
			members.back()->name = _name;

			return *members.back();
		}

		struct _helper
		{
			_helper(type &_t) : m_type(_t) {}
			template<typename _Type> const _helper& add_member(_Type _m, const astring &_name) const
			{
				type::member &l_m = m_type.add_member(_name);
				l_m.get = new getter_<_Type>(_m);

				return *this;
			}
		private:
			type &m_type;
		};
	};

	watch()
	{
		while (!m_types.empty())
		{
			delete m_types.back();
			m_types.pop_back();
		}
	}

	//
	template<typename _Type> type::_helper add_type(const astring &_name)
	{
		for (uint i = 0, s = m_types.size(); i < s; ++i)
		{
			if (m_types[i]->name == _name) return type::_helper(*m_types[i]);
		}

		m_types.push_back(new type);
		m_types.back()->name = _name;

		return type::_helper(*m_types.back());
	}

private:
	array_<type*> m_types;
};