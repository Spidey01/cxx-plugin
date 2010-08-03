#include <CxxPlugin.hxx>
#include "plugin.hxx"
#include <iostream>
#include <stdexcept>

#include <functional>

void f(Plugin *) { std::cout << "function" << std::endl; }

int
main(int argc, char *argv[]) {

    try {
        CxxPlugin plugin("./myplugin", &std::cerr);

        //
        // Classic (funcptr) way of loading functions
        //
        typedef Plugin *(*new_myplugin_funcptr)(void);
        new_myplugin_funcptr new_myplugin;

        new_myplugin = (new_myplugin_funcptr)plugin.load_funcptr("new_myplugin");
        if (!new_myplugin) {
            std::cerr << "Unable to Plugin::load_funcptr()" << std::endl;
            return 1;
        }

        //
        // Modern functor way of loading functions
        //
        typedef std::pointer_to_unary_function<Plugin*, void> delete_myplugin_t;
        delete_myplugin_t delete_myplugin = plugin.load_functor<Plugin*, void>("delete_myplugin");


        //
        // test plugin
        //
        Plugin *p = new_myplugin();
        if (!p) {
            std::cerr << "new_myplugin() returned NULL";
            return 1;
        }
        p->prove();

        delete_myplugin(p);

    } catch (std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

