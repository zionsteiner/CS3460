#include "RendererConsole.hpp"

#include "rlutil.h"

void RendererConsole::render(const LifeSimulator& simulation)
{
    rlutil::cls();
    rlutil::hidecursor();

    std::uint8_t sizeX = simulation.getSizeX();
    std::uint8_t sizeY = simulation.getSizeY();
    for (std::uint8_t x = 0; x < sizeX; ++x)
    {
        for (std::uint8_t y = 0; y < sizeY; ++y)
        {
            if (simulation.getCell(x, y))
            {
                rlutil::locate(x + 1, y + 1);
                rlutil::setChar('X');
            }
        }
    }

    rlutil::showcursor();
}