#pragma once

#include<iostream>
#include<Windows.h>

#include<SDL.h>
#include<SDL_image.h>

#include"Map.h"
#include"Game.h"
#include"Library.h"
#include"Standart.h"
#include"Points.h"
#include"BigPoints.h"
#include"Animations.h"


class Pacman
{
	
	SDL_Texture* texture;
	Animations* animation;
	Animations* die_animation;

	SDL_Renderer* renderer;

	Direction current_direction;
	Direction next_direction;
	Location start_location;
	int speed;
public:		
	Location location;

	Pacman(Animations* new_animation, Animations* new_die_animation, SDL_Renderer*, int, int, int);
	~Pacman();

	Direction get_direction() { return current_direction; }
	void set_direction(Direction direction) { current_direction = direction; next_direction = direction; }
	Location get_location() { return location; }

	void build();
	int update(Direction, Map&, Points*, BigPoints* big_point);
	
	void build_die();

	void gotoStartLocation();
};

