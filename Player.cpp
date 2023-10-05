#include "Player.hpp"
#include <cmath>
Player::Player()
{
    this->moving = false;
    this->terminal_velocity = {10,10};
    this->hitbox.setSize({30,30});
    this->initial_velocity = {1,1};
    this->velocity = initial_velocity;
    this->bullet_size = {5,5};
    this->hitbox.setFillColor(sf::Color::Blue);
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

void Player::Event()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
	moving = true;
	if(this->velocity.x <= terminal_velocity.x)
	    this->velocity.x += this->initial_velocity.x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
	moving = true;
	if(this->velocity.x >= -terminal_velocity.x)
	    this->velocity.x += -this->initial_velocity.x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
	moving = true;
	if(this->velocity.y >= -terminal_velocity.y)
	    this->velocity.y += -this->initial_velocity.y;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
	moving = true;
	if(this->velocity.y <= terminal_velocity.y)
	    this->velocity.y += this->initial_velocity.y;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
	moving = true;
	Bullet new_bullet;
	new_bullet.setSize(bullet_size);
	new_bullet.setFillColor(sf::Color::Cyan);
	new_bullet.setPosition({hitbox.getPosition().x+(hitbox.getSize().x/2)-new_bullet.getSize().x/2,hitbox.getPosition().y+(hitbox.getSize().y/2)-new_bullet.getSize().y/2});
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window));
	sf::Vector2f aim_direction = mouse_pos - hitbox.getPosition();
	aim_direction = aim_direction / (float)std::sqrt(std::pow(aim_direction.x,2) + std::pow(aim_direction.y,2));
	new_bullet.SetVelocity(aim_direction);
	bullet_list.push_back(new_bullet);
	this->velocity += -aim_direction*2.f;
	if(std::abs(this->velocity.x) >= terminal_velocity.x)
	    this->velocity.x -= -aim_direction.x*2.f;
	if(std::abs(this->velocity.y) >= terminal_velocity.y)
	    this->velocity.y -= -aim_direction.y*2.f;
    }
    if(moving)
    {
	this->hitbox.setPosition({this->hitbox.getPosition() + this->velocity});
    }
    if(std::floor(this->velocity.x) > 0)
	this->velocity.x-=0.1;
    if(std::ceil(this->velocity.x) < 0)
	this->velocity.x+=0.1;
    if(std::floor(this->velocity.y) > 0)
	this->velocity.y-=0.1;
    if(std::ceil(this->velocity.y) < 0)
	this->velocity.y+=0.1;
    if((std::floor(this->velocity.x) == 0 || std::ceil(this->velocity.x) == 0 ) && (std::floor(this->velocity.y) == 0 || std::ceil(this->velocity.y) == 0))
	moving = false;
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
    {
	bullet->AddTime();
	bullet->move(bullet->GetVelocity()*bullet->GetTime());

    }
}

