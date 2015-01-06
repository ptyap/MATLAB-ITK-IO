Description:
MATLAB MEX files for reading/writing ITK supported image files.

Required Packages:

CMake (Version 2.6 or newer)
http://www.cmake.org
(Linux: Set CMAKE_EXE_LINKER_FLAGS = -stdlib=libc++)

Insight Toolkit (ITK, version 4 or newer)
http://www.itk.org

Installation:

1) mkdir build
2) cd build
3) ccmake ../
4) make
5) sudo make install

Credits:
Based on code written by Matt McCormick: https://github.com/thewtex/matlab-itk-import/tree/master/source