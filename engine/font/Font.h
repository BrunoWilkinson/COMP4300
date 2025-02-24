#ifndef FONT_H
#define FONT_H

class Font
{
public:
    sf::Font m_font;
    bool m_valid = false;
    std::string m_path = "";
    int m_size = -1;
    sf::Color m_color;

public:
    Font(const std::string& path, const int size, const sf::Color& color) 
        : m_path(path)
        , m_size(size)
        , m_color(color)
    {
        m_valid = m_font.loadFromFile(m_path);
    }

    bool setText(const std::string& string, sf::Text& text)
    {
        if (!m_valid)
        {
            std::cout << "Font is invalid!" << std::endl;
            return false;
        }

        text.setFont(m_font);
        text.setCharacterSize(m_size);
        text.setFillColor(m_color);
        text.setString(string);

        return true;
    }
};
