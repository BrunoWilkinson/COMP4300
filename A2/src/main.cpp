#include "../../engine/ConfigManager.h"
#include "Game.h"

struct Window 
{
    int width = 0;
    int height = 0;
    int frame_limit = 0;
    bool is_fullscreen = false;
};

struct Font
{
    std::string path = "";
    int size = 0;
    float color[3] = { 0.0f, 0.0f, 0.0f };
};

struct Player
{
    int shape_radius = 0;
    int collision_radius = 0;
    float speed = 0;
    float fill_color[3] = { 0.0f, 0.0f, 0.0f };
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int shape_vertices = 0;
};

struct Enemy
{
    int shape_radius = 0;
    int collision_radius = 0;
    float min_speed = 0.0f;
    float max_speed = 0.0f;
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int min_vertices = 0;
    int max_vertices = 0;
    int small_lifespan = 0;
    int spawn_interval = 0;
};

struct Bullet
{
    int shape_radius = 0;
    int collision_radius = 0;
    float speed = 0.0f;
    float fill_color[3] = { 0.0f, 0.0f, 0.0f };
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int shape_vertices = 0;
    int lifespan = 0;
};

int main(int argc, char* argv[])
{
    ConfigManager config_manager = ConfigManager("config.txt");

    const std::vector<std::string> config_window = config_manager.get_config_data("Window");
    Window window = {
        std::stoi(config_window[0]),
        std::stoi(config_window[1]),
        std::stoi(config_window[2]),
        static_cast<bool>(std::stoi(config_window[3])),
    };

    const std::vector<std::string> config_font = config_manager.get_config_data("Font");
    Font font = {
        config_font[0],
        std::stoi(config_font[1]),
        { 
            std::stof(config_font[2]),
            std::stof(config_font[3]),
            std::stof(config_font[4])
        },
    };

    const std::vector<std::string> config_player = config_manager.get_config_data("Player");
    Player player = {
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
    Enemy enemy = {
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
    Bullet bullet = {
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

    Game* game = new Game();
    game->setup( 
        "A2",
        window.width,
        window.height,
        window.frame_limit
    );
    game->init();
}
