#ifndef CXXPLUGIN_PLATFORM_H
#define CXXPLUGIN_PLATFORM_H

/** 
 * @file
 * @brief Platform specifics for CxxPlugin
 * @author Terry Matthew Poulin
 *
 * @section LICENSE
 *
 * Copyright (c) 2009-2010 Terry Matthew Poulin.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This simple header takes a guess at the current platform.
 * Currently Windows NT and POSIX style environments are supported.
 *
 * Provides the following:
 * 	- CXXPLUGIN_HANDLE_T
 * 		the correct type for this platforms idea of a dlopen()'d handle
 * 	- CXXPLUGIN_SO_EXT
 * 		the file extension (e.g. '.dll') used for the plugin file.
 * 	- CXXPLUGIN_OS_NAME
 * 		currently configure for an OS named NAME. 
 * 		Typically NAME is WINDOWS or POSIX. (e.g. CXXPLUGIN_OS_POSIX)
 * 	- CXXPLUGIN_API
 * 		any platform specific type declarations (e.g. dllexport)
 * 	- Any headers needed to use the systems idea of dlfcn.h and company.
 */

#if defined(_WIN32) || defined(__WIN64) || defined(IS_WINDOWS)
#	define CXXPLUGIN_HANDLE_T 	HMODULE
#	define CXXPLUGIN_SO_EXT		".dll"
#	define CXXPLUGIN_OS_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#	define CXXPLUGIN_API __declspec(dllexport)
#elif defined(__APPLE__)	/* likely must come before the POSIX check */
#	define CXXPLUGIN_HANDLE_T 	void *
#	define CXXPLUGIN_SO_EXT		".dylib"
#	define CXXPLUGIN_OS_MACOS
#	include <dlfcn.h>
#	define CXXPLUGIN_API /* assumed to be sane */
#	error "Hmm, what happened to POSIX compliance..."
#elif defined(_POSIX_VERSION) || defined(__unix__) || defined(IS_UNIX)
#	define CXXPLUGIN_HANDLE_T 	void *
#	define CXXPLUGIN_SO_EXT		".so"
#	define CXXPLUGIN_OS_POSIX
#	include <dlfcn.h>
#	define CXXPLUGIN_API /* sane */
#else
#   error "Unknown platform, please port me!"
#endif

#endif

