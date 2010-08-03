#ifndef MYPLUGIN_HPP
#define MYPLUGIN_HPP

#include "plugin.hxx"

class CXXPLUGIN_API MyPlugin : public Plugin {
  public:
    virtual ~MyPlugin() {}
    void prove();
};

extern "C" {
    CXXPLUGIN_API Plugin *new_myplugin(void);
    CXXPLUGIN_API void delete_myplugin(Plugin *);
}

#endif
