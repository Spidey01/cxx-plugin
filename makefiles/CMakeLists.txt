cmake_minimum_required(VERSION 3.13)

project(cxx-plugin)

## normally would be in src/CMakeLists.txt
add_library(CxxPlugin STATIC src/CxxPlugin.cxx)
target_include_directories(CxxPlugin PUBLIC include)

#
## normally would be in tests/CMakeLists.txt
#

add_library(myplugin SHARED tests/myplugin.cpp)
if (UNIX)
    set_target_properties(myplugin PROPERTIES PREFIX "")
endif()
target_include_directories(myplugin PUBLIC include)

# 3.13 doesn't care, but 3.7 on Debian old stable reserves "test".
# If you want to use old CMake, rename it below.
#
add_executable(test tests/test.cpp)
target_link_libraries(test PUBLIC CxxPlugin)
if (UNIX)
    target_link_libraries(test PUBLIC -ldl)
endif()
