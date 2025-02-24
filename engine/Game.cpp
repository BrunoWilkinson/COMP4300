#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <iostream>
#include <cmath>
#include "game.h"

Game::Game(const std::string& path, const std::string& window_name);
{
	init(path, window_name);
}

void Game::init(const std::string& path, const std::string& window_name)
{
}

void Game::run()
{
}
