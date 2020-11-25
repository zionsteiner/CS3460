#include "PatternBlinker.hpp"

PatternBlinker::PatternBlinker()
{
    // Initialize all to false
    for (std::size_t x = 0; x < pattern.size(); ++x)
    {
        for (std::size_t y = 0; y < pattern[0].size(); ++y)
        {
            pattern[x][y] = false;
        }
    }

    // Pattern
    pattern[0][0] = true;
    pattern[1][0] = true;
    pattern[2][0] = true;
}

bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    return pattern[x][y];
}
