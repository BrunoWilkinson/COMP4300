#include <iostream>
#include "Font.h"

bool Font::set_font(sf::Text& text)
{
    if (!m_valid)
    {
        std::cout << "Font is invalid!" << std::endl;
        return false;
    }

    text.setFont(m_font);
    return true;
}
