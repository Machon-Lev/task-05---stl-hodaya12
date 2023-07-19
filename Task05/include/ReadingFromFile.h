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
class ReadingFromFile {
	std::ifstream file;
	std::unordered_map<std::string, std::pair<double, double>> cities;
	std::string filename;
public:
	ReadingFromFile(const std::string& filename);
	std::unordered_map<std::string, std::pair<double, double>> readCitiesFromFile();

};
