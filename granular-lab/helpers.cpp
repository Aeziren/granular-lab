#include "helpers.h"
#include <iostream>

bool init(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight, int scaling = 1) {
	/*Initialize main SDL functions. SubSystem set to only video.*/
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL! Error: " << SDL_GetError();
		return false;
	}

	*window = SDL_CreateWindow("My game", screenWidth * scaling, screenHeight * scaling, 0);
	if (window == NULL) {
		std::cout << "Could not create window! Error: " << SDL_GetError();
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, NULL);
	if (renderer == NULL) {
		std::cout << "Could not create renderer! Error: " << SDL_GetError();
		return false;
	}
	if (SDL_SetRenderScale(*renderer, scaling, scaling) == false) {
		std::cout << "Could not set scale! Error: " << SDL_GetError();
		return false;
	}

	return true;
}

void close(SDL_Window** window, SDL_Renderer** renderer) {
	/*Closes the window, renderer and quit SDL.*/
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*renderer);
	SDL_Quit();
}
