#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
	void init(const std::string& path, const std::string& window_name);

public:
	Game(const std::string& path, const std::string& window_name);
	void run();

};

#endif
