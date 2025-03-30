#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics/Color.hpp>

namespace utils
{
    inline void sfcolor_to_floats(const sf::Color& SFColor, float col[3])
    {
        col[0] = SFColor.r / 255.0f;
        col[1] = SFColor.g / 255.0f;
        col[2] = SFColor.b / 255.0f;
    }

    inline sf::Color floats_to_sfcolor(const float col[3])
    {
        return sf::Color(col[0] * 255, col[1] * 255, col[2] * 255);
    }
}

#endif
