#include "Player.hpp"
#include <cmath>
Player::Player()
{
	this->moving = false;
	this->terminal_velocity = {8, 8};
	this->hitbox.setSize({30, 30});
	this->initial_velocity = {2, 2};
	this->velocity = initial_velocity;
	this->bullet_size = {5, 5};
	this->hitbox.setFillColor(sf::Color::Blue);
	this->firing_cooldown = 100;
	speed_factor = 1;
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
	for (auto bullet = bullet_list.begin(); bullet != bullet_list.end(); bullet++)
		if (object.getGlobalBounds().intersects(bullet->getGlobalBounds()))
		{
			bullet->Hit();
			return true;
		}
	return false;
}

void Player::Event()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moving = true;
		if (this->velocity.x <= terminal_velocity.x)
			this->velocity.x += std::abs(initial_velocity.x);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moving = true;
		if (this->velocity.x >= -terminal_velocity.x)
			this->velocity.x -= std::abs(initial_velocity.x);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moving = true;
		if (this->velocity.y >= -terminal_velocity.y)
			this->velocity.y -= std::abs(initial_velocity.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moving = true;
		if (this->velocity.y <= terminal_velocity.y)
			this->velocity.y += std::abs(initial_velocity.y);
	}
	speed_factor = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		speed_factor = 0.25;

	if (velocity.x > 0)
		velocity.x -= 0.5;
	if (velocity.x < 0)
		velocity.x += 0.5;
	if (velocity.y > 0)
		velocity.y -= 0.5;
	if (velocity.y < 0)
		velocity.y += 0.5;
	if (velocity.x == 0 && velocity.y == 0)
		moving = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float time = firing_counter.getElapsedTime().asMilliseconds();
		if (time > firing_cooldown)
		{
			Bullet new_bullet;
			new_bullet.setSize(bullet_size);
			sf::Vector2f center = {hitbox.getPosition().x + (hitbox.getSize().x / 2) - new_bullet.getSize().x / 2, hitbox.getPosition().y + (hitbox.getSize().y / 2) - new_bullet.getSize().y / 2};
			new_bullet.setFillColor(sf::Color::Cyan);
			new_bullet.setPosition(center);
			sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window));
			sf::Vector2f aim_direction = mouse_pos - center;
			aim_direction = aim_direction / (float)std::sqrt(std::pow(aim_direction.x, 2) + std::pow(aim_direction.y, 2));
			float aim_offset = 0;
			if (rand() % 100 > 50)
				aim_offset = speed_factor * 0.05 * (std::abs(this->velocity.x) + std::abs(this->velocity.y));
			else
				aim_offset = speed_factor * -0.05 * (std::abs(this->velocity.x) + std::abs(this->velocity.y));
			if (moving)
			{
				if (aim_direction.x < 0 && aim_direction.y < 0) // inaccurate
					new_bullet.SetVelocity({aim_direction.x + aim_offset, aim_direction.y - aim_offset});
				else if (aim_direction.x > 0 && aim_direction.y > 0) // inaccurate
					new_bullet.SetVelocity({aim_direction.x - aim_offset, aim_direction.y + aim_offset});
				else // inaccurate
					new_bullet.SetVelocity({aim_direction.x + aim_offset, aim_direction.y + aim_offset});
			}
			else // accurate
				new_bullet.SetVelocity(aim_direction);

			bullet_list.push_back(new_bullet);

			// recoil
			//  moving = true;
			//  this->velocity += -aim_direction*2.f;
			//  if(std::abs(this->velocity.x) >= terminal_velocity.x)
			//  this->velocity.x -= -aim_direction.x*2.f;
			//  if(std::abs(this->velocity.y) >= terminal_velocity.y)
			//  this->velocity.y -= -aim_direction.y*2.f;
			firing_counter = sf::Clock();
		}
	}
	if (moving)
		this->hitbox.setPosition(this->hitbox.getPosition() + this->velocity * speed_factor);
	if (hitbox.getPosition().x <= 0)
		SetPosition({0, this->hitbox.getPosition().y});
	if (hitbox.getPosition().x >= movement_range.x - hitbox.getSize().x)
		SetPosition({movement_range.x - this->hitbox.getSize().x, this->hitbox.getPosition().y});
	if (hitbox.getPosition().y <= 0)
		SetPosition({this->hitbox.getPosition().x, 0});
	if (hitbox.getPosition().y >= movement_range.y - hitbox.getSize().y)
		SetPosition({this->hitbox.getPosition().x, movement_range.y - this->hitbox.getSize().y});
}
bool Player::isbullethit(Bullet &bullet)
{
	return bullet.GetHitStatus() || bullet.getPosition().x < 0 || bullet.getPosition().x > movement_range.x || bullet.getPosition().y < 0 || bullet.getPosition().y > movement_range.y;
}
void Player::Update()
{
	bullet_list.remove_if([this](Bullet bullet)
						  { return isbullethit(bullet); });
	for (auto bullet = bullet_list.begin(); bullet != bullet_list.end(); bullet++)
	{
		bullet->AddTime();
		bullet->move(bullet->GetVelocity() * bullet->GetTime() * 2.f);
	}
}
