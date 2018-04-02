#pragma once
#include "Ghost.h"


Ghost::Ghost()
{
	location = new Location;
	start_location = new Location;
}


Ghost::~Ghost()
{
	delete start_location;
	delete location;
}


Ghost::Ghost(Animations* new_animation, std::string alarm_texture_location, Animations* new_alarm_end_animation, std::string return_texture_location, SDL_Renderer* new_renderer, int new_x, int new_y, int new_speed)
{
	location = new Location;
	start_location = new Location;

	location->x = new_x;
	location->y = new_y;

	start_location->x = new_x;
	start_location->y = new_y;

	renderer = new_renderer;

	alarm = false;
	alarm_end = false;
	return_ = false;
	speed = new_speed;

	current_direction = UP;
	animation = new_animation;
	alarm_end_animation = new_alarm_end_animation;
	alarm_texture = loadTexture(alarm_texture_location.c_str(), renderer);
	return_texture = loadTexture(return_texture_location.c_str(), renderer);
}




void Ghost::build()
{
	if (alarm_end == true) renderTexture(alarm_end_animation->get_texture(LEFT), renderer, location->x, location->y);
	else if (alarm == true) renderTexture(alarm_texture, renderer, location->x, location->y);
	else if (return_ == true) renderTexture(return_texture, renderer, location->x, location->y);
	else renderTexture(animation->get_texture(current_direction), renderer, location->x, location->y);
}



void Ghost::update(Map* map, Pacman* pacman, int randomize_num)
{
	
	PossibleDirections* new_possible_directions = new_findPossibleDirections(map, location->y, location->x);

	int i = location->i = location->y / map->get_tile_size();
	int j = location->j = location->x / map->get_tile_size();

	if (checkCrossroad(location, map))
	{
		// check 
		if (checkShelter(map, i, j) == true)
		{
			return_ = false;
			alarm = false;
		}

		// find possible directions
		PossibleDirections* possible_directions = findPossibleDirections(map, i, j);

		// find distance between ghost and pacman
		int distance = (int)(&pacman->location - location);


		// create random number to reduce level of game
		int random_number = Random(20, randomize_num);
		bool is_random_direction = false;

		if (random_number <= 4 || alarm == true) is_random_direction = true;
		
	
// change direction
		if (map->get_walldest(i, j) == 10 && !return_)
		{
			current_direction = UP;
			is_random_direction = false;
		}

		// if we have 1 direction
		if (possible_directions->count == 1)
		{
			if (possible_directions->right == true) current_direction = RIGHT;
			
			else if (possible_directions->left == true)	current_direction = LEFT;
			
			else if (possible_directions->down == true) current_direction = DOWN;
			
			else if (possible_directions->up == true) current_direction = UP;
		}

		//if we have 2, 3, 4
		else
		{
			if (return_)
			{
				if (map->get_walldest(i, j) == 5)
				{
					current_direction = DOWN;
					is_random_direction = false;
				}
				else
				{
					Direction new_direction = targetDirection(location, possible_directions, current_direction, map->get_shelter_location());
					if (new_direction != ZERO)
					{
						current_direction = new_direction;
						is_random_direction = false;
					}
					else is_random_direction = true;
				}
			}

			// if we use pursue methods
			else if (distance < 5 && is_random_direction == false)
			{
				// returns ZERO if this method can't find out current direction to fulfill all conditions
				// and if it can't we use random

 				Direction new_direction = pursueDirection(location, possible_directions, current_direction, &pacman->get_location(), pacman->get_direction(), randomize_num);
				if (new_direction != ZERO)	current_direction = new_direction;
				

				else is_random_direction = true; 		
			}

			// if we use random 
			if (is_random_direction == true)
			{
				random_number = Random(4, randomize_num);
				current_direction = randomDirection(possible_directions, current_direction, randomize_num);

			}
		}
	}

	// change location



	if (return_) changeLocation(location, current_direction, 10);
	else if (alarm) changeLocation(location, current_direction, 2);
	else if (location->x % speed == 0 && location->y % speed == 0) changeLocation(location, current_direction, speed);
	else changeLocation(location, current_direction, 2);
}



void Ghost::gotoStartLocation()
{
	return_ = false;
	alarm = false;
	alarm_end = false;
	location->x = start_location->x;
	location->y = start_location->y;
}





void  Ghost::viceversaDirection()
{
	if (current_direction == RIGHT) current_direction = LEFT;
	else if (current_direction == LEFT) current_direction = RIGHT;
	else if (current_direction == UP) current_direction = DOWN;
	else if (current_direction == DOWN) current_direction = UP;
}










/*void Ghost::update(Map* map, Location* pacman_location, int random_number)
{

	if ((location.y % map->get_tile_size() == 0) && (location.x % map->get_tile_size() == 0))
	{
		int i = location.y / map->get_tile_size();
		int j = location.x / map->get_tile_size();


	

		Direction priority_direction_y;
		if (i > (pacman_location->y / map->get_tile_size()))
		{
			priority_direction_y = UP;
		}
		else priority_direction_y = DOWN;

		


		Direction priority_direction_x;
		if (i > (pacman_location->x / map->get_tile_size()))
		{
			priority_direction_x = LEFT;
		}
		else priority_direction_x = RIGHT;

		//debug
		//std::cout << "\r" << "I: " << i << ", J: " << j << "\t\t";
		//	
		
		//change direction
		PossibleDirections* possible_directions = findPossibleDirections(map, i, j);
		int rand_temp = -1;


		switch (possible_directions->count)
		{ 
			if()
















		case 4:
		{
			rand_temp = Random(20, random_number);

			if (rand_temp > Rand_number)
			{

				if ((priority_direction_y == UP) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((priority_direction_y == DOWN) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;

				else if ((priority_direction_x == LEFT) && (possible_directions->left == true) && current_direction != RIGHT) current_direction = LEFT;

				else if ((priority_direction_x == RIGHT) && (possible_directions->right == true) && current_direction != LEFT) current_direction = RIGHT;
			}
			
			else if(rand_temp > Rand_number/2)
			{
				 if ((priority_direction_x == LEFT) && (possible_directions->left == true) && current_direction != RIGHT) current_direction = LEFT;

				else if ((priority_direction_x == RIGHT) && (possible_directions->right == true) && current_direction != LEFT) current_direction = RIGHT;
		
				else if ((priority_direction_y == UP) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((priority_direction_y == DOWN) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;

			}

			else if (rand_temp > 3)
			{
				;
			}
			else if (rand_temp == 0)
			{
				current_direction = LEFT;
			}
			else if (rand_temp == 1)
			{
				current_direction = RIGHT;
				break;
			}
			else if (rand_temp == 2)
			{
				current_direction = DOWN;
				break;
			}
			else if (rand_temp == 3)
			{
				current_direction = UP;
				break;
			}
			else
			{
				rand_temp = Random(4, random_number) +1;
				current_direction = (Direction)(rand_temp);
			}
		break;
		}

		case 3:
		{
			
			rand_temp = Random(10, random_number);

			if (rand_temp > Rand_number)
			{
				if ((priority_direction_y == UP) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((priority_direction_y == DOWN) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;

				else if ((priority_direction_x == LEFT) && (possible_directions->left == true) && current_direction != RIGHT) current_direction = LEFT;

				else if ((priority_direction_x == RIGHT) && (possible_directions->right == true) && current_direction != LEFT) current_direction = RIGHT;
			}

			else if (rand_temp > Rand_number/2)
			{
					 if ((priority_direction_x == LEFT) && (possible_directions->left == true) && current_direction != RIGHT) current_direction = LEFT;

				else if ((priority_direction_x == RIGHT) && (possible_directions->right == true) && current_direction != LEFT) current_direction = RIGHT;

				else if ((priority_direction_y == UP) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((priority_direction_y == DOWN) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;

			
			}
			else
			{
				rand_temp = Random(3, random_number);

				if ((rand_temp == 0) && (possible_directions->right == true) && current_direction != LEFT)	current_direction = RIGHT;

				else if ((rand_temp == 1) && (possible_directions->left == true) && current_direction != RIGHT)	current_direction = LEFT;

				else if ((rand_temp == 2) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((rand_temp == 3) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;



				else if ((rand_temp == 3) && (possible_directions->right == true) && current_direction != LEFT)	current_direction = RIGHT;

				else if ((rand_temp == 0) && (possible_directions->left == true) && current_direction != RIGHT)	current_direction = LEFT;

				else if ((rand_temp == 1) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((rand_temp == 2) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;



				else if ((rand_temp == 2) && (possible_directions->right == true) && current_direction != LEFT)	current_direction = RIGHT;

				else if ((rand_temp == 3) && (possible_directions->left == true) && current_direction != RIGHT)	current_direction = LEFT;

				else if ((rand_temp == 0) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((rand_temp == 1) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;



				else if ((rand_temp == 1) && (possible_directions->right == true) && current_direction != LEFT)	current_direction = RIGHT;

				else if ((rand_temp == 2) && (possible_directions->left == true) && current_direction != RIGHT)	current_direction = LEFT;

				else if ((rand_temp == 3) && (possible_directions->up == true) && current_direction != DOWN) current_direction = UP;

				else if ((rand_temp == 0) && (possible_directions->down == true) && current_direction != UP) current_direction = DOWN;

			}

		/*
			// -> current: up & down
			if (current_direction == UP || current_direction == DOWN)
			{
				if ((possible_directions->up == false && current_direction == UP) || (possible_directions->down == false && current_direction == DOWN))
				{
					int rand_temp = Random(2);

					if ((rand_temp == 0) && (possible_directions->right == true))
					{
						current_direction = RIGHT;
					}
					else if ((rand_temp == 1) && (possible_directions->left == true))
					{
						current_direction = LEFT;
					}

					// for acceleration
					else if ((rand_temp == 1) && (possible_directions->right == true))
					{
						current_direction = RIGHT;
						break;
					}
					else if ((rand_temp == 0) && (possible_directions->left == true))
					{
						current_direction = LEFT;
						break;
					}
				}
			}

			// -> up & down
			else if (current_direction != UP && current_direction != DOWN)
			{
				if ((possible_directions->left == false && current_direction == LEFT) || (possible_directions->right == false && current_direction == RIGHT))
				{
					int rand_temp = Random(2);

					if ((rand_temp == 0) && (possible_directions->down == true))
					{
						current_direction = DOWN;
					}
					else if ((rand_temp == 1) && (possible_directions->up == true))
					{
						current_direction = UP;
					}

					// for acceleration
					else if ((rand_temp == 1) && (possible_directions->down == true))
					{
						current_direction = DOWN;
					}
					else if ((rand_temp == 0) && (possible_directions->up == true))
					{
						current_direction = UP;
					}
				}
			}
			// up & down -> right or left 
			else if (current_direction == UP || current_direction == DOWN)
			{
				int rand_temp = Random(2);

				if (rand_temp == 1)
				{
					;

				}
				else if (possible_directions->right == true)
				{
					current_direction = RIGHT;

				}
				else if (possible_directions->left == true)
				{
					current_direction = LEFT;
				}

			}
			// right & left -> up or down 
			else if (current_direction == RIGHT || current_direction == LEFT)
			{
				int rand_temp = Random(2);

				if (rand_temp == 0)
				{
					;

				}
				else if (possible_directions->up == true)
				{
					current_direction = UP;
				}
				else if (possible_directions->down == true)
				{
					current_direction = DOWN;
				}
			}
			
			
		break;	
		}


		case 2:
		{
			if (possible_directions->right == true && possible_directions->left == true && (current_direction == RIGHT || current_direction == LEFT))
			{
				;
			}
			else if (possible_directions->down == true && possible_directions->up == true && (current_direction == DOWN || current_direction == RIGHT))
			{
				;
			}
			else if (current_direction == UP || current_direction == DOWN)
			{

				if (possible_directions->right == true) current_direction = RIGHT;
				if (possible_directions->left == true) current_direction = LEFT;

			}

			else if (current_direction == LEFT || current_direction == RIGHT)
			{
				if (possible_directions->down == true) current_direction = DOWN;
				if (possible_directions->up == true) current_direction = UP;
			}


		break;
		}


		case 1:
		{
			if (possible_directions->right == true)
			{
				current_direction = RIGHT;
			}
			else if (possible_directions->left == true)
			{
				current_direction = LEFT;
			}

			else if (possible_directions->down == true)
			{
				current_direction = DOWN;
			}
			else if (possible_directions->up == true)
			{
				current_direction = UP;
			}
		break;
		}


		default:
		{
			std::cout << "Error! Possible directions count != 1, 2, 3, 4" << std::endl;
		break;
		}
		}
	}
	if (current_direction == UP)
	{
		location.y -= speed;
	}
	else if (current_direction == DOWN)
	{
		location.y += speed;
	}
	else if (current_direction == LEFT)
	{
		location.x -= speed;
	}
	else if (current_direction == RIGHT)
	{
		location.x += speed;
	}
}

*/