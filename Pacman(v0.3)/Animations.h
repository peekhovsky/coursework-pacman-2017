#pragma once

#include<iostream>
#include<cmath>

#include<SDL.h>
#include<SDL_image.h>

#include"Window.h"
#include"Standart.h"
#include"Game.h"

class Animations
{
	SDL_Renderer* renderer;
	SDL_Texture** texture_left;
	SDL_Texture** texture_right;
	SDL_Texture** texture_up;
	SDL_Texture** texture_down;

	int size;
	int current_texture;
	int pause;
	int current;

public:
	
	Animations(SDL_Renderer* new_renderer, int new_size, int new_pause);
	~Animations();

	SDL_Texture* get_texture(Direction direction);
	void set_texture(std::string file_location, Direction direction, int number);
	int get_size() { return size; }
	SDL_Texture* get_texture();
	// game_settings
	void  setPacmanTextures();
	void  setGhost1Textures();
	void  setGhost2Textures();
	void  setGhost3Textures();
	void  setGhost4Textures();
	void setPacmanDieTextures();
	void setGhostAlarmEndTextures();

	void reload() { current_texture = 0; }
	void build(int sleep, int x, int y);
};

