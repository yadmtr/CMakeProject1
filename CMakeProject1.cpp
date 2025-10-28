﻿// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"

using namespace std;

int main()
{

    int rtn = 0;

    // Create a mplot::Visual. This is linked to a window on your desktop when the program runs
    mplot::Visual v(1536, 1536, "A variety of graph formats");
    // Set scene translation to position the graphs in the centre of the window (See Ctrl-z output to stdout)
    v.setSceneTrans(sm::vec<float, 3>({ -1.21382f, 0.199316f, -5.9f }));

    // Some positioning values used to place each of the GraphVisuals:
    constexpr float step = 1.4f;
    constexpr float row2 = 1.2f;

    try {

        // Some example data in mathplot's 'mathematical vector' class, vvec.
        sm::vvec<float> absc = { -.5, -.4, -.3, -.2, -.1, 0, .1, .2, .3, .4, .5, .6, .7, .8 };
        sm::vvec<float> data = absc.pow(3);

        // Graph 1
        auto gv = std::make_unique<mplot::GraphVisual<float>>(sm::vec<float>{0, 0, 0});
        v.bindmodel(gv); // Necessary boilerplate line (hooks up some callbacks in gv)

        // GraphVisuals have a 'data set style' object
        mplot::DatasetStyle ds;
        ds.linecolour = mplot::colour::purple; // See mplot/colour.h for all the colours or
        // http://www.cloford.com/resources/colours/500col.htm
        ds.linewidth = 0.015f;
        ds.markerstyle = mplot::markerstyle::diamond;
        ds.markercolour = mplot::colour::deepskyblue2;
        gv->setdata(absc, data, ds);

        gv->axisstyle = mplot::axisstyle::L;

        // Set labels to include greek characters:
        namespace uc = mplot::unicode;
        gv->xlabel = "Include unicode symbols like this: " + uc::toUtf8(uc::alpha);
        gv->ylabel = "Unicode for Greek gamma is 0x03b3: " + uc::toUtf8(uc::gamma);

        gv->setthickness(0.001f);
        gv->finalize();
        v.addVisualModel(gv);

        // Graph 2
        gv = std::make_unique<mplot::GraphVisual<float>>(sm::vec<float>({ step,0,0 }));
        v.bindmodel(gv);
        sm::vvec<float> data2 = absc.pow(2);
        ds.linecolour = mplot::colour::royalblue;
        ds.markerstyle = mplot::markerstyle::hexagon;
        ds.markercolour = mplot::colour::black;
        gv->setdata(absc, data2, ds);
        gv->axisstyle = mplot::axisstyle::box;
        gv->ylabel = "mm";
        gv->xlabel = "Abscissa (notice that mm is not rotated)";
        gv->setthickness(0.005f);
        gv->finalize();
        v.addVisualModel(gv);

        gv = std::make_unique<mplot::GraphVisual<float>>(sm::vec<float>({ 0,-row2,0 }));
        v.bindmodel(gv);
        sm::vvec<float> data3 = absc.pow(4);
        gv->setsize(1, 0.8);
        ds.linecolour = mplot::colour::cobaltgreen;
        ds.markerstyle = mplot::markerstyle::circle;
        ds.markercolour = mplot::colour::white;
        ds.markersize = 0.02f;
        ds.markergap = 0.0f;
        gv->setdata(absc, data3, ds);
        gv->axisstyle = mplot::axisstyle::boxfullticks;
        gv->tickstyle = mplot::tickstyle::ticksin;
        gv->ylabel = "mmi";
        gv->xlabel = "mmi is just long enough to be rotated";
        gv->setthickness(0.001f);
        gv->finalize();
        v.addVisualModel(gv);

        gv = std::make_unique<mplot::GraphVisual<float>>(sm::vec<float>({ step,-row2,0 }));
        v.bindmodel(gv);
        absc.resize(1000, 0.0f);
        for (int i = 0; i < 1000; ++i) {
            absc[i] = static_cast<float>(i - 500) * 0.01f;
        }
        gv->setsize(1, 0.8);
        ds.linecolour = mplot::colour::crimson;
        ds.markerstyle = mplot::markerstyle::none;
        ds.markergap = 0.0f;
        ds.linewidth = 0.005f;
        gv->setdata(absc, absc.pow(5), ds);
        gv->axisstyle = mplot::axisstyle::cross;
        gv->setthickness(0.002f);
        gv->finalize();
        v.addVisualModel(gv);

        // Display until user closes window
        v.keepOpen();

    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;


	/*cout << "Hello CMake." << endl;
	return 0;*/
}

//include_directories(BEFORE ${ PROJECT_SOURCE_DIR } / imgui)            # Imgui
//include_directories(BEFORE ${ PROJECT_SOURCE_DIR } / imgui / backends)   #
//
//# If you want to add another directory to your include path, you can add an extra include_directories call :
//# include_directories(BEFORE ${ PROJECT_SOURCE_DIR } / my_includes)
//
//#
//# All the library finding is now done.It's time to compile the program.
//#
//
//set(IMGUI_SOURCES imgui / imgui.cpp
//    imgui / backends / imgui_impl_glfw.cpp imgui / backends / imgui_impl_opengl3.cpp
//    imgui / imgui_widgets.cpp imgui / imgui_tables.cpp imgui / imgui_draw.cpp imgui / imgui_demo.cpp)
//    # The sample is compiled from a single c++ file along with the ImGui sources
//    add_executable(prog1 prog1.cpp ${ IMGUI_SOURCES })
//
//


