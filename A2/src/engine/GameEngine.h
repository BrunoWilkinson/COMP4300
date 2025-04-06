#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Font;
class System;
class EntityManager;

class GameEngine
{
    std::map<std::string, std::shared_ptr<Font>> m_font_map;
    std::vector<std::shared_ptr<System>> m_system_list;
    std::shared_ptr<EntityManager> m_entity_manager;

protected:
    virtual void update_systems();
    virtual void update_debug_window();

public:
    sf::Clock delta_clock;
    sf::RenderWindow window;

    void update();
    void add_font(const std::string& name, const std::string& path);
    void add_system(std::shared_ptr<void> new_system);
    std::shared_ptr<EntityManager> entity_manager() const { return m_entity_manager; }
    virtual void setup(
	const std::string& window_name,
	const unsigned int window_width,
	const unsigned int window_height,
	const unsigned int frame_limit);
};

#endif
