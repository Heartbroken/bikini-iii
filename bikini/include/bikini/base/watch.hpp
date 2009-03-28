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
			uint type;
			astring name;
			getter *get;

			member() : get(0)
			{
			}
			~member()
			{
				delete get;
			}

			template<typename _T> struct type_ { static uint ID() { return *ID_<_T>(); } };
			template<typename _T, typename _S> struct type_<_T _S::*> { static uint ID() { return *ID_<_T>(); } };
			template<typename _T> struct type_<_T (*)()> { static uint ID() { return *ID_<_T>(); } };
			template<typename _T, typename _S> struct type_<_T (_S::*)()> { static uint ID() { return *ID_<_T>(); } };
		};

		astring name;
		array_<uint> bases;
		array_<member*> members;

		type()
		{
		}
		~type()
		{
			while (!members.empty())
			{
				delete members.back();
				members.pop_back();
			}
		}
		void add_base(uint _type)
		{
			bases.push_back(_type);
		}
		template<typename _Type> member& add_member_(const astring &_name)
		{
			uint l_type = member::type_<_Type>::ID();

			if (l_type == bad_ID)
			{
				std::cerr << "ERROR: Member '" << _name << "' type is not registered\n";
			}

			for (uint i = 0, s = members.size(); i < s; ++i)
			{
				if (members[i]->name == _name) return *members[i];
			}
			members.push_back(new member);

			member &l_member = *members.back();
			l_member.type = member::type_<_Type>::ID();
			l_member.name = _name;

			return l_member;
		}

		//
		uint *ID;
		template<typename _Type> static uint* ID_()
		{
			static uint sl_ID = bad_ID;
			return &sl_ID;
		}

		//
		template<typename _Type, bool _POD = traits_<_Type>::is_fundamental> struct _helper_
		{
			_helper_(type &_t) {}
		};
		template<typename _Type> struct _helper_<_Type, false>
		{
			_helper_(type &_t) : m_type(_t)
			{
			}
			template<typename _Type> const _helper_& add_base_() const
			{
				uint l_type = *type::ID_<_Type>();
				if (l_type == bad_ID)
				{
					std::cerr << "ERROR: Base type of type " << m_type.name << " is not registered\n";
				}
				else
				{
					m_type.add_base(l_type);
				}

				return *this;
			}
			template<typename _Type> const _helper_& add_member(_Type _member, const astring &_name) const
			{
				type::member &l_member = m_type.add_member_<_Type>(_name);
				l_member.get = new getter_<_Type>(_member);

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
	template<typename _Type> type::_helper_<_Type> add_type_(const astring &_name)
	{
		for (uint i = 0, s = m_types.size(); i < s; ++i)
		{
			type &l_type = *m_types[i];
			if (l_type.ID == type::ID_<_Type>())
			{
				if (l_type.name != _name)
				{
					std::cerr << "WARNING: Type " << l_type.name << " redefines type " << _name << "\n";
					l_type.name = _name;
				}
				return type::_helper_<_Type>(l_type);
			}
		}

		m_types.push_back(new type);

		type &l_type = *m_types.back();
		l_type.ID = type::ID_<_Type>();
		*l_type.ID = m_types.size() - 1;
		l_type.name = _name;

		return type::_helper_<_Type>(l_type);
	}

private:
	array_<type*> m_types;
};