#pragma once

#include<iostream>
#include<Windows.h>

#include<SDL.h>
#include<SDL_image.h>

#include"Game.h"
#include"Library.h"
#include"Standart.h"
#include"Map.h"


class BigPoints
{
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Map* map;
	Location** location;

public:

	BigPoints(std::string, SDL_Renderer*, Map*);
	~BigPoints();

	bool get_enable(int i, int j)
	{
		return location[i][j].enable;
	}

	void build();
	bool eat(int, int); // returns true if point exist and then deactivate it

	void reload();
};

