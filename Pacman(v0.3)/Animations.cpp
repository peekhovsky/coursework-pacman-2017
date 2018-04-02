#include "Animations.h"


Animations::Animations(SDL_Renderer* new_renderer, int new_size, int new_pause)
{
	renderer = new_renderer;
	size = new_size;
	current_texture = 0;

	texture_left = new SDL_Texture*[size];
	texture_right = new SDL_Texture*[size];
	texture_up = new SDL_Texture*[size];
	texture_down = new SDL_Texture*[size];
	
	pause = new_pause;
	current = 0;
}

Animations::~Animations()
{
	delete[] texture_left;
	delete[] texture_right;
	delete[] texture_up;
	delete[] texture_down;
}


SDL_Texture* Animations::get_texture(Direction direction)
{
	if (current<pause)
	{
		current++;
	}
	else
	{
		current = 0;
		current_texture++;
	}
	if (current_texture >= size) current_texture = 0;
	//current_texture = 0;

	if (direction == LEFT)	return texture_left[current_texture];
	if (direction == RIGHT)	return texture_right[current_texture];
	if (direction == UP)	return texture_up[current_texture];
	if (direction == DOWN)	return texture_down[current_texture];
	else	return texture_left[0];
}

SDL_Texture* Animations::get_texture()
{
	if (current<pause)
	{
		current++;
	}
	else
	{
		current = 0;
		current_texture++;
	}
	if (current_texture >= size) return texture_left[size-1];

	return texture_left[current_texture];
}


void Animations::set_texture(std::string file_location, Direction direction, int number)
{
	/*debug*/ if (number >= size) { std::cout << "Error! set_texture: number >= size" << std::endl;  }


	if (direction == LEFT)	 texture_left[number] = loadTexture(file_location.c_str(), renderer);
	if (direction == RIGHT)	 texture_right[number] =loadTexture(file_location.c_str(), renderer);
	if (direction == UP)	 texture_up[number] = loadTexture(file_location.c_str(), renderer);
	if (direction == DOWN)	 texture_down[number] = loadTexture(file_location.c_str(), renderer);
}

void Animations::setPacmanTextures()
{
	//left
	set_texture("Textures/Pacman/0.png",	 LEFT, 0);
	set_texture("Textures/Pacman/1LEFT.png", LEFT, 1);
	set_texture("Textures/Pacman/2LEFT.png", LEFT, 2);
	set_texture("Textures/Pacman/2LEFT.png", LEFT, 3);

	//right
	set_texture("Textures/Pacman/0.png",	  RIGHT, 0);
	set_texture("Textures/Pacman/1RIGHT.png", RIGHT, 1);
	set_texture("Textures/Pacman/2RIGHT.png", RIGHT, 2);
	set_texture("Textures/Pacman/2RIGHT.png", RIGHT, 3);

	//up
	set_texture("Textures/Pacman/0.png",   UP, 0);
	set_texture("Textures/Pacman/1UP.png", UP, 1);
	set_texture("Textures/Pacman/2UP.png", UP, 2);
	set_texture("Textures/Pacman/2UP.png", UP, 3);

	//down
	set_texture("Textures/Pacman/0.png",	 DOWN, 0);
	set_texture("Textures/Pacman/1DOWN.png", DOWN, 1);
	set_texture("Textures/Pacman/2DOWN.png", DOWN, 2);
	set_texture("Textures/Pacman/2DOWN.png", DOWN, 3);
}

void Animations::setGhost1Textures()
{
	set_texture("Textures/Ghost1/LEFT.png", LEFT, 0);
	set_texture("Textures/Ghost1/RIGHT.png", RIGHT, 0);
	set_texture("Textures/Ghost1/UP.png", UP, 0);
	set_texture("Textures/Ghost1/DOWN.png", DOWN, 0);
	
}

void Animations::setGhost2Textures()
{
	set_texture("Textures/Ghost2/LEFT.png", LEFT, 0);
	set_texture("Textures/Ghost2/RIGHT.png", RIGHT, 0);
	set_texture("Textures/Ghost2/UP.png", UP, 0);
	set_texture("Textures/Ghost2/DOWN.png", DOWN, 0);

}

void Animations::setGhost3Textures()
{
	set_texture("Textures/Ghost3/LEFT.png", LEFT, 0);
	set_texture("Textures/Ghost3/RIGHT.png", RIGHT, 0);
	set_texture("Textures/Ghost3/UP.png", UP, 0);
	set_texture("Textures/Ghost3/DOWN.png", DOWN, 0);

}

void Animations::setGhost4Textures()
{

	set_texture("Textures/Ghost4/LEFT.png", LEFT, 0);
	set_texture("Textures/Ghost4/RIGHT.png", RIGHT, 0);
	set_texture("Textures/Ghost4/UP.png", UP, 0);
	set_texture("Textures/Ghost4/DOWN.png", DOWN, 0);

}

void Animations::setGhostAlarmEndTextures()
{

	set_texture("Textures/Ghost_alarm_end/1.png", LEFT, 0);
	set_texture("Textures/Ghost_alarm_end/2.png", LEFT, 1);


}

void Animations::setPacmanDieTextures()
{

	set_texture("Textures/Pacman/1UP.png", LEFT, 0);
	set_texture("Textures/Pacman/2UP.png", LEFT, 1);
	set_texture("Textures/Pacman/DIE1.png", LEFT, 2);
	set_texture("Textures/Pacman/DIE2.png", LEFT, 3);
	set_texture("Textures/Pacman/DIE3.png", LEFT, 4);
	set_texture("Textures/Pacman/DIE4.png", LEFT, 5);

}


void Animations::build(int sleep, int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		renderTexture(texture_left[i], renderer, x, y);
		SDL_RenderPresent(renderer);
		Sleep(sleep);
	}
}