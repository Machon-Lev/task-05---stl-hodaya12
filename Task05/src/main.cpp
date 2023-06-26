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
#include "frequencies.h"




std::string filename = "data.txt";

/**
 * Calculates the Euclidean distance between two points (x1, y1) and (x2, y2).
 */
double calculateDistanceL2(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

/**
 * Calculates the Chebyshev distance between two points (x1, y1) and (x2, y2).
 */
double calculateDistanceLinf(double x1, double y1, double x2, double y2) {
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

/**
 * Calculates the Manhattan distance between two points (x1, y1) and (x2, y2).
 */
double calculateDistanceL1(double x1, double y1, double x2, double y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

/**
 * Reads the city data from a file and returns an unordered map containing the city names and their coordinates.
 * The file format should be:
 *   - Line 1: City name
 *   - Line 2: City coordinates (x-y format)
 *   - Repeat for each city
 */
std::unordered_map<std::string, std::pair<double, double>> readCitiesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::unordered_map<std::string, std::pair<double, double>> cities;

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    // Check if the file is empty
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Empty file: " + filename);
    }
    file.seekg(0, std::ios::beg);

    std::string line;
    std::string cityName;
    std::string cityCoordinates;

    while (std::getline(file, line)) {
        cityName = line;
        if (!std::getline(file, line)) {
            throw std::runtime_error("Invalid file format: " + filename);
        }
        cityCoordinates = line;

        size_t pos = cityCoordinates.find('-');
        if (pos == std::string::npos) {
            throw std::runtime_error("Invalid file format: " + filename);
        }

        double x, y;
        char hyphen;
        std::istringstream iss(cityCoordinates);
        if (!(iss >> x >> hyphen >> y)) {
            throw std::runtime_error("Invalid input for coordinates in file: " + filename);
        }

        cities[cityName] = std::make_pair(x, y);
    }

    file.close();
    return cities;
}

/**
 * Searches for cities within a given radius around a selected city.
 * Prints the nearby cities and the number of cities to the north of the selected city.
 * The distance function used for the search is determined by the norm parameter.
 */
void searchCities(const std::unordered_map<std::string, std::pair<double, double>>& cities, const std::string& cityName, double radius, const std::function<double(double, double, double, double)>& distanceFunc) {
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities;
    std::unordered_map<std::string, std::pair<double, double>> northCities;

    const auto& selectedCity = cities.find(cityName);
    if (selectedCity == cities.end()) {
        std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
        return;
    }
    nearbyCities.reserve(cities.size());
    std::copy_if(cities.begin(), cities.end(), std::inserter(nearbyCities, nearbyCities.end()), [&](const auto& city) {
        const auto& coordinates = city.second;
        double distance = distanceFunc(coordinates.first, coordinates.second, selectedCity->second.first, selectedCity->second.second);
        return distance <= radius;
        });


    std::vector<std::pair<std::string, std::pair<double, double>>> tempVec(nearbyCities.begin(), nearbyCities.end());
    std::sort(tempVec.begin(), tempVec.end(), [&](const auto& city1, const auto& city2) {
        const auto& coordinates1 = city1.second;
        const auto& coordinates2 = city2.second;
        double distance1 = distanceFunc(coordinates1.first, coordinates1.second, selectedCity->second.first, selectedCity->second.second);
        double distance2 = distanceFunc(coordinates2.first, coordinates2.second, selectedCity->second.first, selectedCity->second.second);
        return distance1 < distance2;
        });

    std::cout << "Search result:" << std::endl;
    std::cout << nearbyCities.size() << " city/cities found in the given radius." << std::endl;
    std::cout << std::count_if(cities.cbegin(), cities.cend(),
        [&](const auto& city) { return city.second.second < selectedCity->second.second; });
    std::cout << " cities are to the north of the selected city." << std::endl;

    std::cout << "City list:" << std::endl;

    std::vector<std::string> cityNames;
    std::transform(tempVec.cbegin(), tempVec.cend(), std::back_inserter(cityNames), [](const auto& city) {
        std::cout << city.first << std::endl;
        return city.first;
        });

}

/**
 * Clears the input buffer.
 */
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Prompts the user to enter a city name, radius, and norm for the search.
 * Performs the city search recursively until the user enters '0' as the city name.
 */
void searchCitiesRecursive(const std::unordered_map<std::string, std::pair<double, double>>& cities) {
    clearInputBuffer();
    std::cout << "Please enter selected city name (with line break after it):" << std::endl;
    std::string cityName;

    std::getline(std::cin, cityName);
    if (cityName == "0") {
        std::cout << "Bye" << std::endl;
        return;
    }


    double radius;
    std::string input;

    do {
        std::cout << "Please enter the wanted radius:" << std::endl;
        std::cin >> input;

        try {
            radius = std::stod(input);
            if (radius <= 0) {
                std::cout << "Invalid radius. Please enter a positive value." << std::endl;
            }
        }
        catch (const std::exception&) {
            std::cout << "Invalid radius. Please enter a valid numeric value." << std::endl;
            radius = -1; // Set an invalid value to continue the loop
        }
    } while (radius <= 0);


    std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):" << std::endl;
    int norm;
    std::array<std::function<double(double, double, double, double)>, 3> distanceFuncArray = {
           calculateDistanceL2,
           calculateDistanceLinf,
           calculateDistanceL1
    };

    while (!(std::cin >> norm) || norm < 0 || norm > 2) {
        std::cin.clear();
        clearInputBuffer();
        std::cout << "Invalid norm. Please try again." << std::endl;
    }

    searchCities(cities, cityName, radius, distanceFuncArray[norm]);

    
    searchCitiesRecursive(cities);

}
int cities() {
    std::unordered_map<std::string, std::pair<double, double>> cities;
    try {
        cities = readCitiesFromFile(filename);
        searchCitiesRecursive(cities);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;

}

int main() {
    int input=0;
    while (input != 1 && input != 2) {
        std::cout << "choose 1 to run the cities program or 2 to run the frequencies program" << std::endl;
        std::cin >> input;
    }
    if (input == 1)
        cities();
    if (input == 2)
        frequencies();
    
    return 0;
}