#include <iostream>

#include <utility>
#include <vector>
#include <fstream>
#include <cmath>

#include <sm/bezcoord>
#include <sm/bezcurvepath>

#include <mplot/ReadCurves.h>

int main()
{
    int rtn = -1;

    try {
        mplot::ReadCurves r("../../tests/trial.svg");
        sm::bezcurvepath<float> bcp = r.getCorticalPath();
        bcp.computePoints (0.01f);
        std::vector<sm::bezcoord<float>> pts = bcp.getPoints();
        std::cout << "Got " << pts.size() << " points with getPoints()" << std::endl;
        auto i = pts.begin();
        while (i != pts.end()) {
            std::cout << *i << std::endl;
            ++i;
        }
        // 0.329310834408 0.849295854568 1.00672543049
        std::cout.precision(12);
        std::cout << "pts[23] =  " << pts[23].t()
                  << " " << pts[23].x()
                  << " " << pts[23].y()
                  << std::endl;
        if ((std::abs(pts[23].t() - 0.329311) < 0.00001f)
            && (std::abs(pts[23].x() - 0.849296) < 0.00001f)
            && (std::abs(pts[23].y()- 1.00673) < 0.00001f)) {
            std::cout << "Matches expectation; rtn IS 0" << std::endl;
            rtn = 0;
        } else {
            std::cout << "rtn not 0" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught exception reading trial.svg: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
