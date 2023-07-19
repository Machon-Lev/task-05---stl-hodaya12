#include "SearchingCities.h"

/**
     * Constructor - Creates a SearchingCities object with a selected city name and a map of city names and coordinates.
     * @param cities1 A map containing city names and their coordinates.
     * @param cityName1 The name of the city to be selected.
     */
SearchingCities::SearchingCities(const std::unordered_map<std::string, std::pair<double, double>>& cities1, const std::string& cityName1):cityName(cityName1),cities(cities1)
{
    auto selectedCity = cities1.find(cityName1);
    if (selectedCity == cities1.end()) {
        std::cout << "ERROR: \"" << cityName1 << "\" isn't found in the city list. Please try again." << std::endl;
        cityName="";
    }
    
}

/**
  * Searches for cities within a given radius around a selected city.
  * Prints the nearby cities 
  * The distance function used for the search is determined by the norm parameter.
  */
void SearchingCities::searchCitiesInRadius(double radius,int norm) {
    if (cityName=="")
        return;
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities=filterCities(radius, norm);
    CalculateDistance c;

    const auto& selectedCity = cities.find(cityName);
 
    std::vector<std::pair<std::string, std::pair<double, double>>> tempVec(nearbyCities.begin(), nearbyCities.end());
    std::sort(tempVec.begin(), tempVec.end(), [&](const auto& city1, const auto& city2) {
        const auto& coordinates1 = city1.second;
        const auto& coordinates2 = city2.second;
        double distance1 = c[norm](coordinates1.first, coordinates1.second, selectedCity->second.first, selectedCity->second.second);
        double distance2 = c[norm](coordinates2.first, coordinates2.second, selectedCity->second.first, selectedCity->second.second);
        return distance1 < distance2;
        });

    std::cout << "Search result:" << std::endl;
    std::cout << nearbyCities.size() << " city/cities found in the given radius." << std::endl;
   

    std::cout << "City list:" << std::endl;

    std::vector<std::string> cityNames;
    std::transform(tempVec.cbegin(), tempVec.cend(), std::back_inserter(cityNames), [](const auto& city) {
        std::cout << city.first << std::endl;
        return city.first;
        });

}

/**
   * Filter the cities within a given radius around the selected city.
   * The function performs filtering using horizontal, vertical, and distance-based filters.
   * The distance function used for the filtering is determined by the 'norm' parameter.
   * @param radius The search radius.
   * @param norm The norm value used for the distance function.
   * @return An unordered map containing the filtered cities.
   */
std::unordered_map<std::string, std::pair<double, double>> SearchingCities::filterCities(double radius, int norm)
{
    
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities;
    if (cityName == "")
        return nearbyCities;
    nearbyCities = filterCitiesByHorizontal(radius, cities);
    nearbyCities = filterCitiesByVertical(radius, nearbyCities);
    nearbyCities = filterCitiesByCircle(radius, norm, nearbyCities);
    return nearbyCities;
   
}

/**
   * Filter the cities within a given radius around the selected city by the horizontal coordinate.
   * @param radius The search radius.
   * @param cities1 A map containing city names and their coordinates.
   * @return An unordered map containing the filtered cities.
   */
std::unordered_map<std::string, std::pair<double, double>> SearchingCities::filterCitiesByHorizontal(double radius, std::unordered_map<std::string, std::pair<double, double>> cities1)
{
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities;
    const auto& selectedCity = cities1.find(cityName);
    nearbyCities.reserve(cities1.size());
    std::copy_if(cities1.begin(), cities1.end(), std::inserter(nearbyCities, nearbyCities.end()), [&](const auto& city) {
        const auto& x = city.second.first;
        return selectedCity->second.first + radius >= x && selectedCity->second.first - radius <= x;
        });
    return nearbyCities;
}

/**
     * Filter the cities within a given radius around the selected city by the vertical coordinate.
     * @param radius The search radius.
     * @param cities1 A map containing city names and their coordinates.
     * @return An unordered map containing the filtered cities.
     */
std::unordered_map<std::string, std::pair<double, double>> SearchingCities::filterCitiesByVertical(double radius, std::unordered_map<std::string, std::pair<double, double>> cities1)
{
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities;
    const auto& selectedCity = cities1.find(cityName);
    nearbyCities.reserve(cities1.size());
    std::copy_if(cities1.begin(), cities1.end(), std::inserter(nearbyCities, nearbyCities.end()), [&](const auto& city) {
        const auto& y = city.second.second;
        return selectedCity->second.second + radius >= y && selectedCity->second.second - radius <= y;
        });
    return nearbyCities;
}

/**
     * Filter the cities within a given radius around the selected city based on the distance function determined by the 'norm' parameter.
     * @param radius The search radius.
     * @param norm The norm value used for the distance function.
     * @param cities1 A map containing city names and their coordinates.
     * @return An unordered map containing the filtered cities.
     */
std::unordered_map<std::string, std::pair<double, double>> SearchingCities::filterCitiesByCircle(double radius, int norm, std::unordered_map<std::string, std::pair<double, double>> cities1)
{
    CalculateDistance c;
    std::unordered_map<std::string, std::pair<double, double>> nearbyCities;
    const auto& selectedCity = cities1.find(cityName);
    nearbyCities.reserve(cities1.size());
    std::copy_if(cities1.begin(), cities1.end(), std::inserter(nearbyCities, nearbyCities.end()), [&](const auto& city) {
        const auto& coordinates = city.second;
        double distance = c[norm](coordinates.first, coordinates.second, selectedCity->second.first, selectedCity->second.second);
        return selectedCity->first != city.first && distance <= radius;
        });


    return nearbyCities;
}

/**
 * Prints the number of cities to the north of the selected city.
 */
void SearchingCities::searcNorthCities()
{
    if (cityName == "")
        return;
    const auto& selectedCity = cities.find(cityName);
    std::cout << std::count_if(cities.cbegin(), cities.cend(),
        [&](const auto& city) { return selectedCity->first != city.first&&city.second.second < selectedCity->second.second; });
    std::cout << " cities are to the north of the selected city." << std::endl;
}
