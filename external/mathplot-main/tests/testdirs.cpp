#include <mplot/tools.h>
#include <mplot/Random.h>
#include <string>
#include <iostream>

int main()
{
    int rtn = -2;
    mplot::RandString rs(8);
    std::string dpath = "testdir" + rs.get();
    mplot::tools::createDir (dpath);
    if (mplot::tools::dirExists (dpath)) {
        std::cout << "Created directory " << dpath << " successfully.\n";
        rtn = 0;
    } else {
        std::cout << "Failed to create directory " << dpath << ".\n";
        rtn = -1;
    }
    return rtn;
}
