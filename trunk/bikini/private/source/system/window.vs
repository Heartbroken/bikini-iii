/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

struct VS_INPUT {
	float3 p : POSITION;
	float4 c : COLOR0;
};

struct VS_OUTPUT {
	float4 hpos : POSITION0;
	float4 c : COLOR0;
};

VS_OUTPUT main(VS_INPUT _in) {
	VS_OUTPUT l_out = (VS_OUTPUT)0;
	l_out.hpos = float4(_in.p, 1);
	l_out.c = _in.c;
	return l_out;
}