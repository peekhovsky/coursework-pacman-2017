#include "Pacman.h"



Pacman::Pacman(Animations* new_animation, Animations* new_die_animation, SDL_Renderer* new_renderer, int new_x, int new_y, int new_speed)
{
	//point = nullptr;
	start_location.x = location.x = new_x;
	start_location.y = location.y = new_y;
	

	renderer = new_renderer;	
	//texture = loadTexture(texture_location.c_str(), new_renderer);

	animation = new_animation;
	die_animation = new_die_animation;
	speed = new_speed;
	current_direction = ZERO;
	next_direction = ZERO;


}

Pacman::~Pacman()
{
	
}



void Pacman::build()
{
	renderTexture(animation->get_texture(current_direction), renderer, location.x, location.y);
}

void Pacman::build_die()
{
	renderTexture(die_animation->get_texture(), renderer, location.x, location.y);
}


int Pacman::update(Direction new_direction, Map& map, Points* point, BigPoints* big_point)
{
	int coins = 0;
	next_direction = new_direction;

	int i = location.i = location.y / map.get_tile_size();
	int j = location.j = location.x / map.get_tile_size();

	if ((location.y % map.get_tile_size() == 0) && (location.x % map.get_tile_size() == 0))
	{

		//debug
		std::cout <<"\r"<<"I: " << i << ", J: " << j<<"\t\t";
		//

		//change direction
		if (current_direction != next_direction)
		{
			if (map.get_walldest(i + 1, j) < 10 && (next_direction == DOWN))
			{
				current_direction = DOWN;
			}
			if (map.get_walldest(i - 1, j) < 10 && (next_direction == UP))
			{
				current_direction = UP;
			}
			if (map.get_walldest(i, j + 1) < 10 && (next_direction == RIGHT))
			{
				current_direction = RIGHT;
			}
			if (map.get_walldest(i, j - 1) < 10 && (next_direction == LEFT))
			{
				current_direction = LEFT;
			}
		}

		// stop direction
		if (map.get_walldest(i + 1, j) > 10 && (current_direction == DOWN))
		{
			current_direction = ZERO;
		}
		if (map.get_walldest(i - 1, j) > 10 && (current_direction == UP))
		{
			current_direction = ZERO;
		}
		if (map.get_walldest(i, j + 1) > 10 && (current_direction == RIGHT))
		{
			current_direction = ZERO;
		}
		if (map.get_walldest(i, j - 1) > 10 && (current_direction == LEFT))
		{
			current_direction = ZERO;
		}

		// teleportation
		if (map.get_walldest(i, j) == 8)
		{
			if (j == 3) location.x = map.get_tile_size()*(map.get_width()-2);
			if (j == 19) location.x = map.get_tile_size() + 1;
		}


		//points
		if (point->eat(i, j)) coins = 10;
		if (big_point->eat(i, j)) coins = 11;
	}
	

	else if ((next_direction == DOWN && current_direction == UP) || 
			 (next_direction == UP && current_direction == DOWN) ||
			 (next_direction == LEFT && current_direction == RIGHT) || 
			 (next_direction == RIGHT && current_direction == LEFT))
	{
		current_direction = next_direction;
	}



	// change location
	changeLocation(&location, current_direction, speed);

	
	return coins;
}



void Pacman::gotoStartLocation()
{
	location.x = start_location.x;
	location.y = start_location.y;
}

