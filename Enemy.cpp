#include "Enemy.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
Enemy::Enemy()
{   
    this->hitbox.setFillColor(sf::Color::Green);
    this->hitbox.setSize({30,30});
    this->is_hit = false;
}
void Enemy::SetMovementRange(sf::Vector2f range)
{
    this->movement_range = range;
}
void Enemy::SetVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
sf::RectangleShape Enemy::GetHitbox()
{
    return hitbox;
}
void Enemy::Event()
{
    if(hitbox.getPosition().x > movement_range.x - hitbox.getSize().x && this->velocity.x > 0)
	this->velocity = {-1*this->velocity.x,this->velocity.y};
    if(hitbox.getPosition().x <= 0 && this->velocity.x < 0)
	this->velocity = {-1*this->velocity.x,this->velocity.y};
    if(hitbox.getPosition().y > movement_range.y - hitbox.getSize().y && this->velocity.y > 0)
	this->velocity = {this->velocity.x,-1*this->velocity.y};
    if(hitbox.getPosition().y <= 0 && this->velocity.y < 0)
	this->velocity = {this->velocity.x,-1*this->velocity.y};

}
void Enemy::Update()
{
    this->hitbox.setPosition(hitbox.getPosition()+velocity);
}

