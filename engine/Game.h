#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

class Game
{
    sf::Clock m_delta_clock;
	sf::RenderWindow m_window;

	virtual void run();
	void init();

public:
	Game(const std::string& path,
	  const std::string& window_name,
	  const unsigned int window_width,
	  const unsigned int window_height,
	  const unsigned int frame_linit);
};


#endif
