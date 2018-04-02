#include"Game.h"

#define TILE_SIZE 40

// returns "0" if user presses dir. keys;
// returns "3" if user presses ESC 
int waitDirectionKey(Direction& direction)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			direction = UP;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			direction = DOWN;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			direction = LEFT;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			direction = RIGHT;
			break;
		
		default:
			break;
		}	
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return 3;
			}
		}

		if (event.type == SDL_QUIT)
		{
			exit(0);
		}
	}
	return NULL;
}



// finds possible directions for pacman and ghosts by changing PossibleDirections structure

PossibleDirections* findPossibleDirections(Map* map, int i, int j)
{
	PossibleDirections* possible_directions = new PossibleDirections;
	possible_directions->count = 0;
	if (map->get_walldest(i, j + 1) < 11 )
	{
		possible_directions->right = true;
		possible_directions->count++;
	}
	else possible_directions->right = false;

	if (map->get_walldest(i, j - 1) < 11)
	{
		possible_directions->left = true;
		possible_directions->count++;
	}
	else possible_directions->left = false;

	if (map->get_walldest(i + 1, j)  < 10)
	{
		possible_directions->down = true;
		possible_directions->count++;
	}
	else possible_directions->down = false;

	if (map->get_walldest(i - 1, j) < 11)
	{
		if (map->get_walldest(i - 1, j) == 10)
		{
			int temp = rand() % 10;
			if(temp == 0) possible_directions->up = true;
		}
		else possible_directions->up = true;
		possible_directions->count++;
	}
	else possible_directions->up = false;

	return possible_directions;
}

PossibleDirections* new_findPossibleDirections(Map* map, int y, int x)
{
	PossibleDirections* possible_directions = new PossibleDirections;

	// find i and j
	int i = abs(y / map->get_tile_size());
	int j = abs(x / map->get_tile_size());


		possible_directions->count = 0;
		if (map->get_walldest(i, j + 1) > 1)
		{
			possible_directions->right = true;
			possible_directions->count++;
		}
		else possible_directions->right = false;

		if (map->get_walldest(i, j - 1) > 1)
		{
			possible_directions->left = true;
			possible_directions->count++;
		}
		else possible_directions->left = false;

		if (map->get_walldest(i + 1, j) > 1)
		{
			possible_directions->down = true;
			possible_directions->count++;
		}
		else possible_directions->down = false;

		if (map->get_walldest(i - 1, j) > 1)
		{
			possible_directions->up = true;
			possible_directions->count++;
		}
		else possible_directions->up = false;

	return possible_directions;
}



// returns true if this place is not a direct road
bool checkCrossroad(Location* location, Map* map)
{
	if ((location->y  % map->get_tile_size() == 0) && (location->x % map->get_tile_size() == 0)) return true;
	else return false;
}


// using "Indian code" for a speed
	// if we were using loop speed of the game would be small
// returns random direction expect the opposite direction

Direction randomDirection(PossibleDirections* possible_directions, Direction current_direction, int randomize_num)
{
	int random_number = Random(4, randomize_num);
	Direction direction = current_direction;

	switch (random_number)
	{
	case 0:
	
	    if		(possible_directions->down	== true && current_direction != UP)		direction = DOWN;
		else if (possible_directions->up	== true && current_direction != DOWN)	direction = UP;
		else if (possible_directions->left	== true && current_direction != RIGHT)	direction = LEFT;
		else if (possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;
		break;
	
	case 1:
	
		if		(possible_directions->right	== true && current_direction != LEFT)	direction = RIGHT;
		else if (possible_directions->down	== true && current_direction != UP)		direction = DOWN;
		else if (possible_directions->up	== true && current_direction != DOWN)	direction = UP;
		else if (possible_directions->left	== true && current_direction != RIGHT)	direction = LEFT;
		break;
	
	case 2:
	
		if		(possible_directions->left	== true && current_direction != RIGHT)	direction = LEFT;
		else if (possible_directions->right	== true && current_direction != LEFT)	direction = RIGHT;
		else if (possible_directions->down	== true && current_direction != UP)		direction = DOWN;
		else if (possible_directions->up	== true && current_direction != DOWN)	direction = UP;
		break;
	
	case 3:
	
		if		(possible_directions->up	== true && current_direction != DOWN)	direction = UP;
		else if (possible_directions->left	== true && current_direction != RIGHT)	direction = LEFT;
		else if (possible_directions->right	== true && current_direction != LEFT)	direction = RIGHT;
		else if (possible_directions->down	== true && current_direction != UP)		direction = DOWN;
		break;
	
	}
	return direction;
}



// returs direction depending on location of pacman


Direction pursueDirection(Location* location, PossibleDirections* possible_directions, Direction current_direction,
	Location* bot_location, Direction bot_direction,  int randomize_num)
{
	
	// find out priority directions depending on pacman
	Direction priority_direction_i;
	if (location->i > bot_location->i)	priority_direction_i = UP;
	else								priority_direction_i = DOWN;

	Direction priority_direction_j;
	if (location->j > bot_location->j)	priority_direction_j = LEFT;
	else								priority_direction_j = RIGHT;


	int random_number = Random(2, randomize_num);

	Direction direction = ZERO;

	// pursue pacman if we can
	if		(bot_direction == DOWN	&& possible_directions->down == true && current_direction != UP)	direction = DOWN;
	else if (bot_direction == UP	&& possible_directions->up == true && current_direction != DOWN)	direction = UP;
	else if (bot_direction == LEFT	&& possible_directions->left == true && current_direction != RIGHT) direction = LEFT;
	else if (bot_direction == RIGHT	&& possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;

	// if cannot try to go to pacman region
	else if (random_number == 0)
	{
		if		(priority_direction_i == DOWN	&& possible_directions->down == true && current_direction != UP)	direction = DOWN;
		else if (priority_direction_i == UP		&& possible_directions->up == true && current_direction != DOWN)	direction = UP;
		else if (priority_direction_j == LEFT	&& possible_directions->left == true && current_direction != RIGHT)	direction = LEFT;
		else if (priority_direction_j == RIGHT	&& possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;
	}

	// for acceleration 
	else if (random_number == 1)
	{
		if		(priority_direction_j == LEFT	&& possible_directions->left == true && current_direction != RIGHT)	direction = LEFT;
		else if (priority_direction_j == RIGHT	&& possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;
		else if (priority_direction_i == DOWN	&& possible_directions->down == true && current_direction != UP)	direction = DOWN;
		else if (priority_direction_i == UP		&& possible_directions->up == true && current_direction != DOWN)	direction = UP;
	}

	return direction;
}

Direction targetDirection(Location* location, PossibleDirections* possible_directions, Direction current_direction, Location* target_location)
{

	// find out priority directions depending on pacman
	Direction priority_direction_i;
	if (location->y > target_location->y)			priority_direction_i = UP;
	else if (location->y == target_location->y) 	priority_direction_i = ZERO;
	else											priority_direction_i = DOWN;

	Direction priority_direction_j;
	if (location->x > target_location->x)			priority_direction_j = LEFT;
	else if (location->x == target_location->x) 	priority_direction_j = ZERO;
	else											priority_direction_j = RIGHT;

	Direction direction = ZERO;


	if (abs(location->y - target_location->y) > abs(location->x - target_location->x))
	{
		if (priority_direction_i == DOWN			&& possible_directions->down == true && current_direction != UP)	direction = DOWN;
		else if (priority_direction_i == UP			&& possible_directions->up == true && current_direction != DOWN)	direction = UP;
		else if (priority_direction_j == LEFT		&& possible_directions->left == true && current_direction != RIGHT)	direction = LEFT;
		else if (priority_direction_j == RIGHT		&& possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;		

	}
	else 
	{
		if (priority_direction_j == LEFT			&& possible_directions->left == true && current_direction != RIGHT)	direction = LEFT;
		else if (priority_direction_j == RIGHT		&& possible_directions->right == true && current_direction != LEFT)	direction = RIGHT;
		else if (priority_direction_i == DOWN		&& possible_directions->down == true && current_direction != UP)	direction = DOWN;
		else if (priority_direction_i == UP			&& possible_directions->up == true && current_direction != DOWN)	direction = UP;
	}
	
	return direction;
}





// changes location of pacman and ghosts on a map



void changeLocation(Location* location, Direction current_direction, int speed)
{
	int shift_x = location->x % TILE_SIZE;
	int shift_y = location->y % TILE_SIZE;
	
	//moving
		if (current_direction == UP)
		{
			if (shift_y < speed && shift_y!=0)
			{
				location->y -= shift_y;
			}
			else location->y -= speed;
		}
		else if (current_direction == DOWN)
		{
			if ((TILE_SIZE - shift_y) < speed && shift_y != 0)
			{
				location->y += TILE_SIZE - shift_y;
			}
			else location->y += speed;
		}	
		else if (current_direction == LEFT )
		{
			if (shift_x < speed && shift_x != 0)
			{
				location->x -= shift_x;
			}
			else location->x -= speed;
		}
		else if (current_direction == RIGHT)
		{
			if ((TILE_SIZE - shift_x) < speed && shift_x != 0)
			{
				location->x += TILE_SIZE - shift_x;
			}
			else location->x += speed;
		}
	//teleport
		if ((location->x - 1) / TILE_SIZE == 0 && location->y / TILE_SIZE == 9)
		{
			location->x = 19 * TILE_SIZE - 1;
		}
		else if (location->x / TILE_SIZE == 19 && location->y/ 40 == 9)
		{
			location->x = 1 * TILE_SIZE + 1;
		}
}


// returns true if this place is shelter
bool checkShelter(Map* map, int i, int j)
{
	if (map->get_walldest(i, j) == 2)
	{
		return true;
	}
	else return false;
}

void KillPause()
{
	;
}