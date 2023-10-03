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
bool touch_border(const sf::RectangleShape& bullet)
{
    return bullet.getPosition().y < 0;
}
bool Player::IsBulletHit(const sf::Shape &object)
{
    bool hit = false;
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
	if(object.getGlobalBounds().intersects(bullet->getGlobalBounds()))
	    hit  = true;
    return hit;
}
void Player::Event()
{
    sf::Vector2f player_position = this->hitbox.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	this->velocity = {-this->initial_velocity.x, 0};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	this->velocity = {this->initial_velocity.x, 0};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	this->velocity = {0,-this->initial_velocity.y};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	this->velocity = {0,this->initial_velocity.y};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
	this->velocity.x /= 2;
	this->velocity.y /= 2;
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
    if(hitbox.getPosition().x <= 0)
	SetPosition({0,this->hitbox.getPosition().y});
    if(hitbox.getPosition().x >= movement_range.x - hitbox.getSize().x)
	SetPosition({movement_range.x - this->hitbox.getSize().x, this->hitbox.getPosition().y});
    if(hitbox.getPosition().y <= 0)
	SetPosition({this->hitbox.getPosition().x, 0});
    if(hitbox.getPosition().y >= movement_range.y - hitbox.getSize().y)
	SetPosition({this->hitbox.getPosition().x, movement_range.y - this->hitbox.getSize().y});

    this->velocity = {0,0};
    bullet_list.remove_if(touch_border);
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
	bullet->setPosition({bullet->getPosition().x,bullet->getPosition().y-40});
}


