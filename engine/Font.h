#ifndef FONT_H
#define FONT_H

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Font
{
public:
    sf::Font m_font;
    bool m_valid = false;
    std::string m_path = "";

public:
    Font(const std::string& path) 
        : m_path(path)
    {
        m_valid = m_font.loadFromFile(m_path);
    }

    bool set_font(sf::Text& text);
};

#endif
