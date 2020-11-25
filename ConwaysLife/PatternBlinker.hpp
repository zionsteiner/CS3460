#pragma once

#include "Pattern.hpp"

#include <array>

class PatternBlinker : public Pattern
{
  public:
    PatternBlinker();
    std::uint8_t getSizeX() const
    {
        return static_cast<std::uint8_t>(pattern.size());
    }
    std::uint8_t getSizeY() const
    {
        return static_cast<std::uint8_t>(pattern[0].size());
    }
    bool getCell(std::uint8_t x, std::uint8_t y) const;

  private:
    std::array<std::array<bool, 1>, 3> pattern;
};
