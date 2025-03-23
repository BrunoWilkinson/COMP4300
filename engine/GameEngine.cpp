#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <fstream>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "Font.h"
#include "System.h"

void GameEngine::setup(
           const std::string& window_name,
           const unsigned int window_width,
           const unsigned int window_height,
           const unsigned int framerate_limit)
{
    m_window.create(
        sf::VideoMode({window_width, window_height}),
        window_name);
    m_window.setFramerateLimit(framerate_limit);
}

void GameEngine::add_font(const std::string& name, const std::string& path)
{
    m_font_map[name] = std::make_shared<Font>(path);
}

void GameEngine::add_system(const std::shared_ptr<System> system)
{
    m_system_list.push_back(system);
}

void GameEngine::update_systems()
{
    for (std::shared_ptr<System> system : m_system_list)
    {
        if (system->is_enabled())
        {
            system->update();
        }
    }
}

void GameEngine::update_debug_window()
{
}

void GameEngine::update()
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

        ImGui::Begin("Debug window");

        update_debug_window();

        m_window.clear();

        update_systems();

        ImGui::End();

        ImGui::SFML::Render(m_window);
        m_window.display();
    }

    ImGui::SFML::Shutdown();
}

