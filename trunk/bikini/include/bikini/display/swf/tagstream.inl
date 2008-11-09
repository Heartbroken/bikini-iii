/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/*
inline bitstream::bitstream(u8 *_buffer, uint _byte, uint _bit) :
	m_buffer(_buffer), m_byte(_byte), m_bit(min(_bit, uint(7)))
{}
inline uint bitstream::get_UI8() {
	align();
	u8 l_b0 = m_buffer[m_byte++];
	return uint(l_b0);
}
inline uint bitstream::get_UI16() {
	align();
	u8 l_b0 = m_buffer[m_byte++], l_b1 = m_buffer[m_byte++];
	return uint(l_b0) + uint(l_b1 << 8);
}
inline uint bitstream::get_UI32() {
	align();
	u8 l_b0 = m_buffer[m_byte++], l_b1 = m_buffer[m_byte++], l_b2 = m_buffer[m_byte++], l_b3 = m_buffer[m_byte++];
	return uint(l_b0) + uint(l_b1 << 8) + uint(l_b2 << 16) + uint(l_b3 << 24);
}
inline ubig bitstream::get_UI64() {
	align();
	u8 l_b0 = m_buffer[m_byte++], l_b1 = m_buffer[m_byte++], l_b2 = m_buffer[m_byte++], l_b3 = m_buffer[m_byte++];
	u8 l_b4 = m_buffer[m_byte++], l_b5 = m_buffer[m_byte++], l_b6 = m_buffer[m_byte++], l_b7 = m_buffer[m_byte++];
	return ubig(l_b0) + ubig(l_b1 << 8) + ubig(l_b2 << 16) + ubig(l_b3 << 24) + (ubig(l_b4) << 32) + (ubig(l_b5) << 40) + (ubig(l_b6) << 48) + (ubig(l_b7) << 56);
}
inline sint bitstream::get_SI8() {
	return sint(get_UI8());
}
inline sint bitstream::get_SI16() {
	return sint(get_UI16());
}
inline sint bitstream::get_SI32() {
	return sint(get_UI32());
}
inline sbig bitstream::get_SI64() {
	return sbig(get_UI64());
}
inline uint bitstream::get_EUI32() {
	align();
	uint l_result = m_buffer[m_byte];
	if((l_result & 0x80) == 0) { m_byte += 1; return l_result; }
	l_result = (l_result & 0x7f) | (m_buffer[m_byte + 1] << 7);
	if((l_result & 0x4000) == 0) { m_byte += 2; return l_result; }
	l_result = (l_result & 0x3fff) | (m_buffer[m_byte + 2] << 14);
	if((l_result & 0x200000) == 0) { m_byte += 3; return l_result; }
	l_result = (l_result & 0x1fffff) | (m_buffer[m_byte + 3] << 21);
	if((l_result & 0x10000000) == 0) { m_byte += 4; return l_result; }
	l_result = (l_result & 0x0fffffff) | (m_buffer[m_byte + 5] << 28);
	m_byte += 5; return l_result;
}
inline real bitstream::get_FIXED16() {
	uint l_fraction = get_UI8(), l_integer = get_SI8();
	return real(l_integer) + real(l_fraction) / real(u8(-1));
}
inline real bitstream::get_FIXED32() {
	uint l_fraction = get_UI16(), l_integer = get_SI16();
	return real(l_integer) + real(l_fraction) / real(u16(-1));
}
inline real bitstream::get_FLOAT16() {
	u8 l_b0 = m_buffer[m_byte++], l_b1 = m_buffer[m_byte++];
	u32 l_m = l_b0 + ((l_b1 & 0x3) << 7), l_e = (l_b1 & 0x7c) >> 2, l_s = l_b1 >> 7;
	union _f32_helper { f32 _f32; u32 _u32; };
	_f32_helper l_f; l_f._u32 = (l_s << 31) | (l_e << 23) | l_m;
	return real(l_f._f32);
}
inline real bitstream::get_FLOAT32() {
	u32 l_result = (u32)get_UI32();
	return real(*(f32*)&l_result);
}
inline rbig bitstream::get_FLOAT64() {
	u64 l_result = (u64)get_UI64();
	return rbig(*(f64*)&l_result);
}
inline uint bitstream::get_UB(uint _n) {
	assert(_n <= 32);
	u8 l_byte = m_buffer[m_byte];
	uint l_result = 0;
	while(_n--) {
		uint l_bit = (l_byte & (1 << m_bit)) ? 1 : 0;
		l_result = (l_result << 1) | l_bit;
		--m_bit;
		if(m_bit == 0) {
			l_byte = m_buffer[++m_byte];
			m_bit = 7;
		}
	}
	return l_result;
}
inline sint bitstream::get_SB(uint _n) {
	assert(_n <= 32);
	u8 l_byte = m_buffer[m_byte];
	uint l_result = (l_byte & (1 << m_bit)) ? uint(-1) : 0;
	while(_n--) {
		uint l_bit = (l_byte & (1 << m_bit)) ? 1 : 0;
		l_result = (l_result << 1) | l_bit;
		--m_bit;
		if(m_bit == 0) {
			l_byte = m_buffer[++m_byte];
			m_bit = 7;
		}
	}
	return sint(l_result);
}
inline real bitstream::get_FB(uint _n) {
	assert(_n <= 32);
	u8 l_byte = m_buffer[m_byte];
	uint l_integer = (l_byte & (1 << m_bit)) ? uint(-1) : 0;
	uint l_fraction = 0;
	while(_n--) {
		uint l_bit = (l_byte & (1 << m_bit)) ? 1 : 0;
		if(_n < 16) l_fraction = (l_fraction << 1) | l_bit;
		else l_integer = (l_integer << 1) | l_bit;
		--m_bit;
		if(m_bit == 0) {
			l_byte = m_buffer[++m_byte];
			m_bit = 7;
		}
	}
	return real(sint(l_integer)) + real(l_fraction) / real(u16(-1));
}
inline void bitstream::align(uint _bytes) {
	if(m_bit < 7) { ++m_byte; m_bit = 7; }
	if(m_byte % _bytes > 0) m_byte += _bytes - m_byte % _bytes;
}
inline u8 bitstream::read_byte() {
	return m_buffer[m_byte++];
}
inline bool bitstream::read_bit() {
	bool l_bit = (m_buffer[m_byte] & (1 << m_bit)) > 0;
	if(m_bit == 0) ++m_byte, m_bit = 7; else --m_bit;
	return l_bit;
}
*/