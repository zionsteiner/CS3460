#include "sortutils.hpp"

#include <algorithm>
#include <functional>
#include <random>

int main()
{
    /* Create initial random array */
    SourceArray source;

    /* Fill array with random numbers */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-10000000, 10000000);
    auto rand = std::bind(distribution, generator);

    for (size_t i = 0; i < source.size(); ++i)
    {
        source[i] = rand();
    }

    /* Prepare other array types */
    // 1. Sorted
    SourceArray sortedSource = source;
    std::sort(sortedSource.begin(), sortedSource.end());

    // 2. Reversed
    SourceArray reversedSource = sortedSource;
    std::reverse(reversedSource.begin(), reversedSource.end());

    // 3. Organ-pipe
    SourceArray organPipeSource = sortedSource;
    organPipeStdArray(organPipeSource);

    // 4. Rotate
    SourceArray rotatedSource = sortedSource;
    std::rotate(rotatedSource.begin(), rotatedSource.begin() + 1, rotatedSource.end());

    /* Evaluate timing */
    evaluateRawArray(source, sortedSource, reversedSource, organPipeSource, rotatedSource);
    evaluateStdArray(source, sortedSource, reversedSource, organPipeSource, rotatedSource);
    evaluateStdVector(source, sortedSource, reversedSource, organPipeSource, rotatedSource);
}