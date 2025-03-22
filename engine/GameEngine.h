#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <string>

class GameEngine
{
    sf::Clock m_delta_clock;
    sf::RenderWindow m_window;

protected:
    virtual void update_systems();
    virtual void update_debug_window();

public:
    void init();
    virtual void setup(
	const std::string& window_name,
	const unsigned int window_width,
	const unsigned int window_height,
	const unsigned int frame_limit);
};

#endif
