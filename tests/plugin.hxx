#ifndef PLUGIN_HXX
#define PLUGIN_HXX

#include "CxxPluginPlatform.h"

class CXXPLUGIN_API Plugin {
  public:
    virtual ~Plugin() {}
    virtual void prove() = 0;
};

#endif
