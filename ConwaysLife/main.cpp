#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <thread>

const std::uint16_t N_FRAMES = 1000;

int main()
{
    auto sizeX = static_cast<std::uint8_t>(rlutil::tcols());
    auto sizeY = static_cast<std::uint8_t>(rlutil::trows());

    LifeSimulator sim(sizeX, sizeY);
    PatternAcorn acorn;
    PatternBlinker blinker;
    PatternBlock block;
    PatternGlider glider;
    PatternGosperGliderGun gun;
    sim.insertPattern(acorn, 5, 9);
    sim.insertPattern(gun, sizeX / 4, sizeY / 2);
    sim.insertPattern(blinker, 2, 2);
    sim.insertPattern(blinker, 2, sizeY - 2);
    sim.insertPattern(blinker, sizeX - 4, 2);
    sim.insertPattern(blinker, sizeX - 4, sizeY - 2);
    sim.insertPattern(block, sizeX - 8, sizeY - 6);
    sim.insertPattern(glider, 10, 10);
    RendererConsole renderer;

    for (std::uint16_t frameCount = 0; frameCount < N_FRAMES; ++frameCount)
    {
        renderer.render(sim);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sim.update();
    }

    return 0;
}