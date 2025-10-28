#include <utility>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include <sm/hdfdata>

int main()
{
    int rtn = 0;

    // Test vector of vectors of floats
    // vector of OpenCL Points (& Point2ds)
    // vector of array<float,3>
    // save/retrieve strings

    std::cout << "vector<array<float, 3>>" << std::endl;
    std::vector<std::array<float, 3>> va = { { 1.0, 1.0, 2.0 },
                                             { 3.0, 3.0, 4.0 },
                                             { 5.0, 5.0, 6.0 },
                                             { 7.0, 7.0, 8.0 },
                                             { 9.0, 9.0, 10.0 } };
    {
        sm::hdfdata data("test0.h5", sm::file_access_mode::truncate_write);
        data.add_contained_vals ("/testvecarray", va);
    } // data closes when out of scope

    // Demonstrate appending data to an existing HDF5 file:
    {
        sm::hdfdata data("test0.h5", sm::file_access_mode::read_write);
        data.add_contained_vals ("/testvecarray2", va);
    }

    std::vector<std::array<float, 3>> varead;
    {
        sm::hdfdata data("test0.h5", sm::file_access_mode::read_only);
        data.read_contained_vals ("/testvecarray2", varead);
    }

    if (va.size() == varead.size()) {
        for (unsigned int i = 0; i < va.size(); ++i) {
            if (va[i][0] != varead[i][0]) {
                rtn -= 1;
                break;
            }
            if (va[i][1] != varead[i][1]) {
                rtn -= 1;
                break;
            }
            if (va[i][2] != varead[i][2]) {
                rtn -= 1;
                break;
            }
            std::cout << "Coordinate: (" << va[i][0] << "," << va[i][1] << "," << va[i][2] << ")" << std::endl;
        }
    }

    // Demonstrate overwriting data to an existing HDF5 file:
    va[0][0] = 100.0f;
    {
        sm::hdfdata data("test0.h5", sm::file_access_mode::read_write);
        data.add_contained_vals ("/testvecarray2", va);
    }
    // And read back:
    {
        sm::hdfdata data("test0.h5", sm::file_access_mode::read_only);
        data.read_contained_vals ("/testvecarray2", varead);
    }
    std::cout << "varead[0][0] = " << varead[0][0] << " (should be 100) varead size: " << varead.size() << "\n";
    if (varead.size() != va.size()) { rtn -= 1; }
    if (varead[0][0] != 100.0f) { rtn -= 1; }

    std::cout << "vector<array<float, 12>>" << std::endl;
    std::vector<std::array<float, 12>> va12 = { { 1., 1., 2.,  1., 1., 2., 1., 1., 2., 1., 1., 2. },
                                                { 3., 3., 4.,  2., 1., 2., 3., 3., 4., 3., 3., 4. },
                                                { 5., 5., 6.,  3., 1., 2., 3., 3., 4., 3., 3., 4. },
                                                { 5., 5., 6.,  4., 1., 2., 3., 3., 4., 3., 3., 4. },
                                                { 7., 7., 8.,  5., 1., 2., 3., 3., 4., 3., 3., 4. },
                                                { 9., 9., 10., 6., 1., 2., 3., 3., 4., 3., 3., 4. } };
    {
        sm::hdfdata data("test.h5", std::ios::out | std::ios::trunc);
        data.add_contained_vals ("/testvecf12", va12);
    } // data closes when out of scope

    std::vector<std::array<float, 12>> va12read;
    {
        sm::hdfdata data("test.h5", std::ios::in);
        data.read_contained_vals ("/testvecf12", va12read);
    }

    if (va12.size() == va12read.size()) {
        for (unsigned int i = 0; i < va12.size(); ++i) {
            for (unsigned int j = 0; j < 12; ++j) {
                if (va12[i][j] != va12read[i][j]) {
                    rtn -= 1;
                    break;
                }
            }
            std::cout << "Coordinate: (" << va12[i][0] << "," << va12[i][1] << "," << va12[i][2] << "," << va12[i][3] << "...)" << std::endl;
        }
    }

    std::cout << "vector<pair<ULL,ULL>>" << std::endl;
    std::vector<std::pair<unsigned long long int, unsigned long long int>> vpi2dpair = { std::make_pair(1ULL,3ULL),
                                                                                         std::make_pair(3ULL,4ULL),
                                                                                         std::make_pair(5ULL,7ULL),
                                                                                         std::make_pair(8ULL,8ULL),
                                                                                         std::make_pair(9ULL,18ULL) };
    {
        sm::hdfdata data("test.h5", std::ios::out | std::ios::trunc);
        data.add_contained_vals ("/vpi2dpair", vpi2dpair);
    } // data closes when out of scope

    std::vector<std::pair<unsigned long long int, unsigned long long int>> vpi2dpairread;
    {
        sm::hdfdata data("test.h5", std::ios::in);
        data.read_contained_vals ("/vpi2dpair", vpi2dpairread);
    }

    if (vpi2dpair.size() == vpi2dpairread.size()) {
        //// To here
        for (unsigned int i = 0; i < vpi2dpair.size(); ++i) {
            if (vpi2dpair[i].first != vpi2dpairread[i].first) {
                rtn -= 1;
                break;
            }
            if (vpi2dpair[i].second != vpi2dpairread[i].second) {
                rtn -= 1;
                break;
            }
            std::cout << "Coordinate: (" << vpi2dpairread[i].first << "," << vpi2dpairread[i].second << ")" << std::endl;
        }
    }

    std::string tstr = "Thou art more lovely...";
    {
        sm::hdfdata data("test.h5", std::ios::out | std::ios::trunc);
        data.add_string ("/stringtest", tstr);
    }
    std::string str;
    {
        sm::hdfdata data("test.h5", std::ios::in);
        data.read_string ("/stringtest", str);
    }
    std::cout << "String stored: " << tstr << std::endl;
    std::cout << "String retrieved: " << str << std::endl;
    if (str != tstr) {
        rtn -= 1;
    }

    std::bitset<13> bs;
    bs.set(3);
    bs.set(7);
    {
        sm::hdfdata data("test.h5", std::ios::out | std::ios::trunc);
        data.add_val ("/bitset", bs);
    }
    std::bitset<13> bsread;
    {
        sm::hdfdata data("test.h5", std::ios::in);
        data.read_val ("/bitset", bsread);
    }
    std::cout << "Bitset stored: " << bs << std::endl;
    std::cout << "Bitset retrieved: " << bsread << std::endl;
    if (!(bs == bsread)) {
        rtn -= 1;
    }

    std::cout << "Returning " << rtn << std::endl;

    return rtn;
}
