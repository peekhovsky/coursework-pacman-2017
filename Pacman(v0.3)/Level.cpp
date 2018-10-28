#include"Level.h"






void load()
{
	;

}

int execute(SDL_Renderer* renderer, int pacman_speed, int ghost_speed, int ghost_alarm_speed, int alarm_time, int& menu_choice)
{
	// loading objects 
	Map	map1("Textures/wall.png", "Textures/background.png", renderer, "Maps/map1.txt"); map1.show();
	Points points("Textures/point.png", renderer, &map1);
	BigPoints big_points("Textures/big_point.png", renderer, &map1);

	Animations pacman_animation(renderer, 4, 3); pacman_animation.setPacmanTextures();
	Animations pacman_die_animation(renderer, 6, 15); pacman_die_animation.setPacmanDieTextures();
	Animations ghost1_animation(renderer, 1, 10); ghost1_animation.setGhost1Textures();
	Animations ghost2_animation(renderer, 1, 10); ghost2_animation.setGhost2Textures();
	Animations ghost3_animation(renderer, 1, 10); ghost3_animation.setGhost3Textures();
	Animations ghost4_animation(renderer, 1, 10); ghost4_animation.setGhost4Textures();
	Animations ghost_alarm_end_animation(renderer, 2, 20); ghost_alarm_end_animation.setGhostAlarmEndTextures();

	Pacman pacman(&pacman_animation, &pacman_die_animation, renderer, 10 * map1.get_tile_size(), 15 * map1.get_tile_size(), pacman_speed);
	Ghost ghost1(&ghost1_animation, "Textures/ghost_alarm.png", &ghost_alarm_end_animation, "Textures/ghost_return.png", renderer, 10 * map1.get_tile_size(), 8 * map1.get_tile_size(), ghost_speed);
	Ghost ghost2(&ghost2_animation, "Textures/ghost_alarm.png", &ghost_alarm_end_animation, "Textures/ghost_return.png", renderer, 10 * map1.get_tile_size(), 9 * map1.get_tile_size(), ghost_speed);
	Ghost ghost3(&ghost3_animation, "Textures/ghost_alarm.png", &ghost_alarm_end_animation, "Textures/ghost_return.png", renderer, 11 * map1.get_tile_size(), 9 * map1.get_tile_size(), ghost_speed);
	Ghost ghost4(&ghost4_animation, "Textures/ghost_alarm.png", &ghost_alarm_end_animation, "Textures/ghost_return.png", renderer,  9 * map1.get_tile_size(), 9 * map1.get_tile_size(), ghost_speed);
	
	SDL_Texture* heart_texture = loadTexture("Textures/heart.png", renderer);
	SDL_Texture* background_texture = loadTexture("Textures/background.png", renderer);


	// settings
	Direction direction = ZERO;
	int game_choice = 0; // 0 - nothing, 1 - game_over, 2 - win, 3 - exit 
	int score = 0;
	int current_time = 0;
	int start_alarm_time = 0;
	int current_alarm_time = 0;
	int start_time = clock();
	bool ghost_alarm = false;
	bool new_game = true;
	int health_points = 3;
	int pause = 0;
	int die_pacman = 0;

	while (game_choice == 0)
	{

		if (!pause && !new_game)
		{
		// read a key
		if (waitDirectionKey(direction)) game_choice = 3; // if user presses ESC pause performs (waitDirectionKey retuns 3 if ESC was pressed)


		current_time = clock() - start_time;				// time 
		current_alarm_time = clock() - start_alarm_time;


		if (current_alarm_time > alarm_time * 1000)
		{
			ghost1.set_alarm(false);
			ghost2.set_alarm(false);
			ghost3.set_alarm(false);
			ghost4.set_alarm(false);
			ghost_alarm = false;

			ghost1.set_alarm_end(false);
			ghost2.set_alarm_end(false);
			ghost3.set_alarm_end(false);
			ghost4.set_alarm_end(false);

		}
		else if (current_alarm_time > alarm_time * 700)
		{
			if (ghost1.get_alarm()) ghost1.set_alarm_end(true);
			if (ghost2.get_alarm()) ghost2.set_alarm_end(true);
			if (ghost3.get_alarm()) ghost3.set_alarm_end(true);
			if (ghost4.get_alarm()) ghost4.set_alarm_end(true);
		}

		// update

		
		// update pacman location and score
		
		int coin = pacman.update(direction, map1, &points, &big_points); // returns "1' if pacman catches default point, "3" - if alarm point
		

			 // if pacman eats big point 															
		if (coin == 11)
		{
			ghost_alarm = true;

			if (!ghost1.get_return()) { ghost1.set_alarm(true); }
			if (!ghost2.get_return()) { ghost2.set_alarm(true); }
			if (!ghost3.get_return()) { ghost3.set_alarm(true); }
			if (!ghost4.get_return()) { ghost4.set_alarm(true); }

			ghost1.set_alarm_end(false);
			ghost2.set_alarm_end(false);
			ghost3.set_alarm_end(false);
			ghost4.set_alarm_end(false);

			ghost1.viceversaDirection();
			ghost2.viceversaDirection();
			ghost3.viceversaDirection();
			ghost4.viceversaDirection();
			start_alarm_time = clock();
		}
		score += coin;


		
			// update ghost location
			ghost1.update(&map1, &pacman, clock());
			ghost2.update(&map1, &pacman, clock());
			ghost3.update(&map1, &pacman, clock());
			ghost4.update(&map1, &pacman, clock());




			if (ghost_alarm)
			{
				if (pacman.get_location() >> ghost1.get_location() && ghost1.get_alarm())
				{
					ghost1.set_return(true);
					ghost1.set_alarm(false);
					ghost1.set_alarm_end(false);
					score += 10;
				}
				if (pacman.get_location() >> ghost2.get_location() && ghost2.get_alarm())
				{
					ghost2.set_return(true);
					ghost2.set_alarm(false);
					ghost2.set_alarm_end(false);
					score += 10;
				}
				if (pacman.get_location() >> ghost3.get_location() && ghost3.get_alarm())
				{
					ghost3.set_return(true);
					ghost3.set_alarm(false);
					ghost3.set_alarm_end(false);
					score += 10;
				}
				if (pacman.get_location() >> ghost4.get_location() && ghost4.get_alarm())
				{
					ghost4.set_return(true);
					ghost4.set_alarm(false);
					ghost4.set_alarm_end(false);
					score += 10;
				}
			}


			// check game over
			if ((pacman.get_location() >> ghost1.get_location() && !ghost1.get_alarm() && !ghost1.get_return())
				|| (pacman.get_location() >> ghost2.get_location() && !ghost2.get_alarm() && !ghost2.get_return())
				|| (pacman.get_location() >> ghost3.get_location() && !ghost3.get_alarm() && !ghost3.get_return())
				|| (pacman.get_location() >> ghost4.get_location() && !ghost4.get_alarm() && !ghost4.get_return()))
			{
				health_points--;
				if (health_points == -1) game_choice = 1;
				
				pause = die_pacman = 100;
				
			
			}



			// check win
			if (!points.get_quantity()) game_choice = 2;


		}
		
		// build		
		map1.build();
		points.build();
		big_points.build();
		ghost1.build();
		ghost2.build();
		ghost3.build();
		ghost4.build();

		if (die_pacman)
		{
			pacman.build_die();
		}
		else
		{
			pacman.build();
		}
		

		buildScore(renderer, score, map1.get_tile_size() + 30, 0);
		buildTime(renderer, current_time, map1.get_tile_size() * 13, 0);
		buildHeart(renderer, heart_texture, health_points, map1.get_tile_size() * 7, 0);
		SDL_Color logo_color = { 255, 204, 102 }; //yellow
		buildText(renderer, logo_color, "Pekhovsky", 675, 811, 16);

		// update screen
		SDL_RenderPresent(renderer);

		if(pause != 0) pause--;
		if (die_pacman != 0)
		{
			die_pacman--;
			if (die_pacman == 0)
			{
				ghost1.gotoStartLocation();
				ghost2.gotoStartLocation();
				ghost3.gotoStartLocation();
				ghost4.gotoStartLocation();
				pacman.gotoStartLocation();
				pacman_die_animation.reload();
				SDL_Color text_color = { 255, 204, 102 }; //yellow
				buildText(renderer, text_color, "Ready!", 345, 470, 40);
				SDL_RenderPresent(renderer);
				Sleep(1000);

				(waitDirectionKey(direction));
				direction = ZERO;
				pacman.set_direction(ZERO);
			}
		}


		if (new_game)
		{
			new_game = false;
				SDL_Color text_color = { 255, 204, 102 }; //yellow
				buildText(renderer, text_color, "Ready!", 345, 470, 40);
				SDL_RenderPresent(renderer);
				Sleep(1000);
			
		}

		// pause if enable
		if (game_choice == 3)
		{
			// build score and label "pause"
			renderTexture(background_texture, renderer, 0, 0);
			SDL_Texture* text_texture = TextToTexture(renderer, "Pause", "Fonts/Magneto.ttf", { 255, 255, 255 }, 70);
			renderTexture(text_texture, renderer, 210, 100);
			buildScore(renderer, score, 210, 200);
			buildTime(renderer, current_time, 210, 240);
			SDL_RenderPresent(renderer);

			// build menu
			Menu menu("Textures/button.png", "Textures/button_allocated.png", "Textures/background.png", renderer, 3);
			menu.set_button_location(0, 210, 300);
			menu.set_button_location(1, 210, 400);
			menu.set_button_location(2, 210, 500);
			menu.set_button_text(0, "Resume");
			menu.set_button_text(1, "End game");
			menu.set_button_text(2, "Exit");

			bool escape = false;
			int pause_menu_choice = menu.execute(escape);

			if (escape)  game_choice = 0;
			if (pause_menu_choice == 0) game_choice = 0; // resume	
			if (pause_menu_choice == 1)
			{
				menu_choice = 0; // end game
				return score;
			}
			if (pause_menu_choice == 2)
			{
				menu_choice = 2; // end game
				return score;
			}
			
		}
		// game over
		if (game_choice == 1)
		{
			// build score and label "game over"
			renderTexture(background_texture, renderer, 0, 0);
			SDL_Texture* text_texture = TextToTexture(renderer, "Game over!", "Fonts/Magneto.ttf", { 255, 255, 255 }, 70);
			renderTexture(text_texture, renderer, 210, 100);
			buildScore(renderer, score, 210, 200);
			buildTime(renderer, current_time, 210, 240);
			SDL_RenderPresent(renderer);

			// build menu
			Menu menu("Textures/button.png", "Textures/button_allocated.png", "Textures/background.png", renderer, 3);
			menu.set_button_location(0, 210, 300);
			menu.set_button_location(1, 210, 400);
			menu.set_button_location(2, 210, 500);
			menu.set_button_text(0, "Try again");
			menu.set_button_text(1, "Main menu");
			menu.set_button_text(2, "Exit");
			
			bool escape = false;
			int game_over_menu_choice = menu.execute(escape);

			if (escape == true) exit(0);
			else
			{
				if (game_over_menu_choice == 0)
				{
					menu_choice = 1;
					return score;
				}			
				if (game_over_menu_choice == 1)
				{
					menu_choice = 0;
					return score;
				}
				if (game_over_menu_choice == 2)
				{
					menu_choice = 2;
					return score;
				}
			}
			score = 0;
		}


		// win
		if (game_choice == 2)
		{
			// build score and label
			renderTexture(background_texture, renderer, 0, 0);
			SDL_Texture* text_texture = TextToTexture(renderer, "Done!", "Fonts/Magneto.ttf", { 255, 255, 255 }, 70);
			renderTexture(text_texture, renderer, 210, 100);
			buildScore(renderer, score, 210, 200);
			SDL_RenderPresent(renderer);

			Sleep(1000);
			game_choice = 0;
			ghost1.gotoStartLocation();
			ghost2.gotoStartLocation();
			ghost3.gotoStartLocation();
			ghost4.gotoStartLocation();
			pacman.gotoStartLocation();

			points.reload();
			big_points.reload();

		}
	}//game
}