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
#include "CalculateDistance.h"
class SearchingCities {
	std::string cityName;
	std::unordered_map<std::string, std::pair<double, double>> cities;
public:
	SearchingCities(const std::unordered_map<std::string, std::pair<double, double>>&,const std::string&);
	void searchCitiesInRadius( double radius, int norm);
	std::unordered_map<std::string, std::pair<double, double>> filterCities(double radius, int norm);
	std::unordered_map<std::string, std::pair<double, double>> filterCitiesByHorizontal(double radius, std::unordered_map<std::string, std::pair<double, double>> cities1);
	std::unordered_map<std::string, std::pair<double, double>> filterCitiesByVertical(double radius, std::unordered_map<std::string, std::pair<double, double>> cities1);
	std::unordered_map<std::string, std::pair<double, double>> filterCitiesByCircle(double radius, int norm, std::unordered_map<std::string, std::pair<double, double>> cities1);
	void searcNorthCities();
};