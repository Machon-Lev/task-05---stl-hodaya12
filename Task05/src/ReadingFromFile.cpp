#pragma once
#include "ReadingFromFile.h"


/**
*Constructor - Receives the filename as a parameter and checks the validity of the file.
 */
ReadingFromFile::ReadingFromFile(const std::string& filename1) : filename(filename1), file(filename1)
{
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    // Check if the file is empty
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Empty file: " + filename);
    }
    file.seekg(0, std::ios::beg);
    

}

/**
 * Reads the city data from a file and returns an unordered map containing the city names and their coordinates.
 * The file format should be:
 *   - Line 1: City name
 *   - Line 2: City coordinates (x-y format)
 *   - Repeat for each city
 */
std::unordered_map<std::string, std::pair<double, double>> ReadingFromFile::readCitiesFromFile() {
    

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
