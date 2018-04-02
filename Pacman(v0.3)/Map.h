#pragma once

#include<iostream>
#include<fstream>

#include<SDL.h>
#include<SDL_image.h>
#include<cmath>
//#include"Game.h"
#include"Library.h"
#include"Standart.h"

#define KILL_ZONE 10


struct Location
{
	int x;
	int y;
	int j;
	int i;

	bool enable;


	void operator=(Location* b)
	{
		this->x = b->x;
		this->y = b->y;
	}


	float operator-(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));

		return (r1 - r2);
	}

	float operator+(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));

		return (r1 + r2);
	}



	bool operator>(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));
		if (r1 > r2) return true;
		else return false;
	}

	bool operator<(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));
		if (r1 < r2) return true;
		else return false;
	}

	bool operator>=(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));
		if (r1 >= r2) return true;
		else return false;
	}

	bool operator<=(Location b)
	{
		float r1 = (float)sqrt(pow(this->x, 2) + pow(this->x, 2));
		float r2 = (float)sqrt(pow(b.x, 2) + pow(b.x, 2));
		if (r1 <= r2) return true;
		else return false;
	}

	/* bool operator==(Location b)
	{
	if ((x / 40) == (b.x / 40)) && ((y / 40) == (b.y / 40))) return true;
	else return false;
	}
	*/
	bool operator==(Location b)
	{
		if ((this->i == b.i) && (this->j == b.j)) return true;
		else return false;
	}
	bool operator>>(Location b)
	{
		if ( abs(this->x - b.x)<= KILL_ZONE && abs(this->y - b.y)<= KILL_ZONE) return true;
		else return false;
	}

}

;
class Map
{
	int width;
	int height;
	int tile_size;



	SDL_Texture** wall_texture;
	SDL_Texture* background_texture;
	SDL_Renderer* renderer;

	Location shelter_location;
	int** walldest;

public:
	Map();
	Map(std::string wall_texture_location, std::string backgroung_texture_location, SDL_Renderer* renderer, std::string location);
	~Map();


	void set_walldest(int, int, const char*);
	void set_shelter_location(int i, int j);
	int get_walldest(int, int);
	int get_tile_size(){return tile_size;}
	int get_width(){return width;}
	int get_height(){return height;}
	Location* get_shelter_location(){return &shelter_location;}
	void loadTextures();

	void build();
	
	
	/*debug*/void show();
};

