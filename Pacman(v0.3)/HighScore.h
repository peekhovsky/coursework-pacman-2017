#pragma once
#include<fstream>
#include<iostream> 
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


#include"Library.h"
#include"Game.h"
#include"Menu.h"


#define SCORE_QUANT 10

class HighScore
{
	int data[SCORE_QUANT];
	SDL_Renderer* renderer;
	string file_loc;
public:

	HighScore();
	HighScore(SDL_Renderer* new_renderer, string new_file_loc);
	~HighScore();

	void read();
	void record();

	void set_new(int new_score);
	void build();

};

