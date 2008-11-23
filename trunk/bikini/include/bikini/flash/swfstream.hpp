/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct swfstream : player::object {
	struct record {
		tag::code type; uint length;
	};
	struct info : player::object::info {
		typedef swfstream object;
		typedef const wchar* a0;
		info();
	};
	inline const wstring& get_path() const { return m_path; }
	inline uint get_position() const { return m_position; }
	inline bool good() const { return m_file_ID != bad_ID; }
	swfstream(const info &_info, player &_player, const wchar* _path);
	~swfstream();
	uint seek(sint _offset = 0, uint _from = 1);
	void align();
	u8 BYTE();
	bool BIT();
	uint UI8();
	uint UI16();
	uint UI32();
	ubig UI64();
	sint SI8();
	sint SI16();
	sint SI32();
	sbig SI64();
	uint EncodedU32();
	real FIXED();
	real FIXED8();
	real FLOAT16();
	real FLOAT();
	rbig DOUBLE();
	uint UB(uint _size);
	sint SB(uint _size);
	real FB(uint _size);
	wstring STRING();
	color RGB();
	color RGBA();
	color ARGB();
	rect RECT();
	r3x2 MATRIX();
	cxform CXFORM();
	cxform CXFORMWITHALPHA();
	record RECORD();
private:
	wstring m_path;
	uint m_file_ID, m_position;
	u8 m_byte, m_bit;
	uint m_version, m_length;
	bool m_compressed;
};
