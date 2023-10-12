#include "Enemy.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
Enemy::Enemy()
{   
    this->hitbox.setFillColor(sf::Color::Red);
    this->hitbox.setSize({30,30});
    this->is_hit = false;
    this->bullet_size = {5,5};
    firing_cooldown = 1000;
}
void Enemy::SetMovementRange(sf::Vector2f range)
{
    this->movement_range = range;
}
void Enemy::SetVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
void Enemy::FireBullet(sf::Vector2f position)
{
    float time = firing_counter.getElapsedTime().asMilliseconds();
    if(time > firing_cooldown && !is_hit)
    {
	Bullet new_bullet;
	new_bullet.setSize(bullet_size);
	sf::Vector2f center={hitbox.getPosition().x+(hitbox.getSize().x/2)-new_bullet.getSize().x/2,hitbox.getPosition().y+(hitbox.getSize().y/2)-new_bullet.getSize().y/2};
	new_bullet.setFillColor(sf::Color::Magenta);
	new_bullet.setPosition(center);
	sf::Vector2f aim_direction = position - center;
	aim_direction = aim_direction / (float)std::sqrt(std::pow(aim_direction.x,2) + std::pow(aim_direction.y,2));
	float aim_offset = 0;
	if(rand()%100 > 50)
	    aim_offset = 0.05*(std::abs(this->velocity.x) + std::abs(this->velocity.y));
	else
	    aim_offset = -0.05*(std::abs(this->velocity.x) + std::abs(this->velocity.y));
	new_bullet.SetVelocity(aim_direction);
	bullet_list.push_back(new_bullet);
	firing_counter = sf::Clock();
    }
}
bool Enemy::IsBulletHit(const sf::Shape &object)
{
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
	if(object.getGlobalBounds().intersects(bullet->getGlobalBounds()))
	{
	    bullet->Hit();
	    return true;
	}
    return false;
}
sf::RectangleShape Enemy::GetHitbox()
{
    return hitbox;
}
bool Enemy::isbullethit(Bullet &bullet)
{
    return bullet.GetHitStatus() || bullet.getPosition().x < 0 || bullet.getPosition().x > movement_range.x || bullet.getPosition().y < 0 || bullet.getPosition().y > movement_range.y;
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
    bullet_list.remove_if([this](Bullet bullet){return isbullethit(bullet);});
    for(auto bullet=bullet_list.begin(); bullet!=bullet_list.end(); bullet++)
    {
	bullet->AddTime();
	bullet->move(bullet->GetVelocity()*3.f);
    }
}

