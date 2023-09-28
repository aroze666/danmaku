#include "Player.hpp"
Player::Player(float l_1, float w_1, float l_2, float w_2) : PLAYER_LENGTH(l_1), PLAYER_WIDTH(w_1), BULLET_LENGTH(l_2), BULLET_WIDTH(w_2)
{
    this->hit_box.setPosition(0,0);
    this->hit_box.setSize({PLAYER_LENGTH, PLAYER_WIDTH});
    this->hit_box.setFillColor(sf::Color::White);
}

void Player::PlayerEvent()
{
    sf::Vector2f player_position = this->hit_box.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	this->hit_box.setPosition(player_position.x-10, player_position.y);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	this->hit_box.setPosition(player_position.x+10, player_position.y);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	this->hit_box.setPosition(player_position.x, player_position.y-10);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	this->hit_box.setPosition(player_position.x, player_position.y+10);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
	sf::RectangleShape new_bullet;
	new_bullet.setSize({BULLET_LENGTH, BULLET_WIDTH});
	new_bullet.setFillColor(sf::Color::Red);
	new_bullet.setPosition({player_position.x+(hit_box.getSize().x/2)-new_bullet.getSize().x/2,player_position.y});
	bullet_list.push_back(new_bullet);
    }
}

//helper function
bool is_hit(const sf::RectangleShape& bullet)
{
    return bullet.getPosition().y < 0;
}

void Player::PlayerUpdate()
{
    bullet_list.remove_if(is_hit);
    for(std::list<sf::RectangleShape>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++)
	it->setPosition({it->getPosition().x,it->getPosition().y-50});
}

