/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct watch
{
	//
	typedef pointer type_ID;

	// getter
	struct getter
	{
		bool valid, by_value; uint value_size;
		inline getter() : valid(true), by_value(false), value_size(0) {}
		virtual void operator()(handle _value, pointer _object = 0) const = 0;
	};
	template<typename _Type> struct getter_ : getter
	{
		inline getter_(_Type _p) { valid = false; }
	};
	template<typename _T> struct getter_<_T*> : getter
	{
		inline getter_(_T *_p) : m_p(_p) { value_size = sizeof(_T*); }
		void operator () (handle _value, pointer _object = 0) const { *(_T**)_value = m_p; }
	private:
		_T *m_p;
	};
	template<typename _T, typename _O> struct getter_<_T _O::*> : getter
	{
		inline getter_(_T _O:: *_p) : m_p(_p) { by_value = true; value_size = sizeof(_T); }
		void operator () (handle _value, pointer _object = 0) const { new(_value) _T(((_O*)_object)->*m_p); }
	private:
		_T _O::* m_p;
	};
	template<typename _T> struct getter_<_T (*)()> : getter
	{
		typedef _T (*fn)();
		template<typename _R> struct _helper_ {
			static const bool by_value = true; static const uint value_size = sizeof(_R);
			static void call(handle _value, pointer _object, fn _fn) { new(_value) _R(_fn()); }
		};
		template<typename _R> struct _helper_<_R&> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &_fn(); }
		};
		template<typename _R> struct _helper_<_R*> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = _fn(); }
		};
		inline getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
		void operator () (handle _value, pointer _object = 0) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	template<typename _T, typename _O> struct getter_<_T (_O::*)() const> : getter
	{
		typedef _T (_O::*fn)() const;
		template<typename _R> struct _helper_ {
			static const bool by_value = true; static const uint value_size = sizeof(_R);
			static void call(handle _value, pointer _object, fn _fn) { new(_value) _R((((_O*)_object)->*_fn)()); }
		};
		template<typename _R> struct _helper_<_R&> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &(((_O*)_object)->*_fn)(); }
		};
		template<typename _R> struct _helper_<_R*> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = (((_O*)_object)->*_fn)(); }
		};
		inline getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
		void operator () (handle _value, pointer _object = 0) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	//template<typename _T, typename _O> struct getter_<_T (*)(_O&)> : getter
	//{
	//	inline getter_(_T (*_p)(_O&)) : m_p(_p) { by_value = true; value_size = sizeof(_T); }
	//	void operator () (handle _value, pointer _object = 0) const { new(_value) _T(m_p(*(_O*)_object)); }
	//private:
	//	_T (*m_p)(_O&);
	//};

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

			template<typename _T> struct _const_helper_
			{
				static uint index(const watch &_watch) { return _watch.get_index_of_<_T>(); }
			};
			template<typename _T> struct _const_helper_<const _T>
			{
				static uint index(const watch &_watch) { return _watch.get_index_of_<_T>(); }
			};
			template<typename _T> struct _ref_helper_
			{
				static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
			};
			template<typename _T> struct _ref_helper_<_T*>
			{
				static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
			};
			template<typename _T> struct _ref_helper_<_T&>
			{
				static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
			};
			template<typename _T> struct type_
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _T> struct type_<_T*>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _T, typename _S> struct type_<_T _S::*>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _T> struct type_<_T (*)()>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _T, typename _S> struct type_<_T (_S::*)() const>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _T, typename _S> struct type_<_T (_S::*)()>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
		};

		type_ID ID;
		astring name;
		array_<uint> bases;
		array_<member*> members;

		type(watch &_watch) : m_watch(_watch)
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
		template<typename _Type> void add_base_()
		{
			uint l_type = member::type_<_Type>::index(m_watch);
			if (l_type == bad_ID)
			{
				std::cerr << "ERROR: Base type of type " << name << " is not registered\n";
			}
			else
			{
				bases.push_back(l_type);
			}
		}
		template<typename _Type> member& add_member_(const achar *_name)
		{
			uint l_type = member::type_<_Type>::index(m_watch);

			if (l_type == bad_ID)
			{
				std::cerr << "ERROR: Member '" << _name << "' type is not registered\n";
			}

			for (uint i = 0, s = members.size(); i < s; ++i)
			{
				member &l_member = *members[i];
				if (l_member.name == _name)
				{
					if (l_member.type != l_type)
					{
						std::cerr << "ERROR: Member '" << _name << "' already defined with defferent type\n";
						assert(0);
					}

					return l_member;
				}
			}
			members.push_back(new member);

			member &l_member = *members.back();
			l_member.type = l_type;
			l_member.name = _name;

			return l_member;
		}
		uint member_count() const
		{
			uint l_count = members.size();
			return l_count;
		}
		member& get_member(uint _i) const
		{
			return *members[_i];
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
			template<typename _T> const _helper_& add_base_() const
			{
				m_type.add_base_<_T>();

				return *this;
			}
			template<typename _T> const _helper_& add_member_(_T _member, const achar *_name) const
			{
				return add_member(_member, _name);
			}
			template<typename _T> const _helper_& add_member(_T _member, const achar *_name) const
			{
				type::member &l_member = m_type.add_member_<_T>(_name);
				l_member.get = new getter_<_T>(_member);

				return *this;
			}

		private:
			type &m_type;
		};

		inline watch& get_watch() const
		{
			return m_watch;
		}

	private:
		watch &m_watch;
	};

	struct varaible
	{
		array_<uint> path;

		inline varaible(watch &_watch) : m_watch(_watch)
		{
		}
		inline watch& get_watch() const
		{
			return m_watch;
		}
		inline bool valid() const
		{
			return !path.empty();
		}
		inline uint member_count() const
		{
			assert(valid());

			type::member &l_member = resolve_member();
			type &l_type = m_watch.get_type(l_member.type);

			return l_type.member_count();
		}
		template<typename _T> struct _get_helper_
		{
			static _T get(const varaible &l_v) { _T l_value; l_value.~_T(); l_v.resolve_value(&l_value); return l_value; }
		};
		template<typename _T> struct _get_helper_<_T*>
		{
			static _T* get(const varaible &l_v) { _T* l_value; l_v.resolve_value(&l_value); return l_value; }
		};
		template<typename _T> struct _get_helper_<_T&>
		{
			static _T& get(const varaible &l_v) { _T* l_value; l_v.resolve_value(&l_value); return *l_value; }
		};
		template<typename _Type> _Type get_() const
		{
			assert(!path.empty());

			type::member &l_member = resolve_member();
			type &l_type = m_watch.get_type(l_member.type);

			if (l_member.get->by_value)
			{
				if (l_type.ID == get_ID_of_<_Type>())
				{
					return _get_helper_<_Type>::get(*this);
				}
			}
			else
			{
				if (l_type.ID == get_ID_of_<_Type>())
				{
					return _get_helper_<_Type>::get(*this);
				}
				else if (l_type.ID == get_ID_of_<traits_<_Type>::pointed>())
				{
					return _get_helper_<_Type>::get(*this);
				}
				else if (l_type.ID == get_ID_of_<traits_<_Type>::referred>())
				{
					return _get_helper_<_Type>::get(*this);
				}
			}

			assert(0);

			return traits_<_Type>::referred();
		}

	private:
		watch &m_watch;
		type::member& resolve_member() const
		{
			uint l_type = 0;
			for (uint i = 0, s = path.size(); i < s; ++i)
			{
				type::member &l_member = m_watch.get_type(l_type).get_member(path[i]);
				l_type = l_member.type;

				if (i + 1 == s) return l_member;
			}

			assert(0);

			return *(type::member*)0;
		}
		void resolve_value(handle _value) const
		{
			uint l_type = 0;
			handle l_object = 0;
			for (uint i = 0, s = path.size(); i < s; ++i)
			{
				type::member &l_member = m_watch.get_type(l_type).get_member(path[i]);
				handle l_value = i + 1 < s ? calloc(l_member.get->value_size, 1) : _value;
				(*l_member.get)(l_value, l_object);

				l_type = l_member.type;

				if (i + 1 == s) return;

				l_object = l_value;
			}
		}
	};

	watch()
	{
		clear();
	}
	~watch()
	{
		while (!m_types.empty())
		{
			delete m_types.back();
			m_types.pop_back();
		}
	}

	template<typename _Type> type::_helper_<_Type> add_type_(const achar *_name)
	{
		assert(!m_types.empty());

		for (uint i = 0, s = m_types.size(); i < s; ++i)
		{
			type &l_type = *m_types[i];
			if (l_type.ID == get_ID_of_<_Type>())
			{
				if (l_type.name != _name)
				{
					std::cerr << "WARNING: Type " << l_type.name << " redefines type " << _name << "\n";
					l_type.name = _name;
				}
				return type::_helper_<_Type>(l_type);
			}
		}

		m_types.push_back(new type(*this));

		type &l_type = *m_types.back();
		l_type.name = _name;
		l_type.ID = get_ID_of_<_Type>();

		return type::_helper_<_Type>(l_type);
	}
	uint type_count() const
	{
		return m_types.size();
	}
	type& get_type(uint _i) const
	{
		return *m_types[_i];
	}
	template<typename _Type> varaible add_varaible(_Type _v, const achar *_name)
	{
		assert(!m_types.empty());

		type &l_root = *m_types[0];

		type::_helper_<_Type>(l_root).add_member(_v, _name);

		varaible l_v(*this);
		l_v.path.push_back(l_root.members.size() - 1);

		return l_v;
	}
	void clear()
	{
		while (!m_types.empty())
		{
			delete m_types.back();
			m_types.pop_back();
		}

		m_types.push_back(new type(*this));

		type &l_type = *m_types.back();
		l_type.name = "root";
		l_type.ID = get_ID_of_<watch>();
	}

private:
	template<typename _Type> static type_ID get_ID_of_()
	{
		static uint sl_ID = bad_ID;
		return &sl_ID;
	}
	template<typename _Type> uint get_index_of_() const
	{
		for (uint i = 0, s = m_types.size(); i < s; ++i)
		{
			if (m_types[i]->ID == get_ID_of_<_Type>()) return i;
		}

		return bad_ID;
	}

	array_<type*> m_types;
};