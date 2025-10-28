/*
 * Visualize a CoordArrows VisualModel
 */
#include <iostream>
#include <sm/vec>
#include <mplot/Visual.h>
#include <mplot/CoordArrows.h> // This is the only VisualModel derived class not called SomethingVisual!

int main()
{
    mplot::Visual v(1024, 768, "Coordinate Arrows");
    v.showCoordArrows (true); // Shows the 'scene' coordarrows, that you get in every mplot::Visual
    v.lightingEffects(true);

    // An extra CoordArrows model, with defaults
    sm::vec<float> offset = {};
    auto cavm = std::make_unique<mplot::CoordArrows<>> (offset);
    v.bindmodel (cavm);
    cavm->finalize();
    v.addVisualModel (cavm);

    sm::vec<float> ux = {1,0,0};
    sm::vec<float> uy = {0,1,0};
    sm::vec<float> uz = {0,0,1};

    // An CoordArrows model, with non-defaults
    offset[0] += 1.5f;
    cavm = std::make_unique<mplot::CoordArrows<>> (offset);
    v.bindmodel (cavm);
    cavm->init (ux, uy, -uz);

    cavm->lengths = sm::vec<float>{1,1,1}; // this is the default already
    cavm->thickness = 0.9f;
    cavm->em = 0.08f;
    // or: cavn->init (sm::vec<float>{1,1,1}, 0.9f, 0.08f);

    cavm->z_label = "-Z";

    cavm->finalize();
    v.addVisualModel (cavm);

    // One more, for good measure
    offset[0] += 1.5f;
    cavm = std::make_unique<mplot::CoordArrows<>> (offset);
    v.bindmodel (cavm);
    cavm->init (ux, uz, uy);
    cavm->init (sm::vec<float>{1,1,0.5}, 1.5f, 0.13f);
    cavm->x_label = "X'";
    cavm->y_label = "Y'";
    cavm->z_label = "Z'";
    cavm->finalize();
    v.addVisualModel (cavm);

    v.keepOpen();
}
