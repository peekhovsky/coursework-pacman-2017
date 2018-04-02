
#pragma once
#include<iostream>
#include<Windows.h>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"Library.h"

struct Button
{
	int x;
	int y;
	char* text;
	bool allocated;
};


class Menu
{
	SDL_Texture* button_texture;
	SDL_Texture* alloc_button_texture;
	SDL_Texture* background_texture;
	SDL_Renderer* renderer;
	Button* button;
	int button_amount;

public:
	Menu(std::string, std::string, std::string, SDL_Renderer*, int);
	~Menu();

	int execute();
	int execute(bool& escape);
	void build();

	void	set_button_location(int, int, int);
	void	set_button_text(int, char*);
	int		get_button_amount() { return button_amount; }
	void	change_alloc_button(int num);


	
};

