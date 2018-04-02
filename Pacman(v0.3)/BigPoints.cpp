#include "BigPoints.h"



BigPoints::BigPoints(std::string texture_location, SDL_Renderer* new_renderer, Map* new_map)
{
	texture = loadTexture(texture_location.c_str(), new_renderer);
	renderer = new_renderer;
	map = new_map;

	location = new Location*[map->get_height()];
	for (int i = 0; i < map->get_height(); i++)
	{
		location[i] = new Location[map->get_width()];
	}

	for (int i = 0; i < map->get_height(); i++)
	{
		for (int j = 1; j < map->get_width() - 1; j++)
		{
			location[i][j].x = j*(map->get_tile_size());
			location[i][j].y = i*(map->get_tile_size());

			if (map->get_walldest(i, j) == 4) location[i][j].enable = true;
		}
	}
}

void BigPoints::reload()
{
	for (int i = 0; i < map->get_height(); i++)
	{
		for (int j = 1; j < map->get_width() - 1; j++)
		{
			location[i][j].x = j*(map->get_tile_size());
			location[i][j].y = i*(map->get_tile_size());

			if (map->get_walldest(i, j) == 4) location[i][j].enable = true;
		}
	}
}


BigPoints::~BigPoints()
{

	delete[] location;
}


void BigPoints::build()
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

bool BigPoints::eat(int i, int j)
{
	if (location[i][j].enable == true)
	{
		location[i][j].enable = false;
		return true;
	}
	else return false;
}