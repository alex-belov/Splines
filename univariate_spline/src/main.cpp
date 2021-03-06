#include <cmath>
#include <string>
#include <iostream>
#include <vector>

#include "univariate_spline.h"
#include "../../tools/tools_2d.h"


int main(int agrc, char* argv[])
{
    if (agrc < 6){
        std::cout << "\nArgs: <data filename> <result filename> <points count> <spline knots count> <spline degree>"
                  << "\nFor example: ./univariate_spline.exe data result 1000 7 3" << std::endl;
        return 1;
    }

    const std::string inputFilename = argv[1];
    const std::string outputFilename = argv[2];
    const unsigned int pointsCount = strtoul(argv[3], nullptr, 10);
    const unsigned int knotsCount = strtoul(argv[4], nullptr, 10);
    const unsigned int splineDegree = strtoul(argv[5], nullptr, 10);

    std::vector<std::string> vals_name;
    std::vector<double> x, y, w;

    std::cout << "Reading result..." << std::endl;
    readingData2d(x, y, w, vals_name, inputFilename);

    std::cout << "Approximation of data..." << std::endl;
    UnivariateSpline spl(splineDegree, knotsCount);

    std::cout << "\tInitialize uniform knots..." << std::endl;
    spl.initializeUniformKnots(x);

    std::cout << "\tCalculate coefficients of spline..." << std::endl;
    spl.computingCoefficients(x, y, w);

    std::cout << "Saving result..." << std::endl;
    writingResult2d(x[0], x[x.size() - 1], pointsCount, spl, outputFilename, vals_name);

    return 0;
}