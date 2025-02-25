#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <fstream>
#include <iostream>
#include <cmath>
#include "Game.h"

Game::Game(const std::string& path,
           const std::string& window_name,
           const unsigned int window_width,
           const unsigned int window_height,
           const unsigned int framerate_limit)
{
    m_window.create(
        sf::VideoMode({window_width, window_height}),
        window_name);
    m_window.setFramerateLimit(framerate_limit);

    init();
}

void Game::run()
{
}

void Game::init()
{
    if (!ImGui::SFML::Init(m_window))
    {
        // TODO: add logging error
        return;
    }

    while (m_window.isOpen())
    {
	sf::Event event;
        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(m_window, event);

            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        ImGui::SFML::Update(m_window, m_delta_clock.restart());

        m_window.clear();

        // run ecs systems
        run();

        m_window.display();
    }

    ImGui::SFML::Shutdown();
}

