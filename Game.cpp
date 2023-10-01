#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
{
    this->window_size.x = window.getSize().x;
    this->window_size.y = window.getSize().y;
    player.SetPosition({500,0});
    player.SetMovementRange(window_size);
    Enemy x;
    x.SetMovementRange(window_size);
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
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
	if(is_Collide(player.GetHitbox(), enemy->GetHitbox()))
	{
	    float x = enemy->GetVelcoity().x;
	    float y = enemy->GetVelcoity().y;
	    player.SetVelocity({x*(-1), y*(-1)});
	    enemy->SetVelocity({x*-1,y*-1});
	}
}
void Game::Update()
{
    player.Update();
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
	enemy->Update();
}

bool Game::is_Collide(const sf::Shape &a, const sf::Shape &b)
{
    if(a.getGlobalBounds().intersects(b.getGlobalBounds()))
       return true;
    return false;
}
