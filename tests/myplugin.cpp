#include "myplugin.hpp"

#include <iostream>

CXXPLUGIN_API void
MyPlugin::prove()
{
    std::cout << "MyPlugin::prove() called" << std::endl;
}

extern "C" CXXPLUGIN_API Plugin *
new_myplugin(void)
{
    return new MyPlugin;
}

extern "C" CXXPLUGIN_API void
delete_myplugin(Plugin *p)
{
    std::cout << "delete MyPlugin" << std::endl;
    delete p;
}

