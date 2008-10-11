/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _First, typename _Rest = notype> struct typelist;
template<typename _First, typename _Second, typename _Third> struct typelist<_First, typelist<_Second, _Third> > {
	typedef _First first;
	typedef typelist<_Second, _Third> rest;

	static const uint count = 1 + rest::count;
	static const uint max_size = sizeof(first) > rest::max_size ? sizeof(first) : rest::max_size;

	template<uint _Index> struct item {
		typedef typename rest::item<_Index - 1>::type type;
		static const uint size = sizeof(type);
	};
	template<> struct item<0> {
		typedef first type;
		static const uint size = sizeof(type);
	};

	template<typename _Type> struct type {
	private:
		typedef typename rest::type<_Type> check_rest;
	public:
		static const uint index = check_rest::index == bad_ID ? bad_ID : 1 + (s32)check_rest::index;
		static const bool exists = check_rest::exists;
	};
	template<> struct type<first> {
		static const uint index = 0;
		static const bool exists = true;
	};

	template<typename _Type> struct append { typedef typelist<first, typename rest::append<_Type>::result> result; };

	template<typename _Otherlist> struct otherlist {
		static const bool belong = type<typename _Otherlist::first>::exists && otherlist<typename _Otherlist::rest>::belong;
		inline static uint remap(uint _i) {
			return _i ? otherlist<typename _Otherlist::rest>::remap(_i - 1) : type<typename _Otherlist::first>::index;
		}
	};
	template<> struct otherlist<typelist<notype> > {
		static const bool belong = true;
		inline static uint remap(uint _i) { return bad_ID; }
	};

	inline static uint size(uint _i) {
		assert(_i < count);
		if(_i) return rest::size(_i - 1);
		return sizeof(first);
	}
	inline static handle construct(uint _i) {
		assert(_i < count);
		if(_i) return rest::construct(_i - 1);
//		else return new first;
		return construct(malloc(sizeof(first)), _i);
	}
	inline static handle construct(uint _i, pointer _v) {
		assert(_i < count);
		if(_i) return rest::construct(_i - 1, _v);
		return construct(malloc(sizeof(first)), _i, _v);
	}
	inline static handle construct(handle _h, uint _i) {
		assert(_i < count);
		if(_i) return rest::construct(_h, _i - 1);
		return new(_h) first;
	}
	inline static handle construct(handle _h, uint _i, pointer _v) {
		assert(_i < count);
		if(_i) return rest::construct(_h, _i - 1, _v);
		return new(_h) first(*reinterpret_cast<const first*>(_v));
	}
	inline static void destruct(handle _h, uint _i, bool _and_free = true) {
		assert(_i < count);
		if(_i) return rest::destruct(_h, _i - 1, _and_free);
		reinterpret_cast<first*>(_h)->~first();
		if(_and_free) free(_h);
	}
	inline static bool compare(uint _i, pointer _a, pointer _b) {
		assert(_i < count);
		if(_i) return rest::compare(_i - 1, _a, _b);
		return *reinterpret_cast<const first*>(_a) == *reinterpret_cast<const first*>(_b);
	}
};

template<> struct typelist<notype> {
	static const uint count = 0;
	static const uint max_size = 0;

	template<uint _Index> struct item {
		typedef typename notype type;
		static const uint size = 0;
	};

	template<typename _Type> struct type {
		static const uint index = bad_ID;
		static const bool exists = false;
	};

	template<typename _Type> struct append { typedef typelist<_Type, typelist<notype> > result; };
	template<typename _First, typename _Rest> struct append<typelist<_First, _Rest> > { typedef typelist<_First, _Rest> result; };

	inline static uint size(uint _i) { return 0; }
	inline static handle construct(uint _i) { return 0; }
	inline static handle construct(uint _i, pointer _v) { return 0; }
	inline static handle construct(handle _h, uint _i, pointer _v) { return 0; }
	inline static handle construct(handle _h, uint _i) { return 0; }
	inline static void destruct(handle _h, uint _i, bool _and_free = true) {}
	inline static bool compare(uint _i, pointer _a, pointer _b) { return false; }
};

template<
	typename _Type0,
	typename _Type01 = notype, typename _Type02 = notype, typename _Type03 = notype, typename _Type04 = notype, typename _Type05 = notype,
	typename _Type06 = notype, typename _Type07 = notype, typename _Type08 = notype, typename _Type09 = notype, typename _Type10 = notype,
	typename _Type11 = notype, typename _Type12 = notype, typename _Type13 = notype, typename _Type14 = notype, typename _Type15 = notype,
	typename _Type16 = notype, typename _Type17 = notype, typename _Type18 = notype, typename _Type19 = notype, typename _Type20 = notype,
	typename _Type21 = notype, typename _Type22 = notype, typename _Type23 = notype, typename _Type24 = notype, typename _Type25 = notype,
	typename _Type26 = notype, typename _Type27 = notype, typename _Type28 = notype, typename _Type29 = notype, typename _Type30 = notype,
	typename _Type31 = notype, typename _Type32 = notype, typename _Type33 = notype, typename _Type34 = notype, typename _Type35 = notype,
	typename _Type36 = notype, typename _Type37 = notype, typename _Type38 = notype, typename _Type39 = notype, typename _Type40 = notype,
	typename _Type41 = notype, typename _Type42 = notype, typename _Type43 = notype, typename _Type44 = notype, typename _Type45 = notype,
	typename _Type46 = notype, typename _Type47 = notype, typename _Type48 = notype, typename _Type49 = notype, typename _Type50 = notype
> struct make_typelist {
	typedef typelist<
		_Type0,
		typename make_typelist<
			_Type01, _Type02, _Type03, _Type04, _Type05, _Type06, _Type07, _Type08, _Type09, _Type10,
			_Type11, _Type12, _Type13, _Type14, _Type15, _Type16, _Type17, _Type18, _Type19, _Type20,
			_Type21, _Type22, _Type23, _Type24, _Type25, _Type26, _Type27, _Type28, _Type29, _Type30,
			_Type31, _Type32, _Type33, _Type34, _Type35, _Type36, _Type37, _Type38, _Type39, _Type40,
			_Type41, _Type42, _Type43, _Type44, _Type45, _Type46, _Type47, _Type48, _Type49, _Type50
		>::type
	> type;
};
template<> struct make_typelist<notype> {
	typedef typelist<notype> type;
};
