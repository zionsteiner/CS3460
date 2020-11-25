#include "distributions.hpp"

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

// Helper functions
std::vector<DistributionPair> buildHistogramBins(std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::uint32_t getHistogramIndex(std::vector<DistributionPair>& histogram, std::uint32_t number);

/*
 * Generates uniform histogram
 */
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    // Create histogram bins
    std::vector<DistributionPair> histogram = buildHistogramBins(min, max, numberBins);

    // Generate uniform random numbers and populate bins
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<std::uint32_t> distribution(min, max);
    auto generateUniformRandom = std::bind(distribution, generator);

    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        std::uint32_t randNum = generateUniformRandom();

        std::uint32_t index = getHistogramIndex(histogram, randNum);

        histogram[index].count++;
    }

    return histogram;
}

/*
 * Generates normal histogram
 */
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    // Create histogram bins
    auto min = static_cast<std::uint32_t>(mean - 4 * stdev);
    auto max = static_cast<std::uint32_t>(mean + 4 * stdev - 1);
    std::vector<DistributionPair> histogram = buildHistogramBins(min, max, numberBins);

    // Generate normal random numbers and populate bins
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution distribution(mean, stdev);
    auto generateNormalRandom = std::bind(distribution, generator);

    // why no error here?
    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        // Generate random number, round up, and convert to int
        auto unadjustedRandNum = generateNormalRandom();
        auto randNum = static_cast<std::uint32_t>(ceil(unadjustedRandNum));

        std::uint32_t index;
        if (randNum < min)
        {
            index = 0;
        }
        else if (randNum > max)
        {
            index = static_cast<std::uint32_t>(histogram.size() - 1);
        }
        else
        {
            index = getHistogramIndex(histogram, randNum);
        }

        histogram[index].count++;
    }

    return histogram;
}

/*
 * Generates Poisson histogram
 */
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    // Create histogram bins
    std::uint32_t min = 0;
    std::uint32_t max = numberBins - 1;
    std::vector<DistributionPair> histogram = buildHistogramBins(min, max, numberBins);

    // Generate Poisson random numbers and populate bins
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::poisson_distribution distribution(howOften);
    auto generatePoissonRandom = std::bind(distribution, generator);

    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        // Generate random number, round up, and convert to int
        auto unadjustedRandNum = generatePoissonRandom();
        auto randNum = static_cast<std::uint32_t>(ceil(unadjustedRandNum));

        std::uint32_t index;
        if (randNum > max)
        {
            index = static_cast<std::uint32_t>(histogram.size() - 1);
        }
        else
        {
            index = getHistogramIndex(histogram, randNum);
        }

        histogram[index].count++;
    }

    return histogram;
}

/*
 * Calculates bin edges and returns empty histogram with numberBins
 */
std::vector<DistributionPair> buildHistogramBins(std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> histogram;

    auto increment = static_cast<std::uint32_t>((max - min) / numberBins);
    auto currMin = min;
    auto currMax = currMin + increment;
    for (std::uint8_t i = 0; i < numberBins; ++i)
    {
        histogram.emplace_back(currMin, currMax);

        currMin = currMax + 1;
        currMax = currMin + increment;
    }

    return histogram;
}

/*
 * Given histogram and a number, returns the index of the bin the number belongs to
 */
std::uint32_t getHistogramIndex(std::vector<DistributionPair>& histogram, std::uint32_t number)
{
    auto nBins = histogram.size();
    auto min = histogram[0].minValue;
    auto max = histogram[nBins - 1].maxValue;
    auto increment = static_cast<std::uint32_t>((max - min) / nBins);

    std::uint32_t index = (number - min) / (increment + 1);

    return index;
}

/*
 * Plots given distribution to stdout
 */
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    // Use max bin count to scale bin heights against
    std::uint32_t maxCount = 0;
    for (auto bin : distribution)
    {
        if (bin.count > maxCount)
        {
            maxCount = bin.count;
        }
    }

    std::uint32_t maxValue = distribution[distribution.size() - 1].maxValue;
    std::uint32_t maxDigits = 0;

    auto temp = maxValue;
    while (temp != 0)
    {
        maxDigits++;

        temp /= 10;
    }

    std::cout << title << std::endl;

    for (auto bin : distribution)
    {
        auto nStars = static_cast<std::uint8_t>((bin.count / static_cast<double>(maxCount)) * maxPlotLineSize);

        // Print "[binMin, binMax] :"
        std::cout << "[";
        std::cout << std::setfill(' ') << std::setw(maxDigits) << std::right << std::to_string(bin.minValue);
        std::cout << ", ";
        std::cout << std::setfill(' ') << std::setw(maxDigits) << std::right << std::to_string(bin.maxValue);
        std::cout << "]";
        std::cout << " : ";

        // Print "******", +1 to account for newline
        std::cout << std::setfill('*') << std::setw(nStars + 1) << "\n";
    }

    std::cout << std::endl;
}
