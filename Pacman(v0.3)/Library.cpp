#define _CRT_SECURE_NO_WARNINGS

#include "Library.h"


// initialize

void initializeSDL()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		std::cout << "Error! Cannot initialize the SDL Library" << std::endl;
	}


	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF) != NULL)
	{
		std::cout << "Error! Cannot initialize the IMG Library" << std::endl;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "Error! Cannot initialize the TTF library" << std::endl;
	}
}

void quitSDL()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



// window creation 

SDL_Window* createWindow(std::string name, int x, int y, int w, int h, Uint32 flags)
{
	SDL_Window* window = SDL_CreateWindow(name.c_str(), x, y, w, h, flags);

	if (window == nullptr)
	{
		std::cout << "Error! Cannot create SDL window, code: " << SDL_GetError() << std::endl;
		exit(1);
	};
	return window;
}

SDL_Window* createWindow(std::string name, int w, int h)
{
	SDL_Window* window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Error! Cannot create SDL window, code: " << SDL_GetError() << std::endl;
		exit(1);
	};
	return window;
}



// renderer creation

SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags)
{
	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, index, flags);
	if (renderer == nullptr)
	{
		std::cout << "Error! Cannot create renderer, code: " << SDL_GetError() << std::endl;
	}
	return renderer;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "Error! Cannot create renderer, code: " << SDL_GetError() << std::endl;
	}
	return renderer;
}



// loading

SDL_Texture* LoadBMP(std::string file, SDL_Renderer* renderer)
{
	// open
	SDL_Surface* load_image = nullptr;
	load_image = SDL_LoadBMP(file.c_str());
	if (load_image == nullptr)
	{
		std::cout << "Error! Cannot load BMP image into surface, code: " << SDL_GetError() << std::endl;
	}

	// load into renderer
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer, load_image);
	if (texture == nullptr)
	{
		std::cout << "Error! Cannot upload BMP surface into renderer, code: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(load_image);
	return texture;
}

SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer)
{
	//open
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(file.c_str());
	if (surface == nullptr)
	{
		std::cout << "Error! Cannot upload image into surface, code: " << SDL_GetError() << std::endl;
	}

	// load into renderer
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Error! Cannot upload surface into renderer, code: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);
	return texture;
}


// rendering

void renderTexture(SDL_Texture* texture, SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void renderTexture(std::string file_location, SDL_Renderer *renderer, int x, int y)
{
	SDL_Texture* texture = loadTexture(file_location, renderer);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}


void renderTexture(SDL_Texture *texture, SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}

	SDL_RenderCopy(renderer, texture, clip, &dst);
}

// text

SDL_Texture* TextToTexture(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Error! Cannot find font file" << std::endl;
		return nullptr;
	}

	SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr)
	{
		std::cout << "Error! Cannot create font surface" << std::endl;
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Error! Cannot create font texture" << std::endl;
		return nullptr;
	}
	//Clean up the surface and font
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}


void buildScore(SDL_Renderer *renderer, int coins, int x, int y)
{
	char coins_char[100];
	coins_char[0] = '\0';
	_itoa_s(coins, coins_char, 100, 10);

	std::string coins_str(coins_char);


	SDL_Color text_color = { 255, 255, 255 };
	SDL_Texture* coins_texture = TextToTexture(renderer, "Score: " + coins_str, "Fonts/Magneto.ttf", text_color, 30);
	renderTexture(coins_texture, renderer, x, y+5);
}

void buildText(SDL_Renderer *renderer, SDL_Color text_color, std::string str, int x, int y, int size)
{

	SDL_Texture* coins_texture = TextToTexture(renderer, str.c_str(), "Fonts/Magneto.ttf", text_color, size);
	renderTexture(coins_texture, renderer, x, y);
}

void buildTime(SDL_Renderer *renderer, int current_time, int x, int y)
{
	
	
	int minutes = current_time / (1000 * 60);
	current_time = current_time % (1000 * 60);
	int seconds = current_time / 1000;
	int miliseconds = current_time % 1000;

	const int buff_size = 10;

	char char_current_minutes[buff_size];
	_itoa_s(minutes, char_current_minutes, buff_size, 10);
	std::string str_current_minutes(char_current_minutes);

	char char_current_seconds[buff_size];
	_itoa_s(seconds, char_current_seconds, buff_size, 10);
	std::string str_current_seconds(char_current_seconds);

	char char_current_miliseconds[buff_size];
	_itoa_s(miliseconds, char_current_miliseconds, buff_size, 10);
	std::string str_current_miliseconds(char_current_miliseconds);



	SDL_Color text_color = { 255, 255, 255 };
	SDL_Texture* coins_texture = TextToTexture(renderer, "Time: " + str_current_minutes + ":" + str_current_seconds + ":" + str_current_miliseconds, "Fonts/Magneto.ttf", text_color, 30);

	renderTexture(coins_texture, renderer, x, y+5);
}

void buildHeart(SDL_Renderer *renderer, SDL_Texture* texture, int quant, int x, int y)
{
	int distance = 0;
	while (quant > 0)
	{
		renderTexture(texture, renderer, x + distance, y);
		distance += 45;
		quant--;
	}

}


