#pragma once
#define _CTR_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Map.h"

enum Direction
{
	ZERO = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4,
	RETURN = 5
};

struct PossibleDirections
{
	bool right;
	bool left;
	bool up;
	bool down;
	int count;
};




int waitDirectionKey(Direction& direction);

PossibleDirections* findPossibleDirections(Map* , int, int );

PossibleDirections* new_findPossibleDirections(Map* map, int y, int x);

bool checkCrossroad(Location* location, Map* map);

Direction randomDirection(PossibleDirections* possible_directions, Direction current_direction, int randomize_num);

Direction pursueDirection(Location* location, PossibleDirections* possible_directions, Direction current_direction, Location* bot_location, Direction bot_direction, int randomize_num);

Direction targetDirection(Location* location, PossibleDirections* possible_directions, Direction current_direction, Location* target_location);

void changeLocation(Location* location, Direction current_direction, int speed);

bool checkShelter(Map* map, int i, int j);