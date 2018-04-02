#define _CTR_SECURE_NO_WARNINGS

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
#include"Level.h"
#include"HighScore.h"

const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 840;
const int TILE_SIZE = 40;
const int PACMAN_SPEED = 5;
const int GHOST_SPEED = 4;
const int GHOST_ALARM_SPEED = 2;
const int WIN_SCORE = 189;
const int ALARM_TIME = 10;




//int main(int argv, char* argc[])
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{	
	srand(time(NULL));

// load SDL and textures
initializeSDL();
SDL_Window* window = createWindow("Pacman", WINDOW_WIDTH, WINDOW_HEIGHT);
SDL_Renderer* renderer = createRenderer(window);

int start_menu_choice = -1;	// (-1) - to open menu at first time
							// ( 0) - start game 							// ( 1) - exit
							// ( 2) - high scores
bool quit = false;
	int score = 0; 
	int current_time = 0;
	int level_menu_choice = 0;

	while (!quit)
	{
		// Strart menu
		// loading

		HighScore highscore(renderer, "high_score.txt");

		Menu menu("Textures/button.png", "Textures/button_allocated.png", "Textures/mainmenu_background.png", renderer, 3);
		SDL_Texture* mainmenu_background_texture = loadTexture("Textures/mainmenu_background.png", renderer);
		menu.set_button_location(0, 210, 350);
		menu.set_button_location(1, 210, 450);
		menu.set_button_location(2, 210, 550);
		menu.set_button_text(0, "New game");
		menu.set_button_text(1, "High Scores");
		menu.set_button_text(2, "Exit");
		//

		renderTexture(mainmenu_background_texture, renderer, 0, 0);

		bool escape = false;
		if (level_menu_choice == 0) start_menu_choice = menu.execute(escape);
		if (escape) start_menu_choice = 2;
		if (level_menu_choice == 1) start_menu_choice = 0;
		if (level_menu_choice == 2) start_menu_choice = 2;
		// Game
		if (start_menu_choice == 0)
		{
			int score = execute(renderer, PACMAN_SPEED, GHOST_SPEED, GHOST_ALARM_SPEED, ALARM_TIME, level_menu_choice);
			highscore.set_new(score);
		}

		if (start_menu_choice == 1)
		{
			highscore.build();
		}

		if (start_menu_choice == 2)
		{
			quit = true;
		}

	}


	return 0;
}
