#ifndef __ENEMY__
#define __ENEMY__

#include "Bullet.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
class Enemy : public sf::Drawable {
public:
  Enemy();
  void Update();
  void Event();
  void SetMovementRange(sf::Vector2f range);
  void SetPosition(sf::Vector2f position) {
    this->hitbox.setPosition(position);
  }
  void SetVelocity(sf::Vector2f velocity);
  void SetHit(bool is_hit);
  sf::Vector2f GetVelcoity();
  sf::RectangleShape GetHitbox();
  bool isbullethit(Bullet &bullet);
  bool IsBulletHit(const sf::Shape &object);
  void FireBullet(sf::Vector2f position);
  bool IsHit() { return is_hit; }
  bool BulletExist() {
    int counter = 0;
    for (auto bullet = bullet_list.begin(); bullet != bullet_list.end();
         bullet++) {
      counter++;
    }
    return counter > 0;
  }

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!is_hit)
      target.draw(hitbox, states);
    for (auto bullet = bullet_list.begin(); bullet != bullet_list.end();
         bullet++)
      target.draw(*bullet, states);
  }
  bool is_hit;
  sf::RectangleShape hitbox;
  sf::Vector2f bullet_size;
  sf::Vector2f velocity;
  sf::Vector2f movement_range;
  float firing_cooldown;
  sf::Clock firing_counter;
  std::list<Bullet> bullet_list;
};

#endif
