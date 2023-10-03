#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
{
    this->window_size.x = window.getSize().x;
    this->window_size.y = window.getSize().y;
    player.SetPosition({500,300});
    player.SetMovementRange(window_size);
    player.SetVelocity({3,3});
    Enemy x;
    x.SetMovementRange(window_size);
    x.SetVelocity({-20,-20});
    enemy_list.push_back(x);
}

void Game::GeneralEvent()
{
    player.Event();
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
	enemy->Event();
}
void Game::CollisionEvent()
{

}

void Game::Update()
{
    player.Update();
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
	enemy->Update();
}

bool Game::is_Collide(const sf::Shape &a, const sf::Shape &b)
{
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}
