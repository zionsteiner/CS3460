#include "LifeSimulator.hpp"

#include <utility>

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    field.resize(sizeX, std::vector<bool>(sizeY, false));
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    // Sensible defaults
    std::uint8_t sizeX = getSizeX();
    if (startX >= sizeX)
    {
        startX = sizeX - 1;
    }

    std::uint8_t sizeY = getSizeY();
    if (startY >= sizeY)
    {
        startY = sizeY - 1;
    }

    // Calculate end coordinates given pattern size and starting coordinates
    std::uint8_t patternSizeX = pattern.getSizeX();
    std::uint8_t patternSizeY = pattern.getSizeY();

    decltype(startX) endX = ((startX + patternSizeX - 1) < sizeX) ? (startX + patternSizeX - 1) : sizeX - 1;
    decltype(startX) endY = ((startY + patternSizeY - 1) < sizeY) ? (startY + patternSizeY - 1) : sizeY - 1;

    // Add pattern
    for (auto x = startX; x <= endX; ++x)
    {
        for (auto y = startY; y <= endY; ++y)
        {
            field[x][y] = pattern.getCell(x - startX, y - startY);
        }
    }
}

void LifeSimulator::update()
{
    const std::uint8_t UNDERPOP_THRESH = 2;
    const std::uint8_t OVERPOP_THRESH = 3;

    // Find Coordinate to update
    std::vector<Coordinate> liveCoordinate;
    std::vector<Coordinate> deadCoordinate;

    std::uint8_t sizeX = getSizeX();
    std::uint8_t sizeY = getSizeY();
    for (std::uint8_t x = 0; x < sizeX; ++x)
    {
        for (std::uint8_t y = 0; y < sizeY; ++y)
        {
            std::uint8_t liveNeighborCount = getLiveNeighborCount(x, y);

            // Cell is live
            if (getCell(x, y))
            {
                // Cell dies
                if (liveNeighborCount < UNDERPOP_THRESH || liveNeighborCount > OVERPOP_THRESH)
                {
                    deadCoordinate.emplace_back(x, y);
                }
            }
            // Cell is dead
            else
            {
                // Cell revives
                if (liveNeighborCount == 3)
                {
                    liveCoordinate.emplace_back(x, y);
                }
            }
        }
    }

    // Kill cells
    for (auto coord : deadCoordinate)
    {
        field[coord.first][coord.second] = false;
    }

    // Revive cells
    for (auto coord : liveCoordinate)
    {
        field[coord.first][coord.second] = true;
    }
}

std::uint8_t LifeSimulator::getLiveNeighborCount(std::uint8_t x, std::uint8_t y)
{
    std::uint8_t count = 0;

    // Define neighbor cells
    std::vector<Coordinate> coords;
    coords.emplace_back(decWrap(x, true), decWrap(y, false));
    coords.emplace_back(decWrap(x, true), y);
    coords.emplace_back(decWrap(x, true), incWrap(y, false));
    coords.emplace_back(x, decWrap(y, false));
    coords.emplace_back(x, incWrap(y, false));
    coords.emplace_back(incWrap(x, true), decWrap(y, false));
    coords.emplace_back(incWrap(x, true), y);
    coords.emplace_back(incWrap(x, true), incWrap(y, false));

    // Count
    for (auto coord : coords)
    {
        if (getCell(coord.first, coord.second))
        {
            count++;
        }
    }

    return count;
}

std::uint8_t LifeSimulator::decWrap(std::uint8_t index, bool isX)
{
    std::uint8_t maxIndex = isX ? getSizeX() - 1 : getSizeY() - 1;

    if (index == 0)
    {
        return maxIndex;
    }
    else
    {
        return index - 1;
    }
}

std::uint8_t LifeSimulator::incWrap(std::uint8_t index, bool isX)
{
    std::uint8_t maxIndex = isX ? getSizeX() - 1 : getSizeY() - 1;

    if (index == maxIndex)
    {
        return 0;
    }
    else
    {
        return index + 1;
    }
}

std::uint8_t LifeSimulator::getSizeX() const
{
    return static_cast<std::uint8_t>(field.size());
}

std::uint8_t LifeSimulator::getSizeY() const
{
    // Assumes the field is square
    return static_cast<std::uint8_t>(field[0].size());
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    return field[x][y];
}