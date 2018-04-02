#include "Point.h"



Point::Point(SDL_Texture* new_texture, SDL_Renderer* new_renderer, Map* new_map)
{
	texture = new_texture;
	renderer = new_renderer;
	map = new_map;

	location = new Location*[map->get_height()];
	for (int i = 0; i < map->get_height(); i++)
	{
		location[i] = new Location[map->get_width()];
	}

	for (int i = 0; i < map->get_height(); i++)
	{
		for (int j = 0; j < map->get_width(); j++)
		{
			location[i][j].x = j*map->get_tile_size();
			location[i][j].y = i*map->get_tile_size();
			location[i][j].enable = false;
		}
	}
}


Point::~Point()
{
	delete[] location;
}

void Point::fillLocation()
{
	for (int i = 0; i < map->get_height(); i++)
	{
		for (int j = 0; j < map->get_width(); j++)
		{
			if (map->get_walldest(i, j) == 0)location[i][j].enable= true;
		}
	}

}

void Point::build(SDL_Renderer* renderer)
{
	for (int i = 0; i < map->get_height(); i++)
	{
		for (int j = 0; j < map->get_width(); j++)
		{
			if (location[i][j].enable == true)
			renderTexture(texture, renderer, location[i][j].x, location[i][j].y);
		}
	}

}