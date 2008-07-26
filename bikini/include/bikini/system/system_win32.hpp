/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if !defined(_WIN32)
#	error Wrong system include!!!
#endif

//#define _WIN32_WINNT	0x0501
//#define VC_EXTRALEAN
//
//#ifndef _CRT_SECURE_NO_DEPRECATE
//#	define _CRT_SECURE_NO_DEPRECATE
//#endif
//
//// this speeds up windows.h processing dramatically...
//#define NOGDICAPMASKS
//#define OEMRESOURCE
//#define NOATOM
//#define NOCLIPBOARD
//#define NOMEMMGR
//#define NOMETAFILE
//#define NOOPENFILE
//#define NOSERVICE
//#define NOSOUND
//#define NOCOMM
//#define NOKANJI
//#define NOHELP
//#define NOPROFILER
//#define NODEFERWINDOWPOS
//#define NOMCX
//#define NOMINMAX
//
//#include <windows.h>

#define D3D_DEBUG_INFO
#include <d3d9.h>
//
//#ifdef min
//#	undef min
//#endif
//
//#ifdef max
//#	undef max
//#endif
//
//#ifdef _T
//#	undef _T
//#endif
//
//#ifdef UNICODE
//#	undef UNICODE
//#endif
//
///// bad GUID
//const GUID bad_GUID = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
