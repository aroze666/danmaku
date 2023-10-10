#ifndef __SCENE__
#define __SCENE__
#include <SFML/Graphics.hpp>
#include <vector>
struct Grid : public sf::RectangleShape {
  bool wall = false;
};
class Scene : public sf::Drawable {
public:
  Scene();
  Scene(int *map);
  void Update();
  sf::Vector2f scene_size = {512, 512};
  Grid grids[8][8];

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        target.draw(grids[i][j], states);
  }
};

#endif
