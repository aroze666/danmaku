#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
{
    srand(time(0));
    this->window_size.x = window.getSize().x;
    this->window_size.y = window.getSize().y;
    player.SetPosition({500,300});
    player.SetMovementRange(window_size);
    player.SetVelocity({3,3});
    this->respawn_time = 3000;
}

void Game::create_Enemy()
{
    Enemy new_enemy;
    new_enemy.SetMovementRange(window_size);
    new_enemy.SetPosition({window_size.x/2, 100});
    int x_velocity = rand() % 4 - 2;
    int y_velocity = rand() % 4 - 2;
    if(x_velocity != 0 && y_velocity != 0)
    {
	new_enemy.SetVelocity({(float)x_velocity,(float)y_velocity});
	enemy_list.push_back(new_enemy);
    }
}
void Game::GeneralEvent()
{
    float time = enemy_respawn_clock.getElapsedTime().asMilliseconds();
    player.Event();
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
    {
	enemy->Event();
    }
    if(time > respawn_time)
    {
	create_Enemy();
	if(respawn_time > 200)
	    respawn_time -= 100;
	enemy_respawn_clock = sf::Clock();
    }
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
	for(auto enemy_2 = std::next(enemy,1); enemy_2!=enemy_list.end(); enemy_2++)
	    if(is_Collide(enemy->GetHitbox(), enemy_2->GetHitbox()))
	    {
		sf::Vector2f enemy_velocity;
		enemy_velocity = enemy->GetVelcoity();
		enemy->SetVelocity(enemy_2->GetVelcoity());
		enemy_2->SetVelocity(enemy_velocity);
	    }
	if(is_Collide(player.GetHitbox(), enemy->GetHitbox()))
	{
	    player.SetVelocity(enemy->GetVelcoity());
	    enemy->SetHit(true);
	}
	if(player.IsBulletHit(enemy->GetHitbox()))
	    enemy->SetHit(true);
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
