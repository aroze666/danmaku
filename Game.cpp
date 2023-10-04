#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
{
    this->window_size.x = window.getSize().x;
    this->window_size.y = window.getSize().y;
    player.SetPosition({500,300});
    player.SetMovementRange(window_size);
    player.SetVelocity({3,3});
   }

void Game::create_Enemy()
{
    Enemy new_enemy;
    new_enemy.SetMovementRange(window_size);
    new_enemy.SetPosition({window_size.x/2, 100});
    new_enemy.SetVelocity({(float)(rand()%4-2),(float)(rand()%4-2)});
    enemy_list.push_back(new_enemy);
}
void Game::GeneralEvent()
{
    srand((int)clock.getElapsedTime().asMicroseconds());
    float time = clock.getElapsedTime().asMilliseconds();
    player.Event();
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
    {
	enemy->Event();
    }
    if((int)time % 1000 < 10)
	create_Enemy();
}
bool hitEnemy(Enemy enemy)
{
    return enemy.IsHit();
}
void Game::CollisionEvent()
{
    enemy_list.remove_if(hitEnemy);
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
    {
	if(player.IsBulletHit(enemy->GetHitbox()))
	{
	    enemy->SetHit(true);
	}
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
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}
