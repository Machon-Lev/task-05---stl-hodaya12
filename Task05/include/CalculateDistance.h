#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>
class CalculateDistance {
    const std::array<std::function<double(double, double, double, double)>, 3> distanceFuncArray;
public:
    CalculateDistance();
    double calculateDistanceL2(double x1, double y1, double x2, double y2);


    double calculateDistanceLinf(double x1, double y1, double x2, double y2);


    double calculateDistanceL1(double x1, double y1, double x2, double y2);

    std::function<double(double, double, double, double)> operator[](std::size_t index) const;
};
