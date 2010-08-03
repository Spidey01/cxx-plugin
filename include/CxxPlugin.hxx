#ifndef CXXPLUGIN_HXX
#define CXXPLUGIN_HXX

/** 
 * @file
 * @brief A C++ interface to using "Plugins"
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


#include "CxxPluginPlatform.h"

#include <functional>
#include <ostream>
#include <string>

/** A simple class representing a C/C++ plugin.
 *
 * The plugin is loaded when a CxxPlugin is constructed, and *may* be
 * unloaded when the object is destructed. The exact unloading behaviour is
 * dependent upon the operating system.
 *
 * There are two principal ways of extracting function out of the plugin:
 *      - raw function pointers
 *      - templated function objects (functors)
 *
 *  Using raw function pointers is the standard C style interface, and should
 *  be depreciated in modern C++ code.
 *
 *  Using functors ...
 */

class CxxPlugin {
  public:

    /** Creates a new CxxPlugin
     *
     * @param pluginFile the pathname of the plugin to be loaded, sans 
     *                   any file extension
     *
     * @param stream if supplied, stream is used for logging errors.
     *               the default is not to log errors.
     *
     * @throws std::runtime_error if loading pluginFile failed.
     */

    CxxPlugin(const std::string& pluginFile, std::ostream *stream=NULL);

    ~CxxPlugin();

    /** Sets the error stream used for logging errors.
     *
     * @returns the previously set error stream or NULL.
     */

    std::ostream *set_error_stream(std::ostream *stream);

    /** Loads a function out of the plugin
     *
     * @returns a function pointer to a function named 'funcname' or NULL 
     *          on error.
     */

    void *load_funcptr(const char *funcname);

    /** Loads a unary function out of the plugin and returns a function object.
     *
     * @returns a function object encapsulating a function named 'funcname'.
     */

    template <typename Arg, typename Result> 
        std::pointer_to_unary_function<Arg, Result>
        load_functor(const char *funcname)
        // inlined to be more VC6 friendly :-S
    {
        return std::ptr_fun((Result (*)(Arg))load_funcptr(funcname));
    }

    /** Loads a binary function out of the plugin and returns a function object.
     *
     * @returns a function object encapsulating a function named 'funcname'.
     */

    template <typename Arg1, typename Arg2, typename Result>
        std::pointer_to_binary_function<Arg1, Arg2, Result>
        load_functor(const char *funcname)
    {
        return std::ptr_fun((Result (*)(Arg1, Arg2))load_funcptr(funcname));
    }

  private:
    bool load_lib();

    /** name of the plugin file */
    std::string filename;

    /** platform specific handle for a dynamically linked (plugged in) library */
    CXXPLUGIN_HANDLE_T plugin;

    /** output stream used for logging errors */
    std::ostream *errstream;
};

#endif

