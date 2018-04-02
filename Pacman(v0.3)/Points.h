#pragma once

#include<iostream>
#include<Windows.h>

#include<SDL.h>
#include<SDL_image.h>

#include"Game.h"
#include"Library.h"
#include"Standart.h"
#include"Map.h"


class Points
{
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Map* map;
	Location** location;
	int quantity;
public:

	Points(std::string, SDL_Renderer*, Map*);
	~Points();

	bool get_enable(int i, int j) { return location[i][j].enable; }
	int get_quantity() { return quantity; }

	void build();
	bool eat(int, int); // returns true if point exist and then deactivate it
	void reload();


};

