#pragma once


#include<iostream>


#include<SDL.h>
#include<SDL_image.h>

#include"Library.h"
#include"Standart.h"
#include"Map.h"
#include"Pacman.h"

class Point
{

	SDL_Texture* texture;
	SDL_Renderer* renderer;
	Map* map;

public:
	Location** location;
	Point(SDL_Texture*, SDL_Renderer*, Map*);
	~Point();

	void fillLocation();
	void build(SDL_Renderer*);
};
