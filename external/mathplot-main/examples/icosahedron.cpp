/*
 * Visualize an Icosahedron
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <stdexcept>
#include <string>

#include <sm/vec>

#include <mplot/Visual.h>
#include <mplot/ColourMap.h>
#include <mplot/IcosaVisual.h>

int main()
{
    int rtn = -1;

    mplot::Visual v(1024, 768, "Icosahedron");
    v.showCoordArrows (true);
    // Switch on a mix of diffuse/ambient lighting
    v.lightingEffects(true);

    try {
        sm::vec<float, 3> offset = { 0.0, 0.0, 0.0 };
        sm::vec<float, 3> colour1 = { 1.0, 0.0, 0.0 };

        auto iv = std::make_unique<mplot::IcosaVisual<>> (offset, 0.9f, colour1);
        v.bindmodel (iv);
        iv->finalize();
        v.addVisualModel (iv);

        v.keepOpen();

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
