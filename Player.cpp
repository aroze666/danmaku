#include "Player.hpp"
Player::Player()
{
    this->hitbox.setSize({30,30});
    this->bullet_size = {5,5};
}
void Player::SetMovementRange(sf::Vector2f range)
{ this->movement_range = range;
}
void Player::SetHitboxSize(sf::Vector2f size)
{
    this->hitbox.setSize(size);
}
void Player::SetBulletSize(sf::Vector2f size)
{
    this->bullet_size = size;
}
void Player::SetPosition(sf::Vector2f position)
{
    this->hitbox.setPosition(position);
}
void Player::SetVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
sf::RectangleShape Player::GetHitbox()
{
    return hitbox;
}
bool is_hit(const sf::RectangleShape& bullet)
{
    return bullet.getPosition().y < 0;
}
void Player::Event()
{
    sf::Vector2f player_position = this->hitbox.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hitbox.getPosition().x >= 0)
	this->velocity = {-1,0};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hitbox.getPosition().x + hitbox.getSize().x <= movement_range.x)
	this->velocity = {1,0};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hitbox.getPosition().y >= 0)
	this->velocity = {0,-1};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hitbox.getPosition().y + hitbox.getSize().y <= movement_range.y)
	this->velocity = {0,1};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
	this->velocity.x *=4;
	this->velocity.y *=4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
	sf::RectangleShape new_bullet;
	new_bullet.setSize(bullet_size);
	new_bullet.setFillColor(sf::Color::Red);
	new_bullet.setPosition({player_position.x+(hitbox.getSize().x/2)-new_bullet.getSize().x/2,player_position.y});
	bullet_list.push_back(new_bullet);
    }
}
void Player::Update()
{
    this->hitbox.setPosition({this->hitbox.getPosition() + this->velocity});
    this->velocity = {0,0};
    bullet_list.remove_if(is_hit);
    for(std::list<sf::RectangleShape>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++)
	it->setPosition({it->getPosition().x,it->getPosition().y-80});

}


