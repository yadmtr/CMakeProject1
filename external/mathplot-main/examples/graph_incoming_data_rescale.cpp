/*
 * Visualize a graph on which points are added with time.
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>

#include <sm/vec>
#include <sm/vvec>

#include <mplot/Visual.h>
#include <mplot/ColourMap.h>
#include <mplot/GraphVisual.h>

int main()
{
    namespace uc = mplot::unicode;

    int rtn = -1;

    mplot::Visual v(1024, 768, "Graph");
    v.zNear = 0.001;
    v.showCoordArrows (true);
    v.backgroundWhite();
    v.lightingEffects();

    try {
        sm::vvec<float> absc =  {-1.0, -.9, -.8, -.7, -.6, -.5, -.4, -.3, -.2, -.1, 0, .1, .2, .3, .4, .5, .6, .7, .8, .9, 1.0};
        sm::vvec<float> data = 2.1f * absc.pow(3);
        sm::vvec<float> data2 = 1.5f * absc.pow(5);
        auto gv = std::make_unique<mplot::GraphVisual<float>> (sm::vec<float>({0,0,0}));
        v.bindmodel (gv);

        // Optionally change the size of the graph and range of the axes
        gv->setsize (1.33, 1);
        // Optionally change the range of the axes
        gv->setlimits (-1, 0.1, -1, 1);

        // Set the graphing policy
        gv->policy = mplot::stylepolicy::lines; // markers, lines, both, allcolour
        gv->axisstyle = mplot::axisstyle::twinax;
        // We 'prepare' two datasets, but won't fill them with data yet. However, we do give the data legend label here.
        gv->prepdata ("Third power", mplot::axisside::left);
        gv->prepdata ("Fifth power", mplot::axisside::right);

        gv->ylabel = "f(x) = 2.1x" + uc::toUtf8(uc::ss3);
        // ylabel2 is the right hand y axis label
        gv->ylabel2 = "f(x) = 1.5x" + uc::toUtf8(uc::ss5);

        // Enable auto-rescaling of the x axis
        gv->auto_rescale_x = true;
        // Enable auto-rescaling of the y axis
        gv->auto_rescale_y = true;

        gv->finalize();

        // Add the GraphVisual (as a VisualModel*)
        auto gvp = v.addVisualModel (gv);

        size_t rcount = 0;
        size_t idx = 0;
        v.render();
        while (v.readyToFinish() == false) {
            v.waitevents (0.018);
            // Slowly update the content of the graph
            if (rcount++ % 20 == 0 && idx < absc.size()) {
                // Append to dataset 0
                gvp->append (absc[idx], data[idx], 0);
                // Append to dataset 1
                gvp->append (absc[idx], data2[idx], 1);
                ++idx;
            }
            v.render();
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
