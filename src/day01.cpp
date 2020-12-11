#include "day01.hpp"    // first my includes

#include <algorithm>    // then system
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <numeric>
#include <string>
#include <vector>


// static in this context means it is relevant only for this cpp file, will not be visible from outside
static auto get_ints_from_file(const std::string& fileName) {
    std::ifstream input{fileName}; // no need to close, will be freed once variable input goes out of scope
    
    // any stream in C++ is convertible to bool
    if (!input) {
        throw std::string("Could not open file ") + fileName;            
    }

    return std::vector<int>(std::istream_iterator<int>{input},  // reads ints ignoring whitespaces (can be configured)
                            std::istream_iterator<int>{});
}

/*
ORIGINAL NAIVE SOLUTION

static std::vector<std::array<int, 2>> get_each_two_numbers_of_given_sum(const std::vector<int>& values, int desiredSum) {
    std::vector<std::array<int, 2>> results;

    std::array<int, 2> candidate{0, 0};

    const int maxValue = desiredSum - 1;
    for (const int a : values) {
        if (a > maxValue) continue;

        for (const int b : values) {
            if (a + b == desiredSum) {
                candidate[0] = a;
                candidate[1] = b;

                std::sort(candidate.begin(), candidate.end()); 
                
                if (!std::any_of(results.begin(), results.end(), [candidate](const std::array<int, 2>& item) { return item[0] == candidate[0] and item[1] == candidate[1]; })) {
                   results.push_back({candidate[0], candidate[1]});
                }
            }
        }
    }

    return results;
}

static std::vector<std::array<int, 3>> get_each_three_numbers_of_given_sum(const std::vector<int>& values, int desiredSum) {
    std::vector<std::array<int, 3>> results;

    std::array<int, 3> candidate{0, 0, 0};

    const int maxValue = desiredSum - 1;
    for (const int a : values) {
        if (a > maxValue) continue;

        for (const int b : values) {
            if (a + b > maxValue) continue;

            for (const int c : values) {
                if (a + b + c == desiredSum) {
                    candidate[0] = a;
                    candidate[1] = b;
                    candidate[2] = c;

                    std::sort(candidate.begin(), candidate.end());
                    if (!std::any_of(results.begin(), results.end(), [candidate](const std::array<int, 3>& item) { return item[0] == candidate[0] and item[1] == candidate[1] and item[2] == candidate[2]; })) {
                        results.push_back({candidate[0], candidate[1], candidate[2]});
                    }
                }
            }
        }
    }

    return results;
}
*/

// Smart solution suggested by Hanka Dusikova
static std::optional<std::vector<int>> get_n_numbers_of_given_sum(int n, const std::vector<int>& values, int desiredSum) {
    assert(n > 0);

    if (n == 1) {
        if (not std::binary_search(values.begin(), values.end(), desiredSum)) return std::nullopt;

        return std::vector<int>{desiredSum};    // no need to wrap in optional
    }
    else {
        for (int item: values) {
            if (item > desiredSum) break;

            auto result = get_n_numbers_of_given_sum(n-1, values, desiredSum-item);
            if (not result) continue;

            result->push_back(item);

            return result;
        }

        return std::nullopt;
    }
}

static void print_result_evaluation(const std::string& title, const std::optional<std::vector<int>>& result) {

    if (not result) {
        std::cout << title << "No solution found" << "\n";
        return;
    }
        
    std::cout << title << std::accumulate(result->begin(), result->end(), 1, std::multiplies<>{}) << "\n";    
}

// day01:: defines symbol already defined elsewhere
int day01::solve(const std::string& fileName) {
    std::cout << "-= Day 01 =-\n";
    std::string day01_input{fileName};

    std::vector<int> values = get_ints_from_file(fileName);
    std::sort(values.begin(), values.end());

    try {            
        print_result_evaluation(std::string{"Part A: "}, get_n_numbers_of_given_sum(2, values, 2020));
        print_result_evaluation(std::string{"Part B: "}, get_n_numbers_of_given_sum(3, values, 2020));

        return 0;

    } catch (std::string errorDescription) {
        std::cerr << errorDescription;

        return 1;     
    }    
}

