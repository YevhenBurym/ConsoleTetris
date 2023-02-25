//
// Created by Yevhen on 25.02.2023.
//

#pragma once

#include <chrono>
#include <random>

class RandGenerator {
private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
public:
    RandGenerator();
    double getRandNumber();
};