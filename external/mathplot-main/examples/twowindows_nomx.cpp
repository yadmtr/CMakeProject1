/*
 * Two windows example using non-multicontext guaranteed headers defining global GL function
 * aliases (i.e. using mplot::VisualNoMX in place of mplot::Visual).
 *
 * It works in practice, but it is safer to use the multicontext-safe GLAD headers with
 * mplot::Visual.
 */
#include <iostream>
#include <array>
#include <stdexcept>
#include <string>

#include <sm/vec>
#include <sm/vvec>

#include <mplot/VisualNoMX.h>
#include <mplot/ColourMap.h>
#include <mplot/QuiverVisual.h>
#include <mplot/GraphVisual.h>

int main()
{
    int rtn = -1;

    // Demonstrates use of offset (left at 0,0,0), lengths (3,2,1) and the 'thickness'
    // scaling factor (0.5) for the coordinate arrows. Defines, and makes current a new
    // window and OpenGL context.
    mplot::VisualNoMX v(1024, 768, "Window 1");
    v.showCoordArrows (true);
    v.showTitle (true);
    v.backgroundWhite();
    v.lightingEffects();

    // If I define a second Visual here, then the OpenGL context will now be 'pointing'
    // at this Visual v2
    mplot::VisualNoMX v2(768, 768, "Graph on Window 2");
    v2.showCoordArrows (true);
    v2.showTitle (true);
    v2.backgroundWhite();
    v2.lightingEffects();

    try {
        // Set up data for the first Visual
        sm::vec<float, 3> offset = { 0.0, 0.0, 0.0 };

        std::vector<sm::vec<float, 3>> coords(20*20);
        std::vector<sm::vec<float, 3>> quivs(20*20);
        sm::vvec<float> qlens(20*20, 0.0f);

        size_t k = 0;
        for (int i = -10; i < 10; ++i) {
            for (int j = -10; j < 10; ++j) {
                float x = 0.1*i;
                float y = 0.1*j;
                // z is some function of x, y
                float z = x * std::exp(-(x*x) - (y*y));
                coords[k] = {x, y, z};
                k++;
            }
        }

        k = 0;
        for (int i = -10; i < 10; ++i) {
            for (int j = -10; j < 10; ++j) {
                if (i > -10 && i < 10 && j > -10 && j < 10) {
                    sm::vec<float> r = coords[k] - coords[k-20];
                    sm::vec<float> g = coords[k] - coords[k-1];
                    // Compute normal and modulate by the distance from the centre
                    quivs[k] = r.cross(g);
                    if (coords[k].length() != 0.0f) { quivs[k] *= 1.0f / (1.2f + coords[k].length()); }
                    qlens[k] = quivs[k].length();
                } else {
                    quivs[k] = {0.0f, 0.0f, 0.0f};
                }
                k++;
            }
        }

        auto qvp = std::make_unique<mplot::QuiverVisual<float>>(&coords, offset, &quivs, mplot::ColourMapType::Jet);
        v.bindmodel (qvp);
        qvp->quiver_length_gain = 1.0f; // Scale the length of the quivers on screen
        qvp->colourScale.compute_scaling(0, qlens.max());
        qvp->quiver_thickness_gain = 0.02f; // Scale thickness of the quivers
        qvp->finalize();
        v.addVisualModel (qvp);

        // Set up v2 with a graph, switching to the Visual v2's context first:
        auto gv = std::make_unique<mplot::GraphVisual<float>> (sm::vec<float>({0,0,0}));
        v2.bindmodel (gv);
        sm::vvec<float> x =  {-.5, -.4, -.3, -.2, -.1, 0, .1, .2, .3, .4, .5, .6, .7, .8};
        sm::vvec<float> y = x.pow(3);
        gv->setdata (x, y);
        gv->finalize();
        v2.addVisualModel (gv);

        while (v.readyToFinish() == false && v2.readyToFinish() == false) {
            v.waitevents (0.018);
            v.render();
            v2.render();
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
