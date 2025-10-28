/*
 * Visualize just the CoordArrows - i.e. an empty mplot::Visual
 */

#include "mplot/Visual.h"
#include "mplot/ColourMap.h"
#include <iostream>
#include <array>
#include <stdexcept>
#include <string>

int main (int argc, char** argv)
{
    int rtn = -1;

    mplot::Visual v(1024, 768, "Title");
    v.zNear = 0.001;
    v.showCoordArrows (true);
    v.showTitle (true);
    // For a white background:
    v.backgroundWhite();
    v.lightingEffects();

    bool holdVis = false;
    if (argc > 1) {
        std::string a1(argv[1]);
        holdVis = a1.empty() ? false : true;
    }
    std::cout << "NB: Provide a cmd line arg (anything) to see the graphical window for this program\n";

    try {

        v.render();
        if (holdVis == true) {
            while (v.readyToFinish() == false) {
                glfwWaitEventsTimeout (0.018);
                v.render();
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
