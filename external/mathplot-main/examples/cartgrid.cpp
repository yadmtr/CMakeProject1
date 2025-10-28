/*
 * An example mplot::Visual scene, containing a CartGrid.
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <sm/vec>
#include <sm/cartgrid>

#include <mplot/Visual.h>
#include <mplot/VisualDataModel.h>
#include <mplot/CartGridVisual.h>

int main()
{
    // Contructor args are width, height, title
    mplot::Visual v(1600, 1000, "mplot::CartGridVisual");
    // You can set a field of view (in degrees)
    v.fov = 15;
    // Make this larger to "scroll in and out of the image" faster
    v.scenetrans_stepsize = 0.5;
    // The coord arrows can be displayed within the scene (rather than in, say, the corner). Set true to do so.
    v.coordArrowsInScene (false);
    // You can set the background (white, black, or any other colour)
    v.backgroundWhite();
    // You can switch on the "lighting shader" which puts diffuse light into the scene
    v.lightingEffects();
    // Add some text labels to the scene
    v.addLabel ("This is a\nmplot::CartGridVisual\nobject", {0.26f, -0.16f, 0.0f});

    // Create a HexGrid to show in the scene
    sm::cartgrid cg(0.01, 0.01, 1, 1);
    std::cout << "Number of pixels in grid:" << cg.num() << std::endl;

    // *NB* This call (or any other 'set boundary' call) is essential, as it sets up the
    // d_ vectors in the cartgrid. Without it, the cartgrid will be unusable!
    cg.setBoundaryOnOuterEdge();

    // Make some dummy data (a sine wave) to make an interesting surface
    std::vector<float> data(cg.num(), 0.0);
    for (unsigned int ri=0; ri<cg.num(); ++ri) {
        //std::cout << cg.d_x.size() << std::endl;
        //std::cout << "cg.d_x["<<ri<<"]=" << cg.d_x[ri] << std::endl;
        data[ri] = 0.05f + 0.05f*std::sin(20.0f*cg.d_x[ri]) * std::sin(10.0f*cg.d_y[ri]) ; // Range 0->1
    }

    // Add a CartGridVisual to display the CartGrid within the mplot::Visual scene
    sm::vec<float, 3> offset = { 0.0f, -0.05f, 0.0f };
    auto cgv = std::make_unique<mplot::CartGridVisual<float>>(&cg, offset);
    v.bindmodel (cgv);
    cgv->cartVisMode = mplot::CartVisMode::RectInterp;
    cgv->setScalarData (&data);
    cgv->cm.setType (mplot::ColourMapType::Twilight);
    cgv->finalize();
    v.addVisualModel (cgv);

    v.keepOpen();

    return 0;
}
