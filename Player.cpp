#include "Player.hpp"
Player::Player(sf::Vector2f hitbox_size, sf::Vector2f bullet_size) : HITBOX_SIZE(hitbox_size), BULLET_SIZE(bullet_size)
{
    this->hitbox.setPosition(0,0);
    this->hitbox.setSize(HITBOX_SIZE);
    this->hitbox.setFillColor(sf::Color::White);
}
bool is_hit(const sf::RectangleShape& bullet)
{
    return bullet.getPosition().y < 0;
}
void Player::Update()
{
    sf::Vector2f player_position = this->hitbox.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	this->hitbox.setPosition(player_position.x-10, player_position.y);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	this->hitbox.setPosition(player_position.x+10, player_position.y);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	this->hitbox.setPosition(player_position.x, player_position.y-10);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	this->hitbox.setPosition(player_position.x, player_position.y+10);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
	sf::RectangleShape new_bullet;
	new_bullet.setSize(BULLET_SIZE);
	new_bullet.setFillColor(sf::Color::Red);
	new_bullet.setPosition({player_position.x+(hitbox.getSize().x/2)-new_bullet.getSize().x/2,player_position.y});
	bullet_list.push_back(new_bullet);
    }
    bullet_list.remove_if(is_hit);
    for(std::list<sf::RectangleShape>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++)
	it->setPosition({it->getPosition().x,it->getPosition().y-50});

}


