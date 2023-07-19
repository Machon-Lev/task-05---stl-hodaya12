#include "cities.h"

const std::string filename = "data.txt";

/**
 * Clears the input buffer.
 */
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


/**
 * Prompts the user to enter a city name, radius, and norm for the search.
 * Performs the city search until the user enters '0' as the city name.
 */
void searchCities(std::unordered_map<std::string, std::pair<double, double>> cities) {
    std::string cityName;
    while (true) {
        clearInputBuffer();
        std::cout << "Please enter selected city name (with line break after it):" << std::endl;
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


        while (!(std::cin >> norm) || norm < 0 || norm > 2) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Invalid norm. Please try again." << std::endl;
        }

        SearchingCities s(cities, cityName);
        s.searchCitiesInRadius(radius, norm);
        s.searcNorthCities();
    }
}
int cities() {
    ReadingFromFile r(filename);
    std::unordered_map<std::string, std::pair<double, double>> cities;
    try {
        cities = r.readCitiesFromFile();

        searchCities(cities);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;

}