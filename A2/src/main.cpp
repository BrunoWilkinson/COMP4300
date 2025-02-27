#include "../../engine/Game.h"
#include "../../engine/ConfigManager.h"

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
