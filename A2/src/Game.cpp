#include "engine/imgui/imgui.h"
#include "engine/ConfigManager.h"
#include "engine/EntityManager.h"
#include "engine/Entity.h"

#include <cassert>

#include "Game.h"
#include "Components.h"
#include "RenderSystem.h"

Game::Game()
{
    const std::vector<std::string> config_list = { "Window", "Font", "Player", "Enemy", "Bullet" };
    std::shared_ptr<ConfigManager> config_manager = std::make_shared<ConfigManager>("config.txt", config_list);
    assert(config_manager);

    const std::vector<std::string>& config_window = config_manager->get_config_data(config_list[0]);
    assert(config_window.size() == 4);
    m_config_window = {
        std::stoi(config_window[0]),
        std::stoi(config_window[1]),
        std::stoi(config_window[2]),
        static_cast<bool>(std::stoi(config_window[3])),
    };

    const std::vector<std::string>& config_font = config_manager->get_config_data("Font");
    assert(config_font.size() == 5);
    m_config_font = {
        config_font[0],
        std::stoi(config_font[1]),
        { 
            std::stof(config_font[2]),
            std::stof(config_font[3]),
            std::stof(config_font[4])
        },
    };

    const std::vector<std::string>& config_player = config_manager->get_config_data("Player");
    assert(config_player.size() == 11);
    m_config_player = {
        std::stoi(config_player[0]),
        std::stoi(config_player[1]),
        std::stof(config_player[2]),
        {
            std::stof(config_player[3]),
            std::stof(config_player[4]),
            std::stof(config_player[5]),
        },
        {
            std::stof(config_player[6]),
            std::stof(config_player[7]),
            std::stof(config_player[8]),
        },
        std::stoi(config_player[9]),
        std::stoi(config_player[10]),
    };

    const std::vector<std::string>& config_enemy = config_manager->get_config_data("Enemy");
    assert(config_enemy.size() == 12);
    m_config_enemy = {
        std::stoi(config_enemy[0]),
        std::stoi(config_enemy[1]),
        std::stof(config_enemy[2]),
        std::stof(config_enemy[3]),
        {
            std::stof(config_enemy[4]),
            std::stof(config_enemy[5]),
            std::stof(config_enemy[6]),
        },
        std::stoi(config_enemy[7]),
        std::stoi(config_enemy[8]),
        std::stoi(config_enemy[9]),
        std::stoi(config_enemy[10]),
        std::stoi(config_enemy[11]),
    };

    const std::vector<std::string>& config_bullet = config_manager->get_config_data("Bullet");
    assert(config_bullet.size() == 12);
    m_config_bullet = {
        std::stoi(config_bullet[0]),
        std::stoi(config_bullet[1]),
        std::stof(config_bullet[2]),
        {
            std::stof(config_bullet[3]),
            std::stof(config_bullet[4]),
            std::stof(config_bullet[5]),
        },
        {
            std::stof(config_bullet[6]),
            std::stof(config_bullet[7]),
            std::stof(config_bullet[8]),
        },
        std::stoi(config_bullet[9]),
        std::stoi(config_bullet[10]),
        std::stoi(config_bullet[11]),
    };
}

void Game::start()
{
    GameEngine::setup(
        "A2",
        m_config_window.width,
        m_config_window.height,
        m_config_window.frame_limit
    );
    GameEngine::add_font("halo_dek", m_config_font.path);
    const std::vector<std::string> config_list = { "Window", "Font", "Player", "Enemy", "Bullet" };
    std::shared_ptr<ConfigManager> config_manager = std::make_shared<ConfigManager>("config.txt", config_list);
    assert(config_manager);

    assert(GameEngine::entity_manager());

    // create player
    std::shared_ptr<Entity> player = GameEngine::entity_manager()->add_entity("player");
    std::shared_ptr<CTransform> player_transform = player->add_component<CTransform>(std::make_shared<CTransform>(
        Vector2D(window.getSize().x / 2.f, window.getSize().y / 2.f),
        Vector2D(m_config_player.speed, m_config_player.speed),
        0.f
    ));
    std::shared_ptr<CShape> player_shape = player->add_component<CShape>(std::make_shared<CShape>(
        m_config_player.shape_radius,
        m_config_player.fill_color,
        m_config_player.outline_color, 
        m_config_player.outline_thickness,
        m_config_player.shape_vertices
    ));
    player_shape->shape.setPosition(player_transform->position.x, player_transform->position.y);

    // systems
    std::shared_ptr<RenderSystem> render_system = std::make_shared<RenderSystem>("render_system");
    GameEngine::add_system(render_system);

    update();
}

void Game::update_systems()
{
    GameEngine::update_systems();
}

void Game::update_debug_window()
{
    ImGui::Text("Velocity");
}
