//
// Created by Zion on 10/2/2020.
//

#include "distributions.hpp"

int main()
{
    std::uint32_t howMany = 100000;
    auto uniform = generateUniformDistribution(howMany, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(howMany, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(howMany, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);

    return 0;
}