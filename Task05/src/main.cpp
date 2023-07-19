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
#include "cities.h"



int main() {
    int input = 0;
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