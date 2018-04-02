#include "Map.h"



Map::Map()
{
	walldest = allocateMatrix(width, height);
}

Map::Map(std::string wall_texture_location, std::string backgroung_texture_location, SDL_Renderer* new_renderer, std::string location)
{
	//grafics
	renderer = new_renderer;
	wall_texture = new SDL_Texture*[40];
	background_texture = loadTexture(backgroung_texture_location.c_str(), renderer);
	loadTextures();

	//parameters
	std::ifstream map_file(location);

	map_file >> width;
	map_file >> height;
	map_file >> tile_size;


	walldest = allocateMatrix(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int temp;
			map_file >> temp;
			walldest[i][j] = temp;
			if (walldest[i][j] == 5) set_shelter_location(i, j);
		}
	}
	map_file.close();
}

Map::~Map()
{
	deleteMatrix(walldest);
	delete[] wall_texture;
}


void Map::loadTextures()
{
	wall_texture[10] = loadTexture("Textures/Walls/10.png", renderer);
	wall_texture[11] = loadTexture("Textures/Walls/11.png", renderer);
	wall_texture[12] = loadTexture("Textures/Walls/12.png", renderer);
	wall_texture[13] = loadTexture("Textures/Walls/13.png", renderer);
	wall_texture[14] = loadTexture("Textures/Walls/14.png", renderer);
	
	wall_texture[15] = loadTexture("Textures/Walls/15.png", renderer);

	wall_texture[21] = loadTexture("Textures/Walls/21.png", renderer);
	wall_texture[22] = loadTexture("Textures/Walls/22.png", renderer);
	wall_texture[23] = loadTexture("Textures/Walls/23.png", renderer);
	wall_texture[24] = loadTexture("Textures/Walls/24.png", renderer);
	wall_texture[25] = loadTexture("Textures/Walls/25.png", renderer);
	wall_texture[26] = loadTexture("Textures/Walls/26.png", renderer);

	wall_texture[31] = loadTexture("Textures/Walls/31.png", renderer);
	wall_texture[32] = loadTexture("Textures/Walls/32.png", renderer);
	wall_texture[33] = loadTexture("Textures/Walls/33.png", renderer);
	wall_texture[34] = loadTexture("Textures/Walls/34.png", renderer);
}


void Map::set_shelter_location(int i, int j)
{
		shelter_location.x = j*tile_size;
		shelter_location.y = i*tile_size;
		shelter_location.j = j;
		shelter_location.i = i;
}

void Map::set_walldest(int i, int j, const char* value)
{
	;
}

int Map::get_walldest(int i, int j)
{
	if (i < width && j < height && i >= 0 && j >= 0)
		return walldest[i][j];
	else
	{
		Error("Error: map get_wallset, i or j > width or height");
		return -1;
	}
}

void Map::show()
{
	std::cout << "Map: " << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << walldest[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

void Map::build()
{
	renderTexture(background_texture, renderer, 0, 0);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int y = i * tile_size;
			int x = j * tile_size;


			if(walldest[i][j] >= 10) renderTexture(wall_texture[walldest[i][j]], renderer, x, y);

		}
	}
}