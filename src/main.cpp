#include <iostream>
#include <string>

#include "day01.hpp"

int main(int argc, char **argv) {
    std::cout << "Advent of Code 2020\n\n";

    if (argc != 3) {
        std::cerr << "Exactly two arguments expected:\nmain <dayNumber> <inputFile>.";

        return 1;
    }

    int dayNumber;
    try {
        dayNumber = std::stoi(argv[1]);
    } catch (const std::invalid_argument&) {                    // const exception& is faster than copy approach
        std::cerr << argv[1] << " is not a valid day number.";
        return 1;
    } catch (const std::out_of_range&) {
        std::cerr << argv[1] << " is out of range.";
        return 1;
    }

    switch (dayNumber) {
        case 1:
            return day01::solve(argv[2]);

        default:
            std::cerr << "Number of the day " << dayNumber << " is not implemented.";
            return 1;
    }    
}
