#include "PatternGosperGliderGun.hpp"

PatternGosperGliderGun::PatternGosperGliderGun()
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
    pattern[24][0] = true;
    pattern[22][1] = true;
    pattern[24][1] = true;
    pattern[12][2] = true;
    pattern[13][2] = true;
    pattern[20][2] = true;
    pattern[21][2] = true;
    pattern[34][2] = true;
    pattern[35][2] = true;
    pattern[11][3] = true;
    pattern[15][3] = true;
    pattern[20][3] = true;
    pattern[21][3] = true;
    pattern[34][3] = true;
    pattern[35][3] = true;
    pattern[0][4] = true;
    pattern[1][4] = true;
    pattern[10][4] = true;
    pattern[16][4] = true;
    pattern[20][4] = true;
    pattern[21][4] = true;
    pattern[0][5] = true;
    pattern[1][5] = true;
    pattern[10][5] = true;
    pattern[14][5] = true;
    pattern[16][5] = true;
    pattern[17][5] = true;
    pattern[22][5] = true;
    pattern[24][5] = true;
    pattern[10][6] = true;
    pattern[16][6] = true;
    pattern[24][6] = true;
    pattern[11][7] = true;
    pattern[15][7] = true;
    pattern[12][8] = true;
    pattern[13][8] = true;
}

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    return pattern[x][y];
}
