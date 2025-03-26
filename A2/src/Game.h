#ifndef GAME_H
#define GAME_H

#include "../../engine/GameEngine.h"

struct WindowConfig
{
    int width = 0;
    int height = 0;
    int frame_limit = 0;
    bool is_fullscreen = false;
};

struct FontConfig
{
    std::string path = "";
    int size = 0;
    float color[3] = { 0.0f, 0.0f, 0.0f };
};

struct PlayerConfig
{
    int shape_radius = 0;
    int collision_radius = 0;
    float speed = 0;
    float fill_color[3] = { 0.0f, 0.0f, 0.0f };
    float outline_color[3] = { 0.0f, 0.0f, 0.0f };
    int outline_thickness = 0;
    int shape_vertices = 0;
};

struct EnemyConfig
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

struct BulletConfig
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

class Game : public GameEngine
{
	WindowConfig m_config_window;
	FontConfig m_config_font;
	PlayerConfig m_config_player;
	EnemyConfig m_config_enemy;
	BulletConfig m_config_bullet;

protected:
	virtual void update_systems() override;
	virtual void update_debug_window() override;

public:
	void setup();
	Game();
};

#endif

