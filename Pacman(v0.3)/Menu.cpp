#include "Menu.h"



Menu::Menu(std::string button_texture_location, std::string alloc_button_texture_location, std::string background_texture_location, SDL_Renderer* new_renderer, int new_button_amount)
{
	renderer = new_renderer;
	button_texture = loadTexture(button_texture_location.c_str(), renderer);
	alloc_button_texture = loadTexture(alloc_button_texture_location.c_str(), renderer);
	background_texture = loadTexture(background_texture_location.c_str(), renderer);


	button_amount = new_button_amount;
	button = new Button[new_button_amount];

	for (int i = 0; i < button_amount; i++)
	{
		button[i].allocated = false;
		button[i].x = button[i].y = 0;
	}
}



Menu::~Menu()
{
	delete[] button;
}


// sets button location on a screen
void Menu::set_button_location(int button_number, int x, int y)
{
	if (button_number < button_amount)
	{
		button[button_number].x = x;
		button[button_number].y = y;
	}
	else std::cout << "Error! Button number < button amount" << std::endl;
}


// sets text on a button
void Menu::set_button_text(int button_number, char* new_text)
{
	button[button_number].text = new_text;
}



void Menu::change_alloc_button(int num)
{
	for (int i = 0; i < button_amount; i++)
	{	
		button[i].allocated = false;
	}
	button[num].allocated = true;
}



void Menu::build()
{
	//renderTexture(background_texture, renderer, 0, 0);

	for (int i = 0; i < button_amount; i++)
	{
		
		SDL_Color text_color = { 255, 255, 255 };
		SDL_Texture* text_texture = TextToTexture(renderer, button[i].text, "Fonts/Magneto.ttf",  text_color, 55);
		
		if  (button[i].allocated == true) renderTexture(alloc_button_texture, renderer, button[i].x , button[i].y);
		else renderTexture(button_texture, renderer, button[i].x, button[i].y);
		renderTexture(text_texture, renderer, button[i].x+8, button[i].y+17);
	}

}



int Menu::execute()
{
	int menu_choice = 0;
	bool close_menu = false;




	this->change_alloc_button(menu_choice);
	this->build();
	SDL_RenderPresent(renderer);
	SDL_Event event;

	while (!close_menu  && SDL_WaitEvent(&event))
	{
		if (event.type)
		{
			switch (event.type)
			{
			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_w:
				{
					menu_choice--;
					if (menu_choice < 0) menu_choice = this->get_button_amount() - 1;
					break;
				}
				case SDLK_DOWN:
				case SDLK_s:
				{
					menu_choice++;
					if (menu_choice >= this->get_button_amount()) menu_choice = 0;
					break;
				}
				case SDLK_RETURN:
				{
					close_menu = true;
					break;
				}
				break;
				}
			break;
			}
	
		}
			this->change_alloc_button(menu_choice);
			this->build();
			SDL_RenderPresent(renderer);
		}

	}
	return menu_choice;
}

int Menu::execute(bool& escape)
{
	int menu_choice = 0;
	bool close_menu = false;




	this->change_alloc_button(menu_choice);
	this->build();
	SDL_RenderPresent(renderer);
	SDL_Event event;
	while (!close_menu  && SDL_WaitEvent(&event))
	{
		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
			{
				menu_choice--;
				if (menu_choice < 0) menu_choice = this->get_button_amount() - 1;
				break;
			}
			case SDLK_DOWN:
			case SDLK_s:
			{
				menu_choice++;
				if (menu_choice >= this->get_button_amount()) menu_choice = 0;
				break;
			}

			case SDLK_RETURN:
			{
				close_menu = true;
				break;
			}
			case SDLK_ESCAPE:
			{
				
			}

			}
			this->change_alloc_button(menu_choice);
			this->build();
			SDL_RenderPresent(renderer);
		}

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				escape = true;
				close_menu = true;
				break;
			}
		}
		if (event.type == SDL_QUIT)
		{
			exit(0);
		}

	}
	return menu_choice;
}