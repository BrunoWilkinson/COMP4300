#ifndef UTILS_H
#define UTILS_H

#include <Color.hpp>

namespace utils
{
    void SFToImGuiColor(const sf::Color& SFColor, float col[3])
    {
        col[0] = SFColor.r / 255.0f;
        col[1] = SFColor.g / 255.0f;
        col[2] = SFColor.b / 255.0f;
    }

    sf::Color ImGuiToSFColor(const float col[3])
    {
        retun sf::Color(col[0] * 255, col[1] * 255, col[2] * 255);
    }
}
