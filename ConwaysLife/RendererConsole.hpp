#pragma once

#include "Renderer.hpp"

class RendererConsole : public Renderer
{
  public:
    void render(const LifeSimulator& simulation);
};