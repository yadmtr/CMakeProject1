/*
 * Visualize a rectangle
 */
#include <iostream>
#include <sm/vec>
#include <mplot/Visual.h>
#include <mplot/RectangleVisual.h>

int main()
{
    int rtn = -1;
    mplot::Visual v(1024, 768, "RectangleVisual");

    try {
        sm::vec<float, 3> offset = { 0.0f, 0.0f, 0.0f };
        sm::vec<float, 2> dims = { 0.4f, 2.0f };
        float angle = 0.0f;
        auto rv = std::make_unique<mplot::RectangleVisual<>> (offset, dims, angle, mplot::colour::maroon);
        v.bindmodel (rv);
        rv->finalize();
        v.addVisualModel (rv);

        v.keepOpen();

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
