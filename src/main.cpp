#include "engine/Engine.hpp"

#include "game/SpaceShooterGame.hpp"

int main(int argc, char *argv[])
{
    SpaceShooterGame game;
    Engine engine(game);
    engine.initialize("Space Shooter", 800, 600);
    engine.main_loop();
    return 0;
}
