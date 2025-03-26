#include <memory>
#include <cassert>
#include "Game.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<Game> game = std::make_shared<Game>();

    assert(game);

    game->setup();
    game->update();
}
