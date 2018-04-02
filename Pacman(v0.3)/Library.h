#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<ctime>


struct Animation
{
	SDL_Texture** texture;
	unsigned size;
};




// initialize

void initializeSDL();

// quit

void quitSDL();

// window creation 

SDL_Window* createWindow(std::string name, int x, int y, int w, int h, Uint32 flags);
SDL_Window* createWindow(std::string name, int w, int h);


// renderer creation

SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags);
SDL_Renderer* createRenderer(SDL_Window* window);

// loading

SDL_Texture* LoadBMP(std::string file, SDL_Renderer* renderer);
SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer);


// rendering
void renderTexture(std::string file_location, SDL_Renderer *renderer, int x, int y);
void renderTexture(SDL_Texture* texture, SDL_Renderer *renderer, int x, int y);
void renderTexture(SDL_Texture *texture, SDL_Renderer* renderer, int x, int y, int w, int h);
void renderTexture(SDL_Texture* texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip);


SDL_Texture* TextToTexture(SDL_Renderer *, const std::string &, const std::string &, SDL_Color , int );

void buildScore(SDL_Renderer *, int, int, int);
void buildTime(SDL_Renderer *renderer, int current_time, int x, int y);
void buildHeart(SDL_Renderer *renderer, SDL_Texture* texture, int quant, int x, int y);
void buildText(SDL_Renderer *renderer, SDL_Color text_color, std::string str, int x, int y, int size);