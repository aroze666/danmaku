#include "Game.hpp"

Game::Game() : PLAYER_SIZE({10,10}), PLAYER_BULLET_SIZE({5,5})
{
    
}

void Game::Update()
{
    player.Update();
}
