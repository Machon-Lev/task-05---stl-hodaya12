#include "CalculateDistance.h"

CalculateDistance::CalculateDistance() :
    distanceFuncArray{
        std::function<double(double, double, double, double)>([this](double x1, double y1, double x2, double y2) { return calculateDistanceL2(x1, y1, x2, y2); }),
        std::function<double(double, double, double, double)>([this](double x1, double y1, double x2, double y2) { return calculateDistanceLinf(x1, y1, x2, y2); }),
        std::function<double(double, double, double, double)>([this](double x1, double y1, double x2, double y2) { return calculateDistanceL1(x1, y1, x2, y2); })
}
{
}

/**
 * Calculates the Euclidean distance between two points (x1, y1) and (x2, y2).
 */
double CalculateDistance::calculateDistanceL2(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

/**
 * Calculates the Chebyshev distance between two points (x1, y1) and (x2, y2).
 */
double CalculateDistance::calculateDistanceLinf(double x1, double y1, double x2, double y2) {
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

/**
 * Calculates the Manhattan distance between two points (x1, y1) and (x2, y2).
 */
double CalculateDistance::calculateDistanceL1(double x1, double y1, double x2, double y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

/**
 * Retrieves the distance calculation function at the specified index.
 *
 * @param index The index of the distance calculation function to retrieve.
 * @return The distance calculation function.
 * @throws std::out_of_range if the index is out of range.
 */
std::function<double(double, double, double, double)> CalculateDistance::operator[](std::size_t index) const {
    if (index < distanceFuncArray.size()) {
        return distanceFuncArray[index];
    }
    throw std::out_of_range("Invalid index");
}