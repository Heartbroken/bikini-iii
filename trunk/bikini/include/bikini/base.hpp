#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "base_d")
#else
#	pragma comment(lib, "base")
#endif

#ifdef WIN32

#	define _WIN32_WINNT	0x0500
#	define VC_EXTRALEAN

#	ifndef _CRT_SECURE_NO_DEPRECATE
#		define _CRT_SECURE_NO_DEPRECATE
#	endif

// this speeds up windows.h processing dramatically...
#	define NOGDICAPMASKS
#	define OEMRESOURCE
#	define NOATOM
#	define NOCLIPBOARD
#	define NOMEMMGR
#	define NOMETAFILE
#	define NOOPENFILE
#	define NOSERVICE
#	define NOSOUND
#	define NOCOMM
#	define NOKANJI
#	define NOHELP
#	define NOPROFILER
#	define NODEFERWINDOWPOS
#	define NOMCX
#	define NOMINMAX

#	include <windows.h>

#endif

#include "config.hpp"
#include "base\types.hpp"