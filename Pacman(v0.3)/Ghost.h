#pragma once

#include<iostream>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>

#include"Map.h"
#include"Pacman.h"
#include"Game.h"
#include"Library.h"
#include"Standart.h"
#include"Points.h"
#include"Animations.h"


class Ghost
{
	Animations* animation;
	Animations* alarm_end_animation;
	SDL_Texture* texture;
	SDL_Texture* alarm_texture;
	SDL_Texture* return_texture;
	SDL_Renderer* renderer;

	Direction current_direction;



	bool alarm;
	bool alarm_end;
	bool return_;
	int speed;

public:
	Ghost();
	~Ghost();
	Ghost(Animations*, std::string, Animations*, std::string, SDL_Renderer*, int, int, int);

	Location* location;
	Location* start_location;

	void viceversaDirection();
	Direction get_direction() { return current_direction; }
	Location get_location() { return *location; }

	void set_alarm(bool new_alarm) { alarm = new_alarm; }
	void set_alarm_end(bool new_alarm) { alarm_end = new_alarm; }
	void set_return(bool new_return) { return_ = new_return; }
	bool get_alarm() { return alarm; }
	bool get_return() { return return_; }



	void update(Map* map, Pacman* pacman, int randomize_num);

	void build();

	void gotoStartLocation();
	
};

