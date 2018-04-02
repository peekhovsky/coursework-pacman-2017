#include "HighScore.h"



HighScore::HighScore()
{
}

HighScore::HighScore(SDL_Renderer* new_renderer, string new_file_loc)
{
	renderer = new_renderer;
	file_loc = new_file_loc;

	read();
}

HighScore::~HighScore()
{
	record();
}

void HighScore::read()
{
	std::ifstream map_file(file_loc);

	for (int i = 0; i < SCORE_QUANT; i++)
	{
		map_file >> data[i];
	}


	map_file.close();
}

void HighScore::record()
{
	std::ofstream map_file(file_loc);

	for (int i = 0; i < SCORE_QUANT; i++)
	{
		map_file << data[i];
		map_file << "\n";
	}
	
	map_file.close();
}

void HighScore::set_new(int new_score)
{
	for (int i = 0; i < SCORE_QUANT; i++)
	{
		if (new_score > data[i])
		{
			
			for (int j = SCORE_QUANT-1; j>=i; j--)
			{
				data[j + 1] = data[j];
			}
			data[i] = new_score;
			break;
		}
	}
}


void HighScore::build()
{
	SDL_Texture* background_texture = loadTexture("Textures/background.png", renderer);

	renderTexture(background_texture, renderer, 0, 0);
	SDL_Color text_color = { 255, 255, 255 }; 
	SDL_Texture* coins_texture = TextToTexture(renderer, "High Scores", "Fonts/Magneto.ttf", text_color, 50);
	renderTexture(coins_texture, renderer, 200, 30);

	for (int i = 0; i < SCORE_QUANT; i++)
	{
		char coins_char[100];
		coins_char[0] = '\0';
		_itoa_s(data[i], coins_char, 100, 10);

		std::string coins_str(coins_char);

		SDL_Texture* coins_texture = TextToTexture(renderer, coins_str, "Fonts/Magneto.ttf", text_color, 30);
		renderTexture(coins_texture, renderer, 370, 150 + 50*i);
	}

	SDL_RenderPresent(renderer);
	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}
		if (event.type == SDL_QUIT)
		{
			exit(0);
		}
	
	}

}