#include "../../engine/Game.h"
#include "../../engine/ConfigManager.h"

struct Window 
{
    int width = 0;
    int height = 0;
    int frame_limit = 0;
    bool is_fullscreen = false;
};

struct Font
{
    std::string font_file = "";
    int font_size = 0;
    float color[3] = { 0.0f, 0.0f, 0.0f };
};

struct Player
{
    int shape_radius = 0;
    int collision_radius = 0;
    int speed = 0;
    float fill_color[3] = { 0.0f, 0.0f, 0.0f };
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int shape_verices = 0;
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
    float fill_color[3] = { 0.0f, 0.0f, 0.0f };
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int shape_verices = 0;
    int lifespan = 0;
};

int main(int argc, char* argv[])
{
    // Run the init from the game engine
    ConfigManager config_manager = ConfigManager("config.txt");
    config_data window = config_manager.get_config_data("Window");

    for (std::string& s : window)
    {
         std::cout << s << std::endl;
    }
}
