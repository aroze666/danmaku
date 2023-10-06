#include "Scene.hpp"

Scene::Scene()
{
    int x=8,y=8;
    int map[8][8] = 
    {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    };
    for(int i=0; i<x; i++)
	for(int j=0; j<y;j++)
	{

	    Grid new_grid;
	    if(map[i][j]==0)
	    {
		new_grid.setFillColor(sf::Color::Black);
	    }else {
		new_grid.wall = true;
		new_grid.setFillColor(sf::Color::White);
	    }
	    new_grid.setPosition({i*64.f, j*64.f});
	    new_grid.setSize({63,63});
	    this->grids.push_back(new_grid);
	}
}
Scene::Scene(int *map)
{

}

void Scene::Update()
{
    
}
