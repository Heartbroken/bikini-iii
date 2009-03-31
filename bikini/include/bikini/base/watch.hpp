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
		virtual void operator( ) (handle _value, pointer _object) const = 0;
	};
	template<typename _Type> struct getter_ : getter
	{
		inline getter_(_Type) { valid = false; }
		void operator () (handle _value, pointer _object) const {}
	};
	template<typename _T> struct getter_<void (*)(_T)> : getter
	{
		inline getter_(void (*)(_T)) { valid = false; }
		void operator () (handle _value, pointer _object) const {}
	};
	template<typename _T, typename _O> struct getter_<void (_O::*)(_T)> : getter
	{
		inline getter_(void (_O::*)(_T)) { valid = false; }
		void operator () (handle _value, pointer _object) const {}
	};
	template<typename _T> struct getter_<_T*> : getter
	{
		inline getter_(_T *_p) : m_p(_p) { value_size = sizeof(_T*); }
		void operator () (handle _value, pointer _object) const { *(_T**)_value = m_p; }
	private:
		_T *m_p;
	};
	template<typename _T, typename _O> struct getter_<_T _O::*> : getter
	{
		inline getter_(_T _O:: *_p) : m_p(_p) { by_value = false; value_size = sizeof(_T*); }
		void operator () (handle _value, pointer _object) const { *(_T**)_value = &(((_O*)_object)->*m_p); }
	private:
		_T _O::* m_p;
	};
	template<typename _T> struct getter_<_T (*)()> : getter
	{
		typedef _T (*fn)();
		template<typename _R> struct _helper_ {
			static const bool by_value = true; static const uint value_size = sizeof(_R);
			static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R(_fn()); }
		};
		template<typename _R> struct _helper_<_R&> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &_fn(); }
		};
		template<typename _R> struct _helper_<_R*> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = _fn(); }
		};
		inline getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
		void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	template<typename _T, typename _O> struct getter_<_T (_O::*)() const> : getter
	{
		typedef _T (_O::*fn)() const;
		template<typename _R> struct _helper_ {
			static const bool by_value = true; static const uint value_size = sizeof(_R);
			static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R((((_O*)_object)->*_fn)()); }
		};
		template<typename _R> struct _helper_<_R&> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &(((_O*)_object)->*_fn)(); }
		};
		template<typename _R> struct _helper_<_R*> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = (((_O*)_object)->*_fn)(); }
		};
		inline getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
		void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	// If your accessor doesn't match any of getter templates or matches wrong one,
	// make a wrapper function like
	//
	// MemberType Get_MyClass_Member1(const MyClass &_o) { return _o.Get_Member1(); }
	//
	// and register it.
	template<typename _T, typename _O> struct getter_<_T (*)(const _O&)> : getter
	{
		typedef _T (*fn)(const _O&);
		template<typename _R> struct _helper_ {
			static const bool by_value = true; static const uint value_size = sizeof(_R);
			static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R(_fn(*(_O*)_object)); }
		};
		template<typename _R> struct _helper_<_R&> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &_fn(*(_O*)_object); }
		};
		template<typename _R> struct _helper_<_R*> {
			static const bool by_value = false; static const uint value_size = sizeof(_R*);
			static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = _fn(*(_O*)_object); }
		};
		inline getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
		void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};

	// setter
	struct setter
	{
		bool valid;
		inline setter() : valid(true) {}
		virtual void operator () (pointer _value, handle _object) const = 0;
	};
	template<typename _Type> struct setter_ : setter
	{
		inline setter_(_Type) { valid = false; }
		void operator () (pointer _value, handle _object) const {}
	};
	template<typename _T> struct setter_<_T*> : setter
	{
		inline setter_(_T *_p) : m_p(_p) {}
		void operator () (pointer _value, handle _object) const { *m_p = *(_T*)_value; }
	private:
		_T *m_p;
	};
	template<typename _T> struct setter_<_T(*)()> : setter
	{
		inline setter_(_T(*)()){ valid = false; }
		void operator () (pointer _value, handle _object) const {}
	};
	template<typename _T, typename _O> struct setter_<_T _O::*> : setter
	{
		inline setter_(_T _O:: *_p) : m_p(_p) {}
		void operator () (pointer _value, handle _object) const { ((_O*)_object)->*m_p = *(_T*)_value; }
	private:
		_T _O::* m_p;
	};
	template<typename _R, typename _T> struct setter_<_R (*)(_T)> : setter
	{
		typedef _R (*fn)(_T);
		template<typename _V> struct _helper_ {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V&> {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V*> {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn((_V*)_value); }
		};
		inline setter_(fn _fn) : m_fn(_fn) {}
		void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	template<typename _R, typename _O, typename _T> struct setter_<_R (_O::*)(_T)> : setter
	{
		typedef _R (_O::*fn)(_T);
		template<typename _V> struct _helper_ {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)(*(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V&> {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)(*(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V*> {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)((_V*)_value); }
		};
		inline setter_(fn _fn) : m_fn(_fn) {}
		void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	template<typename _O, typename _T> struct setter_<_T& (_O::*)()> : setter
	{
		typedef _T& (_O::*fn)();
		template<typename _V> struct _helper_ {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = *(_V*)_value; }
		};
		template<typename _V> struct _helper_<_V&> {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = *(_V*)_value; }
		};
		template<typename _V> struct _helper_<_V*> {
			static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = (_V*)_value; }
		};
		inline setter_(fn _fn) : m_fn(_fn) {}
		void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
	};
	// If your accessor doesn't match any of setter templates or matches wrong one,
	// make a wrapper function like
	//
	// void Set_MyClass_Member1(MyClass &_o, const MemberType &_v) { _o.Set_Member1(_v); }
	//
	// and register it
	template<typename _O, typename _T> struct setter_<void (*)(_O&, _T)> : setter
	{
		typedef void (*fn)(_O&, _T);
		template<typename _V> struct _helper_ {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, *(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V&> {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, *(_V*)_value); }
		};
		template<typename _V> struct _helper_<_V*> {
			static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, (_V*)_value); }
		};
		inline setter_(fn _fn) : m_fn(_fn) {}
		void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
	private:
		fn m_fn;
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
			setter *set;

			member() : get(0), set(0)
			{
			}
			~member()
			{
				delete get;
				delete set;
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
			template<typename _R, typename _T> struct type_<_R (*)(_T)>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _R, typename _S, typename _T> struct type_<_R (_S::*)(_T)>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _S, typename _T> struct type_<_T (*)(const _S&)>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
			template<typename _S, typename _T> struct type_<void (*)(_S&, _T)>
			{
				static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
			};
		};
		struct base
		{
			uint type;
			handle (*base_cast)(handle);
			template<typename _T, typename _B> static handle cast_(handle _p) { return static_cast<_B*>((_T*)_p); }
		};
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
				base &l_base = m_type.add_base_<_T>();
				l_base.base_cast = base::cast_<_Type, _T>;

				return *this;
			}
			template<typename _T> const _helper_& add_member_(_T _member, const achar *_name) const
			{
				return add_member(_member, _name);
			}
			template<typename _T> const _helper_& add_member(_T _member, const achar *_name) const
			{
				type::member &l_member = m_type.add_member_<_T>(_name);

				getter *l_get = new getter_<_T>(_member);
				if (l_get->valid) l_member.get = l_get;
				else delete l_get;

				setter *l_set = new setter_<_T>(_member);
				if (l_set->valid) l_member.set = l_set;
				else delete l_set;

				return *this;
			}

		private:
			type &m_type;
		};


		type_ID ID;
		astring name;

		type(watch &_watch) : m_watch(_watch), m_destroy_fn(0)
		{
		}
		~type()
		{
			while (!m_members.empty())
			{
				delete m_members.back();
				m_members.pop_back();
			}
			while (!m_bases.empty())
			{
				delete m_bases.back();
				m_bases.pop_back();
			}
		}
		template<typename _Type> base& add_base_()
		{
			uint l_type = member::type_<_Type>::index(m_watch);
			if (l_type == bad_ID)
			{
				std::cerr << "ERROR: (Watch) Base type of type " << name << " is not registered\n";
				assert(0);
			}
			m_bases.push_back(new base);
			m_bases.back()->type = l_type;

			return *m_bases.back();
		}
		inline uint base_count() const
		{
			return m_bases.size();
		}
		inline base& get_base(uint _i) const
		{
			return *m_bases[_i];
		}
		template<typename _Type> member& add_member_(const achar *_name)
		{
			uint l_type = member::type_<_Type>::index(m_watch);

			if (l_type == bad_ID)
			{
				std::cerr << "ERROR: (Watch) Member '" << _name << "' type is not registered\n";
			}

			for (uint i = 0, s = m_members.size(); i < s; ++i)
			{
				member &l_member = *m_members[i];
				if (l_member.name == _name)
				{
					if (l_member.type != l_type)
					{
						std::cerr << "ERROR: (Watch) Member '" << _name << "' already defined with different type\n";
						assert(0);
					}

					return l_member;
				}
			}
			m_members.push_back(new member);

			member &l_member = *m_members.back();
			l_member.type = l_type;
			l_member.name = _name;

			return l_member;
		}
		inline uint own_member_count() const
		{
			return m_members.size();
		}
		uint member_count() const
		{
			uint l_count = m_members.size();

			for (uint i = 0, s = base_count(); i < s; ++i)
			{
				base &l_base = get_base(i);
				type &l_type = m_watch.get_type(l_base.type);
				l_count += l_type.member_count();
			}

			return l_count;
		}
		member& get_member(uint _i) const
		{
			if (_i < m_members.size())
			{
				return *m_members[_i];
			}

			uint l_i = _i - m_members.size();

			for (uint i = 0, s = base_count(); i < s; ++i)
			{
				base &l_base = get_base(i);
				type &l_type = m_watch.get_type(l_base.type);

				uint l_count = l_type.member_count();

				if (l_i < l_count) return l_type.get_member(l_i);

				l_i -= l_count;
			}

			std::cerr << "ERROR: (Watch) Bad member index\n";
			assert(0);

			return *(member*)0;
		}
		handle member_base_cast(uint _i, handle _p) const
		{
			if (_i < m_members.size())
			{
				return _p;
			}

			uint l_i = _i - m_members.size();

			for (uint i = 0, s = base_count(); i < s; ++i)
			{
				base &l_base = get_base(i);
				type &l_type = m_watch.get_type(l_base.type);

				uint l_count = l_type.member_count();

				if (l_i < l_count) return l_type.member_base_cast(l_i, l_base.base_cast(_p));

				l_i -= l_count;
			}

			std::cerr << "ERROR: (Watch) Bad member index\n";
			assert(0);

			return _p;
		}
		uint find_member(const achar *_name) const
		{
			for (uint i = 0, s = member_count(); i < s; ++i)
			{
				member &l_member = get_member(i);
				if (l_member.name == _name) return i;
			}

			return bad_ID;
		}
		inline watch& get_watch() const
		{
			return m_watch;
		}
		template<typename _Type> inline void set_destroy_()
		{
			m_destroy_fn = destroy_<_Type>;
		}
		inline void destroy_value(handle _p) const
		{
			if (m_destroy_fn != 0) m_destroy_fn(_p);
		}

	private:
		watch &m_watch;
		array_<base*> m_bases;
		array_<member*> m_members;
		void (*m_destroy_fn)(handle);
		template<typename _Type> static inline void destroy_(handle _p) { ((_Type*)_p)->~_Type(); }
	};

	struct varaible
	{
		array_<uint> path;

		inline varaible(watch &_watch) : m_watch(_watch)
		{
		}
		inline varaible(const varaible &_v) : m_watch(_v.get_watch()), path(_v.path)
		{
		}
		inline varaible& operator = (const varaible &_v)
		{
			this->~varaible(); new(this) varaible(_v); return *this;
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
		inline varaible get_member(const achar *_name) const
		{
			assert(valid());

			type::member &l_member = resolve_member();
			type &l_type = m_watch.get_type(l_member.type);
			uint l_i = l_type.find_member(_name);

			if (l_i == bad_ID) return varaible(m_watch);

			varaible l_v = *this;
			l_v.path.push_back(l_i);

			return l_v;
		}
		inline varaible operator [] (const achar *_name) const
		{
			return get_member(_name);
		}
		template<typename _T> struct _get_helper_
		{
			static inline _T get(const varaible &l_v, bool _byval)
			{
				if (_byval)
				{
					_T l_value; l_value.~_T(); l_v.resolve_get(&l_value); return l_value;
				}
				_T* l_value; l_v.resolve_get(&l_value); return *l_value;
			}
		};
		template<typename _T> struct _get_helper_<_T*>
		{
			static inline _T* get(const varaible &l_v, bool _byval)
			{
				if (_byval)
				{
					std::cerr << "ERROR: (Watch) An attempt to get pointer to temporary value\n"; assert(0); return (_T*)0;
				}
				_T* l_value; l_v.resolve_get(&l_value); return l_value;
			}
		};
		template<typename _T> struct _get_helper_<_T&>
		{
			static inline _T& get(const varaible &l_v, bool _byval)
			{
				if (_byval)
				{
					std::cerr << "ERROR: (Watch) An attempt to get reference to temporary value\n"; assert(0); return *(_T*)0;
				}
				_T* l_value; l_v.resolve_get(&l_value); return *l_value;
			}
		};
		template<typename _Type> _Type get_() const
		{
			assert(!path.empty());

			type::member &l_member = resolve_member();
			type &l_type = m_watch.get_type(l_member.type);

			if (l_type.ID == get_ID_of_<_Type>() || l_type.ID == get_ID_of_<traits_<_Type>::pointed>() || l_type.ID == get_ID_of_<traits_<_Type>::referred>())
			{
				return _get_helper_<_Type>::get(*this, l_member.get->by_value);
			}

			std::cerr << "ERROR: (Watch) An attempt get value of wrong type\n";

			return *(traits_<_Type>::referred*)0;
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
		void resolve_get(handle _value) const
		{
			uint l_type = 0;
			handle l_object = 0;
			bool l_destroy_object = false;
			for (uint i = 0, s = path.size(); i < s; ++i)
			{
				uint l_step = path[i];
				type &l_object_type = m_watch.get_type(l_type);
				type::member &l_member = l_object_type.get_member(l_step);

				handle l_value = i + 1 < s ? calloc(l_member.get->value_size, 1) : _value;
				(*l_member.get)(l_value, l_object_type.member_base_cast(l_step, l_object));

				if (l_destroy_object) l_object_type.destroy_value(l_object);

				if (i + 1 == s) return;

				if (l_member.get->by_value) { l_object = l_value; l_destroy_object = true; }
				else { l_object = *(void**)l_value; l_destroy_object = false; }

				l_type = l_member.type;
			}
		}
		void resolve_set(pointer _value) const
		{
			uint l_type = 0;
			handle l_object = 0;
			bool l_destroy_object = false;
			for (uint i = 0, s = path.size(); i < s; ++i)
			{
				uint l_step = path[i];
				type &l_object_type = m_watch.get_type(l_type);
				type::member &l_member = l_object_type.get_member(l_step);

				handle l_value = 0;

				if (i + 1 < s)
				{
					l_value = calloc(l_member.get->value_size, 1);
					(*l_member.get)(l_value, l_object_type.member_base_cast(l_step, l_object));
				}
				else
				{
					(*l_member.set)(_value, l_object_type.member_base_cast(l_step, l_object));
				}

				if (l_destroy_object) l_object_type.destroy_value(l_object);

				if (i + 1 == s) return;

				if (l_member.get->by_value) { l_object = l_value; l_destroy_object = true; }
				else { l_object = *(void**)l_value; l_destroy_object = false; }

				l_type = l_member.type;
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
					std::cerr << "WARNING: (Watch) Type '" << _name << "' redefines type '" << l_type.name << "'\n";
					l_type.name = _name;
				}
				return type::_helper_<_Type>(l_type);
			}
		}

		m_types.push_back(new type(*this));

		type &l_type = *m_types.back();
		l_type.name = _name;
		l_type.ID = get_ID_of_<_Type>();
		l_type.set_destroy_<_Type>();

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

		assert(l_root.base_count() == 0);

		type::_helper_<_Type>(l_root).add_member(_v, _name);

		varaible l_v(*this);
		l_v.path.push_back(l_root.member_count() - 1);

		return l_v;
	}
	varaible find_varaible(const achar *_path)
	{
		assert(!m_types.empty());

		astring l_path = _path;
		astring l_name = l_path.substr(0, l_path.find("::"));
		l_path.erase(0, l_name.length() + 2);
		type &l_root = *m_types[0];
		uint l_i = l_root.find_member(l_name.c_str());

		if (l_i == bad_ID) return varaible(*this);

		varaible l_v(*this);
		l_v.path.push_back(l_i);

		while (l_path != "")
		{
			l_name = l_path.substr(0, l_path.find("::"));
			l_path.erase(0, l_name.length() + 2);

			l_v = l_v[l_name.c_str()];
		}

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