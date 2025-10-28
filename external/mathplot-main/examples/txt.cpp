/*
 * TxtVisual example
 */
#include <sm/vec>
#include <mplot/Visual.h>
#include <mplot/TxtVisual.h>

int main()
{
    mplot::Visual v (1024, 768, "TxtVisual example");

    auto tv = std::make_unique<mplot::TxtVisual<>> ("This is text\nand it's a VisualModel\n"
                                                    "It rotates and translates with the scene.\n"
                                                    "You can use newline characters [here]-->\n"
                                                    "in the source and these are reflected in the output.",
                                                    sm::vec<float>{1.0f, 0.0f, 0.5f}, mplot::TextFeatures (0.1f));
    v.bindmodel (tv);
    tv->finalize();
    v.addVisualModel (tv);

    v.keepOpen();

    return 0;
}
