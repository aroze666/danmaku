#include "Enemy.hpp"
Enemy::Enemy(sf::Vector2f hitbox_size, sf::Vector2f bullet_size) : HITBOX_SIZE(hitbox_size), BULLET_SIZE(bullet_size)
{   
    srand(time(0));
    this->hitbox.setFillColor(sf::Color::Green);
    this->hitbox.setSize(HITBOX_SIZE);
    this->hitbox.setPosition(300,300);
}

void Enemy::Update()
{
    sf::Vector2f enemy_position = this->hitbox.getPosition();
    int random = rand() % 30;
    if(enemy_position.x > 800)
	this->velocity = {-10,0};
    else if(enemy_position.x < 0)
	this->velocity = {10,0};
    else if(random == 0)
	this->velocity = {-10,0};
    else if(random == 1)
	this->velocity = {10,0};
    this->hitbox.setPosition(enemy_position + velocity);
	
}

