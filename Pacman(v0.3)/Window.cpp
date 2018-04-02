#include"Window.h"

Window::Window(int new_height, int new_width, std::string new_name)
{
	height = new_height;
	width = new_width;
	name = new_name;

	initializeLibrary();
	createWindow();
	createRenderer();
}

Window::~Window()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Window::initializeLibrary()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		std::cerr << "Error! Cannot initialize the SDL Library" << std::endl;
	}


	if (IMG_Init(IMG_INIT_PNG) != NULL)
	{
		std::cerr << "Error! Cannot initialize the IMG Library" << std::endl;
	}

	if (TTF_Init() != NULL)
	{
		std::cerr << "Error! Cannot initialize the TTF library" << std::endl;
	};
}

void Window::createWindow()
{
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Error! Cannot create SDL window, code: " << SDL_GetError() << std::endl;
		exit(1);
	};
}

void Window::createRenderer()
{

	renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "Error! Cannot create renderer"<< std::endl;
		exit(2);
	}
}

SDL_Texture* Window::loadTexture(std::string file)
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

void Window::renderTexture(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}


SDL_Texture* Window::textToTexture(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
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

void Window::presentWindow()
{
	SDL_RenderPresent(renderer);
}


// text

SDL_Texture* Window::TextToTexture(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
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


void Window::buildScore(int coins, int x, int y)
{
	char coins_char[100];
	coins_char[0] = '\0';
	_itoa_s(coins, coins_char, 100, 10);

	std::string coins_str(coins_char);


	SDL_Color text_color = { 255, 255, 255 };
	SDL_Texture* coins_texture = TextToTexture("Score: " + coins_str, "Fonts/Roboto-Medium.ttf", text_color, 30);
	renderTexture(coins_texture, x, y);
}

void Window::buildTime(int current_time, int x, int y)
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
	SDL_Texture* coins_texture = TextToTexture("Time: " + str_current_minutes + ":" + str_current_seconds + ":" + str_current_miliseconds, "Fonts/Roboto-Medium.ttf", text_color, 30);

	renderTexture(coins_texture, x, y);
}

void Window::buildHeart(SDL_Texture* texture, int quant, int x, int y)
{
	int distance = 0;
	while (quant > 0)
	{
		renderTexture(texture, x + distance, y);
		distance += 45;
		quant--;
	}

}


