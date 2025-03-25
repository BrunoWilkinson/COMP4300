#include "Game.h"
#include "../../engine/imgui/imgui.h"
#include "../../engine/ConfigManager.h"
#include "../../engine/EntityManager.h"
#include "../../engine/Entity.h"

Game::Game()
{
    ConfigManager config_manager = ConfigManager("config.txt");

    const std::vector<std::string> config_window = config_manager.get_config_data("Window");
    m_config_window = {
        std::stoi(config_window[0]),
        std::stoi(config_window[1]),
        std::stoi(config_window[2]),
        static_cast<bool>(std::stoi(config_window[3])),
    };

    const std::vector<std::string> config_font = config_manager.get_config_data("Font");
    m_config_font = {
        config_font[0],
        std::stoi(config_font[1]),
        { 
            std::stof(config_font[2]),
            std::stof(config_font[3]),
            std::stof(config_font[4])
        },
    };

    const std::vector<std::string> config_player = config_manager.get_config_data("Player");
    m_player = {
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

    const std::vector<std::string> config_enemy = config_manager.get_config_data("Enemy");
    m_enemy = {
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

    const std::vector<std::string> config_bullet = config_manager.get_config_data("Bullet");
    m_bullet = {
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

void Game::setup()
{
    GameEngine::setup( 
        "A2",
        m_config_window.width,
        m_config_window.height,
        m_config_window.frame_limit
    );
    GameEngine::add_font("halo_dek", m_config_font.path);

    assert(GameEngine::entity_manager());

    // create player
    std::shared_ptr<Entity> player = GameEngine::entity_manager()->add_entity("player");
}

void Game::update_systems()
{}

void Game::update_debug_window()
{
    ImGui::Text("Velocity");
}
