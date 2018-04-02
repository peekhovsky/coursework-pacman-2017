#pragma once

#include<iostream>
#include<fstream>
#include<Windows.h>
#include<ctime>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"Window.h"
#include"Game.h"
#include"Menu.h"
#include"Map.h"
#include"Library.h"
#include"Standart.h"
#include"Pacman.h"
#include"Ghost.h"
#include"Points.h"
#include"BigPoints.h"
#include"Animations.h"

class Level
{
	Pacman pacman;
	Ghost ghost1;
	Ghost ghost2;
	Ghost ghost3;
	Ghost ghost4;
	Animations pacman_animation;
	Animations ghost1_animation;
	Animations ghost2_animation;
	Animations ghost3_animation;
	Animations ghost4_animation;

};
int execute(SDL_Renderer* renderer, int pacman_speed, int ghost_speed, int ghost_alarm_speed, int alarm_time, int& menu_choice);