---
title: Orientation
parent: Welcome
layout: page
permalink: /orientation
nav_order: 4
---
# Finding your way
This is an introduction to the mathplot repository; what's in each directory and why they are there.

First off, the library is header-only, which means that you don't need to compile it to include it in your programs. You just `#include` the relevant headers in your own `.cpp` files. All the header files that you need to include are in **mathplot/morph**.

However, there are many **test** and **example** programs that can be built, and some **standalone_examples** to help you to write CMake configurations that will build your program with mathplot.

At the time of writing, if you clone mathplot, change directory into its root and type `ls`, then you'll see something like this:

![An image of the following listing of directories and files:
build           examples     README.build.compiler.md  README.md
buildtools      fonts        README.build.linux.md     README.svg_boundaries.md
ci_scripts      include      README.build.mac.md       RRID.md
CMakeLists.txt  LICENSE.txt  README.build.windows.md   shaders
docs            maths        README.cmake.md           tests
doxygen         mplot        README.contributing.md    vcpkg
]

The files in the root directory include some markdown/readme files (*.md), some cmake configuration files (CMakeLists.txt, cmake_cmd_windows.txt, CMakeSettings.seb.json), the license file, a valgrind suppression file for debugging and a number of glsl files that probably belong elsewhere.

The sub-directories are:

* **build/** The build directory. This won't exist if you just cloned, but you'll probably create it
* **buildtools/** Holds a tool called incbin which can be used when working on MS Windows
* **docs/** This documentation/reference website is in here and is automatically published on github pages
* **examples/** All the example programs that demonstrate the use of the headers in `mplot/`
* **fonts/** Holds a copy of the dejavu and ttf-bitstream-vera font files that mathplot builds into your binaries
* **include/** Any third party header code lives in here
* **maths/** This is a git-submodule. You should have recursively cloned, in which case it will contain [Seb's maths](https://github.com/sebsjames/maths)
* **mplot/** All the library headers are in here
* **tests/** This contains test programs that can be run with `ctest` or `make test`

## mplot/

Most of mathplot is in the base namespace `mplot` and their files are at the base of **mplot/**. This is regardless of whether they are code for drawing visualizations or core maths code. Most classes are in a single `.h` header file with the same name as the class, although there are a few exceptions (such as **Random.h**, which contains several classes including ``morph::RandUniform`` and ``morph::RandNormal``).

Files called `XxxVisual.h` are classes that derive from `mplot::VisualModel`. This means that they are models that you can incorporate into your `mplot::Visual` scene. For example, `TriaxesVisual.h` is for drawing a 3D axis into which you can place a 3D scatter or quiver plot. `ColourbarVisual.h` helps you to draw a colour bar legend to display alongside one of your graphs.

Sub-directories in **mplot/** are:

* **mplot/fonts/** Fonts header code (verafonts.h encodes the fonts for Windows compilations)
* **mplot/gl/** Mathplot GL code (`mplot::gl`), including code for running GL compute shaders
* **mplot/glad/** The GLAD GL headers
* **mplot/healpix/** Third party healpix code, slightly modified to work within our mathematical framework, for HEALPix visualization
* **mplot/jcvoronoi/** Third party healpix code, slightly modified to work within our mathematical framework for Voronoi grids
* **mplot/qt/** Some classes to make it possible to incorporate mathplot OpenGL graphics in Qt programs (`mplot::qt`)
* **mplot/wx/** Classes to incorporate mathplot OpenGL graphics in wxWidgets and wxWindows programs (`mplot::wx`)