#ifndef __PLAYER__
#define __PLAYER__

#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <random>
class Player : public sf::Drawable {
public:
  Player();
  void SetHitboxSize(sf::Vector2f size);
  void SetBulletSize(sf::Vector2f size);
  void SetPosition(sf::Vector2f position);
  void SetVelocity(sf::Vector2f velocity);
  void SetWindow(sf::RenderWindow *window);
  void SetMovementRange(sf::Vector2f range);
  sf::Vector2f GetPlayerAimVector();
  sf::Vector2f GetPlayerCenter();
  sf::Vector2f GetVelocity();
  sf::RectangleShape GetHitbox();
  bool IsBulletHit(const sf::Shape &object);
  void Update();
  void Event();

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(crosshair, states);
    target.draw(hitbox, states);
    for (auto it = bullet_list.begin(); it != bullet_list.end(); it++) {
      target.draw(*it, states);
    }
  }

  bool isbullethit(Bullet &bullet);
  sf::Vector2f terminal_velocity;
  sf::RectangleShape hitbox;
  sf::Vector2f bullet_size;
  std::list<Bullet> bullet_list;
  sf::Vector2f initial_velocity;
  sf::Vector2f velocity;
  sf::Vector2f movement_range;
  sf::RenderWindow *window;
  sf::CircleShape crosshair;
  float speed_factor;
  float firing_cooldown;
  sf::Clock firing_counter;
  bool moving;
};

#endif
