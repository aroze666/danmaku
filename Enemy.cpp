#include "Enemy.hpp"
Enemy::Enemy()
{   
    this->hitbox.setFillColor(sf::Color::Green);
    this->hitbox.setSize({30,30});
}

void Enemy::SetMovementRange(sf::Vector2f range)
{
    this->movement_range = range;
}

void Enemy::Update()
{
    sf::Vector2f enemy_position = this->hitbox.getPosition();
    if(enemy_position.x > movement_range.x)
	this->velocity = {-10,0};
    else if(enemy_position.x <= 0)
	this->velocity = {10,0};
    this->hitbox.setPosition(enemy_position + velocity);
	
}

