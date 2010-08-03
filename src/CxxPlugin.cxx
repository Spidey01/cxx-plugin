/** 
 * @file
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
 */

#include <CxxPlugin.hxx>
#include <CxxPluginPlatform.h>

#include <stdexcept>

CxxPlugin::CxxPlugin(const std::string& pluginFile, std::ostream *stream)
    : filename(pluginFile),
      errstream(stream)
{
    filename.append(CXXPLUGIN_SO_EXT);

    if (!load_lib()) {
        std::string msg = "Failed to load library: ";
        msg.append(filename);

        if (errstream) {
            *errstream << msg << std::endl;
        }
        throw std::runtime_error(msg);
    }

}

CxxPlugin::~CxxPlugin()
{

#ifdef CXXPLUGIN_OS_WINDOWS
    if (FreeLibrary(plugin) != 0) {
        if (errstream) {
            // TODO: something useful here...
            //*errstream << msg << filename << ": " << GetLastError() << std::endl;
        }
    }
#elif defined(CXXPLUGIN_OS_POSIX) || defined(CXXPLUGIN_OS_MACOS)
    if (dlclose(plugin) == -1) {
        if (errstream) {
            *errstream << dlerror() << std::endl;
        }
    }
#endif
}

bool CxxPlugin::load_lib()
{

#ifdef CXXPLUGIN_OS_WINDOWS
    if ((plugin = LoadLibrary(filename.c_str())) == NULL) {
        return false;
    }
#elif defined(CXXPLUGIN_OS_POSIX) || defined(CXXPLUGIN_OS_MACOS)
    if ((plugin = dlopen(filename.c_str(), RTLD_NOW)) == NULL) {
        return false;
    }
#endif

    return true;
}

std::ostream *CxxPlugin::set_error_stream(std::ostream *stream)
{
    std::ostream *os = errstream;
    errstream = stream;
    return os;
}

void *CxxPlugin::load_funcptr(const char *funcname)
{

#ifdef CXXPLUGIN_OS_WINDOWS
    return GetProcAddress(plugin, funcname);
#elif defined(CXXPLUGIN_OS_POSIX) || defined(CXXPLUGIN_OS_MACOS)
    return dlsym(plugin, funcname);
#endif

}

