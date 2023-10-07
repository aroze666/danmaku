#include "Scene.hpp"

Scene::Scene()
{
    int x=8,y=8;
    int map[64] = 
    {
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
    };
    int counter = 0;
    for(int i=0; i<8; i++)
    {
	for(int j=0; j<y;j++)
	{
	    Grid new_grid;
	    if(map[counter]==0)
	    {
		new_grid.setFillColor(sf::Color::Black);
	    }else {
		new_grid.wall = true;
		new_grid.setFillColor(sf::Color::White);
	    }
	    new_grid.setPosition({j*64.f, i*64.f});
	    new_grid.setSize({63,63});
	    grids[i][j] = new_grid;
	    counter ++;
	}
    }
}
Scene::Scene(int *map)
{

}

void Scene::Update()
{
    
}
