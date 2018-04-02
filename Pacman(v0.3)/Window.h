#pragma once

#include<iostream>
#include<Windows.h>
#include<ctime>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


class Window
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
	std::string name;

public:
	Window(int new_height, int new_width, std::string new_name);
	~Window();

	void initializeLibrary();
	void createWindow();
	void createRenderer();
	void renderTexture(SDL_Texture* texture, int x, int y);
	SDL_Texture* loadTexture(std::string file);
	SDL_Texture* textToTexture(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
	
	void presentWindow();

	SDL_Texture* TextToTexture(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
	void buildScore(int coins, int x, int y);
	void buildTime(int current_time, int x, int y);
	void buildHeart(SDL_Texture* texture, int quant, int x, int y);

	int get_width() { return width; }
	int get_height() { return height; }
};