#include "imgui/imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui/imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <iostream>
#include <cmath>
#include <cassert>
#include "Game.h"
#include "Font.h"
#include "System.h"
#include "EntityManager.h"

void GameEngine::setup(
           const std::string& window_name,
           const unsigned int window_width,
           const unsigned int window_height,
           const unsigned int framerate_limit)
{
    window.create(
        sf::VideoMode({window_width, window_height}),
        window_name
    );
    window.setFramerateLimit(framerate_limit);
    m_entity_manager = std::make_shared<EntityManager>();
}

void GameEngine::add_font(const std::string& name, const std::string& path)
{
    m_font_map[name] = std::make_shared<Font>(path);
}

void GameEngine::add_system(const std::shared_ptr<void> new_system)
{
    std::shared_ptr<System> system = static_pointer_cast<System>(new_system);
    assert(system);
    m_system_list.push_back(system);
}

void GameEngine::update_systems()
{
    for (std::shared_ptr<System> system : m_system_list)
    {
        if (system->is_enabled())
        {
            system->update(this);
        }
    }
}

void GameEngine::update_debug_window()
{
}

void GameEngine::update()
{
    if (!ImGui::SFML::Init(window))
    {
        // TODO: add logging error
        return;
    }

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

        m_entity_manager->update();

        ImGui::SFML::Update(window, delta_clock.restart());

        ImGui::Begin("Debug window");

        update_debug_window();

        window.clear();

        update_systems();

        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

