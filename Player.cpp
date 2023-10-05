#include "Player.hpp"
Player::Player()
{
    this->hitbox.setSize({30,30});
    this->initial_velocity = {4,4};
    this->bullet_size = {5,5};
}
void Player::SetMovementRange(sf::Vector2f range)
{
    this->movement_range = range;
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
bool Player::IsBulletHit(const sf::Shape &object)
{
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
	if(object.getGlobalBounds().intersects(bullet->getGlobalBounds()))
	{
	    bullet->Hit();
	    return true;
	}
    return false;
}
void Player::CreateBullet()
{
    Bullet new_bullet;
    new_bullet.setSize(bullet_size);
    new_bullet.setFillColor(sf::Color::Red);
    new_bullet.setPosition({hitbox.getPosition().x+(hitbox.getSize().x/2)-new_bullet.getSize().x/2,hitbox.getPosition().y});
    bullet_list.push_back(new_bullet);
}

void Player::Event()
{
    bool moving = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
	moving = true;
	this->velocity.x = this->initial_velocity.x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
	moving = true;
	this->velocity.x = -this->initial_velocity.x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
	moving = true;
	this->velocity.y = -this->initial_velocity.y;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
	moving = true;
	this->velocity.y = this->initial_velocity.y;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
	this->velocity.x /= 2;
	this->velocity.y /= 2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
	CreateBullet();
	this->velocity.x /= 2;
	this->velocity.y /= 2;
    }
    if(moving)
    {
	this->hitbox.setPosition({this->hitbox.getPosition() + this->velocity});
	this->velocity.x = 0;
	this->velocity.y = 0;
	moving = false;
    }
    if(hitbox.getPosition().x <= 0)
	SetPosition({0,this->hitbox.getPosition().y});
    if(hitbox.getPosition().x >= movement_range.x - hitbox.getSize().x)
	SetPosition({movement_range.x - this->hitbox.getSize().x, this->hitbox.getPosition().y});
    if(hitbox.getPosition().y <= 0)
	SetPosition({this->hitbox.getPosition().x, 0});
    if(hitbox.getPosition().y >= movement_range.y - hitbox.getSize().y)
	SetPosition({this->hitbox.getPosition().x, movement_range.y - this->hitbox.getSize().y});
 }
bool bulletHit(Bullet &bullet)
{
    return bullet.GetHitStatus() || bullet.getPosition().y < 0;
}
void Player::Update()
{
    bullet_list.remove_if(bulletHit);
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
	bullet->setPosition({bullet->getPosition().x,bullet->getPosition().y-40});
}


