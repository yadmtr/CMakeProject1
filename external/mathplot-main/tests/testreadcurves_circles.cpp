#include <iostream>

#include <utility>
#include <vector>
#include <fstream>

#include <sm/bezcoord>
#include <sm/bezcurvepath>

#include <mplot/ReadCurves.h>

int main()
{
    int rtn = -1;

    try {
        mplot::ReadCurves r("../../tests/whiskerbarrels_withcentres.svg");
        //r.save (0.001f);
        sm::bezcurvepath<float> bcp = r.getCorticalPath();
        bcp.computePoints (0.01f);
        std::vector<sm::bezcoord<float>> pts = bcp.getPoints();
        auto i = pts.begin();
        while (i != pts.end()) {
            std::cout << *i << std::endl;
            ++i;
        }

        std::cout.precision(12);
        std::cout << "pts[23] =  " << pts[23].t()
             << " " << pts[23].x()
             << " " << pts[23].y()
             << std::endl;
        if ((fabs(pts[23].t() - 0.110523112118) < 0.000001f)
            && (fabs(pts[23].x() - 0.74002712965) < 0.000001f)
            && (fabs(pts[23].y() - 0.393309623003) < 0.000001f)) {
            std::cout << "rtn IS 0" << std::endl;
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
