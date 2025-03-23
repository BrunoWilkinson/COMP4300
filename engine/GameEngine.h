#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>


class Font;
class System;

class GameEngine
{
    sf::Clock m_delta_clock;
    sf::RenderWindow m_window;
    std::map<std::string, std::shared_ptr<Font>> m_font_map;
    std::vector<std::shared_ptr<System>> m_system_list;

protected:
    virtual void update_systems();
    virtual void update_debug_window();

public:
    void update();
    void add_font(const std::string& name, const std::string& path);
    void add_system(std::shared_ptr<System> system);
    virtual void setup(
	const std::string& window_name,
	const unsigned int window_width,
	const unsigned int window_height,
	const unsigned int frame_limit);
};

#endif
