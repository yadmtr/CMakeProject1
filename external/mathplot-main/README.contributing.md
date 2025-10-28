# Contributing to mathplot

## Different ways to contribute

You can offer to help with library code, example programs, unit tests,
documentation and continuous integration or even just requests for
features.

## Who might want to contribute

If you're interested in drawing fast graphics for data visualization
using C++, then you should take a look at this project. Right now, the
library can draw 2D graphs and a range of 3D plots including surfaces,
scatter plots and quiver plots. It's extensible, and is easily adapted
to draw agents in a 3D world, so it leds itself to robotics
simulations too.

You can learn about how a complete OpenGL library can be built from
this project. You can also look at the way the authors have designed
the mathematics code. The project provides a good example of a CMake
build system

## Contributing code

You can start by examining the example programs
(**mathplot/examples/**). Most examples demonstrate the use of one or more
of the 'VisualModels' in **mathplot/mplot/**. See if you can find
something that you want to do that isn't implemented already and open
an issue to discuss how that could be added.

If you're ready to write some code, fork the project and then create
your PR.

## Contributing documentation

The code documentation is provided as a github pages site, which is
generated from the files in mathplot/docs/

If you install ruby and jekyll on your local machine, you can run the
site locally. See **mathplot/docs/run_local.sh**.

First install dependencies:
```bash
sudo apt install ruby ruby-dev
gem install --install-dir ~/gems bundler jekyll jekyll-default-layout just-the-docs github-pages
```
Then run

```bash
pushd docs
./run_local.sh
```

Now you can navigate to http://127.0.0.1:4000/ to view the docs

You can edit the content by changing files like:

**mathplot/docs/ref/visualmodels/gridvisual.md**

The files are written in markdown.