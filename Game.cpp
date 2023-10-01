#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
{
    this->window_size.x = window.getSize().x;
    this->window_size.y = window.getSize().y;
    Enemy x;
    x.SetMovementRange(window_size);
    enemy_list.push_back(x);
}

void Game::Update()
{
    player.Update();
    for(std::list<Enemy>::iterator it=enemy_list.begin(); it!=enemy_list.end(); it++)
	it->Update();
}
