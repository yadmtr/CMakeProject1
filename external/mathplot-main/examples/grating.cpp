/*
 * Visualize a Grating
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
#include <mplot/GratingVisual.h>

struct myvisual final : public mplot::Visual<>
{
    // Boilerplate constructor (just copy this):
    myvisual (int width, int height, const std::string& title) : mplot::Visual<> (width, height, title) {}

    // Angle of the bands
    float angle = 0.0f;
    // Time
    unsigned long long int t = 0;
    // band 'wavelength'
    float lambda = 0.5f;

    // Flag if we should reinit the model
    bool needs_reinit = false;
    bool do_loop2 = true;

protected:
    void key_callback_extra (int key, [[maybe_unused]]int scancode, int action, [[maybe_unused]]int mods) override
    {
        if (action == mplot::keyaction::press || action == mplot::keyaction::repeat) {
            if (key == mplot::key::w) {
                this->angle += this->angle <= 179.0f ? 1.0f : 0.0f;
                this->needs_reinit = true;
            } else if (key == mplot::key::s) {
                this->angle -= this->angle >= 1.0f ? 1.0f : 0.0f;
                this->needs_reinit = true;
            } else if (key == mplot::key::a) {
                this->t = this->t > 0 ? this->t - 1 : 0;
                this->needs_reinit = true;
            } else if (key == mplot::key::d) {
                this->t = this->t + 1;
                this->needs_reinit = true;
            } else if (key == mplot::key::p) {
                this->lambda += 0.05f;
                this->needs_reinit = true;
            } else if (key == mplot::key::l) {
                this->lambda -= 0.05f;
                this->lambda = this->lambda < 0.05f ? 0.05f : this->lambda;
                this->needs_reinit = true;
            }
            if (this->needs_reinit) {
                std::cout << "\nKeyboard update: " << mplot::unicode::toUtf8(mplot::unicode::alpha) <<  " = " << angle
                          << ", time point is " << this->t
                          << ", " << mplot::unicode::toUtf8(mplot::unicode::lambda) << " = " << lambda << std::endl;
            }
        }
    }
};


int main (int ac, char** av)
{
    int rtn = -1;
    myvisual v(1024, 768, "Grating");
    v.setSceneTrans (sm::vec<float,3>({-0.990124f, -0.452241f, -3.6f}));

    if (ac > 1) { v.angle = std::atoi (av[1]); } // First arg is angle
    if (ac > 2) { v.t = std::atoi (av[2]); } // second is time
    if (ac > 3) { v.do_loop2 = (std::atoi (av[3]) == 0) ? false : true; }
    constexpr bool interactive = true;

    try {
        sm::vec<float, 3> offset = { 0.0f, 0.0f, 0.0f };

        auto rvm = std::make_unique<mplot::GratingVisual<>> (offset);
        v.bindmodel (rvm);
        rvm->v_front = { -0.01f, 0.0173f };
        rvm->t = v.t;
        rvm->do_loop2 = v.do_loop2;
        rvm->lambda = v.lambda;
        rvm->alpha = v.angle;
        rvm->finalize();
        auto rvmp = v.addVisualModel (rvm);

        if constexpr (interactive) {
            while (!v.readyToFinish()) {
                v.waitevents (0.018);
                v.render();
                if (v.needs_reinit == true) {
                    rvmp->t = v.t;
                    rvmp->alpha = v.angle;
                    rvmp->lambda = v.lambda;
                    rvmp->reinit();
                    v.needs_reinit = false;
                }
            }
        } else {
            v.keepOpen();
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        rtn = -1;
    }

    return rtn;
}
