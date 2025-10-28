// Twinax graph
#include <sm/vec>
#include <sm/vvec>

#include <mplot/Visual.h>
#include <mplot/GraphVisual.h>
#include <mplot/unicode.h>

int main()
{
    namespace uc = mplot::unicode;

    // Set up a mplot::Visual 'scene environment'.
    mplot::Visual v(1024, 768, "Twinax GraphVisual example");
    // Create a new GraphVisual with offset within the scene of 0,0,0
    auto gv = std::make_unique<mplot::GraphVisual<double>> (sm::vec<float>({0,0,0}));
    v.bindmodel (gv);
    // This is going to be a twin axis graph
    gv->axisstyle = mplot::axisstyle::twinax;
    // Data for the x axis. A vvec is like std::vector, but with built-in maths methods
    sm::vvec<double> x;
    // This works like numpy's linspace() (the 3 args are "start", "end" and "num"):
    x.linspace (-0.5, 0.8, 14);

    // Set a graph up of x^3
    std::string ds1legend = uc::toUtf8 (uc::alpha) + "(x) = x" + uc::toUtf8 (uc::ss3);
    gv->setdata (x, x.pow(3), ds1legend);
    gv->ylabel = uc::toUtf8 (uc::alpha);

    // And 100x^2
    std::string ds2legend = uc::toUtf8 (uc::beta) + "(x) = 100x" + uc::toUtf8 (uc::ss2);
    gv->setdata (x, x.pow(2)*100, ds2legend, mplot::axisside::right);
    gv->ylabel2 = uc::toUtf8 (uc::beta);

    // finalize() makes the GraphVisual compute the vertices of the OpenGL model
    gv->finalize();
    // Add the GraphVisual OpenGL model to the Visual scene
    v.addVisualModel (gv);
    // Render the scene on the screen until user quits with 'Ctrl-q'
    v.keepOpen();
    // When v goes out of scope, gv will be deallocated
    return 0;
}
