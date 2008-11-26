/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// shape

shape::shape(const info &_info, player &_player) :
	player::object(_info, _player)
{
	//player &l_player = get_player();
	//if(l_player.exists(m_swfstream_ID)) {
	//	swfstream &l_stream = l_player.get<swfstream>(m_swfstream_ID);
	//	if(l_stream.good()) {
	//		m_rect = l_stream.RECT();
	//		assert(_type == tag::DefineShape4);
	//		rect l_edgebound = l_stream.RECT();
	//		uint l_reserved = l_stream.UB(6);
	//		uint l_nonscalingstrokes = l_stream.UB(1);
	//		uint l_scalingstrokes = l_stream.UB(1);
	//		{ // read fill styles
	//			uint l_count = l_stream.UI8();
	//			if(l_count == 0xff) l_count = l_stream.UI16();
	//			for(uint i = 0; i < l_count; ++i) {
	//				uint l_type = l_stream.UI8();
	//				switch(l_type) {
	//					case 0x00 : {
	//						color l_c = (_type > tag::DefineShape2) ? l_stream.RGBA() : l_stream.RGB();
	//						uint a=0;
	//					} break;
	//				}
	//				l_stream.align();
	//			}
	//		}
	//		{ // read line styles
	//			uint l_count = l_stream.UI8();
	//			if(l_count == 0xff) l_count = l_stream.UI16();
	//			for(uint i = 0; i < l_count; ++i) {
	//				uint l_width = l_stream.UI16();
	//				uint l_startcapstyle = l_stream.UB(2);
	//				uint l_joinstyle = l_stream.UB(2);
	//				uint l_hasfillflag = l_stream.UB(1);
	//				uint l_nohscaleflag = l_stream.UB(1);
	//				uint l_novscaleflag = l_stream.UB(1);
	//				uint l_pixelhintingflag = l_stream.UB(1);
	//				uint l_reservedflag = l_stream.UB(5);
	//				uint l_noclose = l_stream.UB(1);
	//				uint l_endcapstyle = l_stream.UB(2);
	//				if(l_joinstyle == 2) {
	//					uint l_miterlimitfactor = l_stream.UI16();
	//				}
	//				if(l_hasfillflag == 0) {
	//					color l_color = l_stream.RGBA();
	//				}
	//				if(l_hasfillflag == 1) {
	//					//
	//				}
	//				l_stream.align();
	//			}
	//		}
	//		uint l_numfillbits = l_stream.UB(4);
	//		uint l_numlinebits = l_stream.UB(4);
	//		// read shape records
	//		while(true) {
	//			uint l_type = l_stream.UB(1);
	//			if(l_type == 0) {
	//				uint l_newstyles = l_stream.UB(1);
	//				uint l_linestyle = l_stream.UB(1);
	//				uint l_fillstyle1 = l_stream.UB(1);
	//				uint l_fillstyle0 = l_stream.UB(1);
	//				uint l_moveto = l_stream.UB(1);
	//				if(l_newstyles + l_linestyle + l_fillstyle1 + l_fillstyle0 + l_moveto == 0) break;
	//				if(l_moveto) {
	//					uint l_movebits = l_stream.UB(5);
	//					sint l_movex = l_stream.SB(l_movebits);
	//					sint l_movey = l_stream.SB(l_movebits);
	//				}
	//				if(l_fillstyle0) {
	//					uint l_fill0 = l_stream.UB(l_numfillbits);
	//				}
	//				if(l_fillstyle1) {
	//					uint l_fill1 = l_stream.UB(l_numfillbits);
	//				}
	//				if(l_linestyle) {
	//					uint l_line = l_stream.UB(l_numlinebits);
	//				}
	//				if(l_newstyles) {
	//					{ // read fill styles
	//						uint l_count = l_stream.UI8();
	//						if(l_count == 0xff) l_count = l_stream.UI16();
	//						for(uint i = 0; i < l_count; ++i) {
	//							uint l_type = l_stream.UI8();
	//							switch(l_type) {
	//								case 0x00 : {
	//									color l_c = (_type > tag::DefineShape2) ? l_stream.RGBA() : l_stream.RGB();
	//									uint a=0;
	//								} break;
	//							}
	//							l_stream.align();
	//						}
	//					}
	//					{ // read line styles
	//						uint l_count = l_stream.UI8();
	//						if(l_count == 0xff) l_count = l_stream.UI16();
	//						for(uint i = 0; i < l_count; ++i) {
	//							uint l_width = l_stream.UI16();
	//							uint l_startcapstyle = l_stream.UB(2);
	//							uint l_joinstyle = l_stream.UB(2);
	//							uint l_hasfillflag = l_stream.UB(1);
	//							uint l_nohscaleflag = l_stream.UB(1);
	//							uint l_novscaleflag = l_stream.UB(1);
	//							uint l_pixelhintingflag = l_stream.UB(1);
	//							uint l_reservedflag = l_stream.UB(5);
	//							uint l_noclose = l_stream.UB(1);
	//							uint l_endcapstyle = l_stream.UB(2);
	//							if(l_joinstyle == 2) {
	//								uint l_miterlimitfactor = l_stream.UI16();
	//							}
	//							if(l_hasfillflag == 0) {
	//								color l_color = l_stream.RGBA();
	//							}
	//							if(l_hasfillflag == 1) {
	//								//
	//							}
	//							l_stream.align();
	//						}
	//					}
	//					l_numfillbits = l_stream.UB(4);
	//					l_numlinebits = l_stream.UB(4);
	//				}
	//			} else {
	//				uint l_straight = l_stream.UB(1);
	//				uint l_numbits = l_stream.UB(4) + 2;
	//				if(l_straight) {
	//					uint l_generalline = l_stream.UB(1);
	//					uint l_vertline = (l_generalline == 0) ? l_stream.UB(1) : 0;
	//					sint l_deltax = (l_generalline == 1 || l_vertline == 0) ? l_stream.SB(l_numbits) : 0;
	//					sint l_deltay = (l_generalline == 1 || l_vertline == 1) ? l_stream.SB(l_numbits) : 0;
	//				} else {
	//					sint l_cdeltax = l_stream.SB(l_numbits);
	//					sint l_cdeltay = l_stream.SB(l_numbits);
	//					sint l_adeltax = l_stream.SB(l_numbits);
	//					sint l_adeltay = l_stream.SB(l_numbits);
	//				}
	//			}
	//			//l_stream.align();
	//		}
	//	}
	//}
}
shape::~shape() {
}

// shape::info

shape::info::info(swfstream &_s, tag::type _type) : player::object::info(ot::shape) {
		if(_s.good()) {
			m_rect = _s.RECT();
			assert(_type == tag::DefineShape4);
			rect l_edgebound = _s.RECT();
			uint l_reserved = _s.UB(6);
			uint l_nonscalingstrokes = _s.UB(1);
			uint l_scalingstrokes = _s.UB(1);
			{ // read fill styles
				uint l_count = _s.UI8();
				if(l_count == 0xff) l_count = _s.UI16();
				for(uint i = 0; i < l_count; ++i) {
					uint l_type = _s.UI8();
					switch(l_type) {
						case 0x00 : {
							color l_c = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
							uint a=0;
						} break;
					}
					_s.align();
				}
			}
			{ // read line styles
				uint l_count = _s.UI8();
				if(l_count == 0xff) l_count = _s.UI16();
				for(uint i = 0; i < l_count; ++i) {
					uint l_width = _s.UI16();
					uint l_startcapstyle = _s.UB(2);
					uint l_joinstyle = _s.UB(2);
					uint l_hasfillflag = _s.UB(1);
					uint l_nohscaleflag = _s.UB(1);
					uint l_novscaleflag = _s.UB(1);
					uint l_pixelhintingflag = _s.UB(1);
					uint l_reservedflag = _s.UB(5);
					uint l_noclose = _s.UB(1);
					uint l_endcapstyle = _s.UB(2);
					if(l_joinstyle == 2) {
						uint l_miterlimitfactor = _s.UI16();
					}
					if(l_hasfillflag == 0) {
						color l_color = _s.RGBA();
					}
					if(l_hasfillflag == 1) {
						//
					}
					_s.align();
				}
			}
			uint l_numfillbits = _s.UB(4);
			uint l_numlinebits = _s.UB(4);
			// read shape records
			while(true) {
				uint l_type = _s.UB(1);
				if(l_type == 0) {
					uint l_newstyles = _s.UB(1);
					uint l_linestyle = _s.UB(1);
					uint l_fillstyle1 = _s.UB(1);
					uint l_fillstyle0 = _s.UB(1);
					uint l_moveto = _s.UB(1);
					if(l_newstyles + l_linestyle + l_fillstyle1 + l_fillstyle0 + l_moveto == 0) break;
					if(l_moveto) {
						uint l_movebits = _s.UB(5);
						sint l_movex = _s.SB(l_movebits);
						sint l_movey = _s.SB(l_movebits);
					}
					if(l_fillstyle0) {
						uint l_fill0 = _s.UB(l_numfillbits);
					}
					if(l_fillstyle1) {
						uint l_fill1 = _s.UB(l_numfillbits);
					}
					if(l_linestyle) {
						uint l_line = _s.UB(l_numlinebits);
					}
					if(l_newstyles) {
						{ // read fill styles
							uint l_count = _s.UI8();
							if(l_count == 0xff) l_count = _s.UI16();
							for(uint i = 0; i < l_count; ++i) {
								uint l_type = _s.UI8();
								switch(l_type) {
									case 0x00 : {
										color l_c = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
										uint a=0;
									} break;
								}
								_s.align();
							}
						}
						{ // read line styles
							uint l_count = _s.UI8();
							if(l_count == 0xff) l_count = _s.UI16();
							for(uint i = 0; i < l_count; ++i) {
								uint l_width = _s.UI16();
								uint l_startcapstyle = _s.UB(2);
								uint l_joinstyle = _s.UB(2);
								uint l_hasfillflag = _s.UB(1);
								uint l_nohscaleflag = _s.UB(1);
								uint l_novscaleflag = _s.UB(1);
								uint l_pixelhintingflag = _s.UB(1);
								uint l_reservedflag = _s.UB(5);
								uint l_noclose = _s.UB(1);
								uint l_endcapstyle = _s.UB(2);
								if(l_joinstyle == 2) {
									uint l_miterlimitfactor = _s.UI16();
								}
								if(l_hasfillflag == 0) {
									color l_color = _s.RGBA();
								}
								if(l_hasfillflag == 1) {
									//
								}
								_s.align();
							}
						}
						l_numfillbits = _s.UB(4);
						l_numlinebits = _s.UB(4);
					}
				} else {
					uint l_straight = _s.UB(1);
					uint l_numbits = _s.UB(4) + 2;
					if(l_straight) {
						uint l_generalline = _s.UB(1);
						uint l_vertline = (l_generalline == 0) ? _s.UB(1) : 0;
						sint l_deltax = (l_generalline == 1 || l_vertline == 0) ? _s.SB(l_numbits) : 0;
						sint l_deltay = (l_generalline == 1 || l_vertline == 1) ? _s.SB(l_numbits) : 0;
					} else {
						sint l_cdeltax = _s.SB(l_numbits);
						sint l_cdeltay = _s.SB(l_numbits);
						sint l_adeltax = _s.SB(l_numbits);
						sint l_adeltay = _s.SB(l_numbits);
					}
				}
				//_s.align();
			}
		}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
