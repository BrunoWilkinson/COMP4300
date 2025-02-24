#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Game.h"

Game::Game(const std::string& path, const std::string& window_name);
{
	init(path, window_name);
}

void Game::init(const std::string& path, const std::string& window_name)
{
    ConfigManager configManager("config.txt");
    sf::RenderWindow window(sf::VideoMode({configManager.getWindowWidth(), configManager.getWindowHeight()}), "Assignment 1");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window))
    {
        return -1;
    }
    sf::Clock deltaClock;


    while (window.isOpen())
    {
	sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();
        for (Shape* shape : configManager.getShapes())
        {
            shape->draw(window, deltaClock, configManager.getFonts()[0]);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void Game::run()
{
}
