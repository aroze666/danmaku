#include "Game.hpp"

Game::Game(sf::RenderWindow &window) 
{
    srand(time(0));
    window_size = sf::Vector2f(window.getSize());
    player.SetPosition({400,300});
    player.SetMovementRange(scene.scene_size);
    player.SetWindow(&window);
    player.SetVelocity({3,3});
    this->respawn_time = 3000;
}

void Game::create_Enemy()
{
    Enemy new_enemy;
    new_enemy.SetMovementRange(scene.scene_size);
    new_enemy.SetPosition({(float)(rand()%(int)scene.scene_size.x), 100});
    int x_velocity = rand() % 6 - 2;
    int y_velocity = rand() % 6 - 2;
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
	enemy->FireBullet(player.GetHitbox().getPosition());
    }
    if(time > respawn_time)
    {
	create_Enemy();
	enemy_respawn_clock = sf::Clock();
    }
}
void Game::CollisionEvent()
{
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
    {
	for(auto enemy_2 = std::next(enemy,1); enemy_2!=enemy_list.end(); enemy_2++)
	    if(!enemy->IsHit() && !enemy_2->IsHit() && is_Collide(enemy->GetHitbox(), enemy_2->GetHitbox()))
	    {
		sf::Vector2f enemy_velocity;
		enemy_velocity = enemy->GetVelcoity();
		enemy->SetVelocity(enemy_2->GetVelcoity());
		enemy_2->SetVelocity(enemy_velocity);
	    }
	if(!enemy->IsHit() && (is_Collide(player.GetHitbox(), enemy->GetHitbox())))
	{
	    enemy->SetHit(true);
	    std::cout << "Taken Damage from hitbox.\n";
	    if(respawn_time > 600)
		respawn_time -= 100;
	}
	if(!enemy->IsHit() && player.IsBulletHit(enemy->GetHitbox()))
	{
	    enemy->SetHit(true);
	    std::cout << "Killed an enemy.\n";
	}
	if(enemy->IsBulletHit(player.GetHitbox()))
	    std::cout << "Taken Damage from bullets.\n";
    }
    enemy_list.remove_if([](Enemy enemy){return enemy.IsHit() && !enemy.BulletExist();});
}


void Game::Update()
{
    player.Update();
    ray.Update(player.GetPlayerCenter(), player.GetPlayerAimVector(), scene);
    for(auto enemy = enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
    {
	enemy->Update();
    }

}

bool Game::is_Collide(const sf::Shape &a, const sf::Shape &b)
{
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}
