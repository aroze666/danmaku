#ifndef __GAME__
#define __GAME__
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Raycaster.hpp"
#include "Scene.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <list>

class Game : public sf::Drawable {
public:
  Game(sf::RenderWindow &window);
  void Update();
  void GeneralEvent();
  void CollisionEvent();

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(scene, states);
    target.draw(player, states);
    target.draw(ray, states);
    int counter = 0;
    for (auto enemy = enemy_list.begin(); enemy != enemy_list.end(); enemy++) {
      counter++;
      target.draw(*enemy, states);
    }
  }
  Player player;
  Scene scene;
  RayCaster ray{70};
  sf::RenderWindow window;
  sf::Clock enemy_respawn_clock;
  int respawn_time;
  sf::Vector2f window_size;
  std::list<Enemy> enemy_list;
  std::list<Bullet> bullet_list;
  bool is_Collide(const sf::Shape &a, const sf::Shape &b);
  void create_Enemy();
};
#endif
