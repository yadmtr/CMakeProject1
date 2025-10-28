#include <iostream>
#include <sm/vvec>

int main()
{
    int rtn = 0;

    sm::vvec<float> a = { 6,0,6 };

    sm::vvec<float> b = a;
    b.rescale();
    std::cout << a << " rescaled: " << b << std::endl;

    sm::vvec<float> c = a;
    c.rescale_sym();
    std::cout << a << " symetrically rescaled: " << c << std::endl;

    sm::vvec<float> g = a;
    g.rescale_neg();
    std::cout << a << " neg rescaled: " << g << std::endl;

    if (b != sm::vvec<float>({1, 0, 1})) { --rtn; }
    if (c != sm::vvec<float>({1,-1, 1})) { --rtn; }
    if (g != sm::vvec<float>({0,-1, 0})) { --rtn; }

    sm::vvec<float> e = { -8,-7,-4,-2 };

    sm::vvec<float> d = e;
    d.rescale();
    std::cout << e << " rescaled: " << d << std::endl;

    sm::vvec<float> f = e;
    f.rescale_sym();
    std::cout << e << " sym rescaled: " << f << std::endl;

    sm::vvec<float> h = e;
    h.rescale_neg();
    std::cout << e << " neg rescaled: " << h << std::endl;

    return rtn;
}
