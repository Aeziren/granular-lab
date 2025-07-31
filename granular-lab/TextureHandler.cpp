#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "TextureHandler.h"



SDL_Texture* TextureHandler::loadTexture(SDL_Renderer* renderer, std::string texturePath) {	
	SDL_Surface* loadedSurface{ IMG_Load(texturePath.c_str()) };


	if (!loadedSurface) {
		std::cout << "Could not load surface!"; // To Do: Detail this error message
		return NULL;
	}

	SDL_Texture* finalTexture{ SDL_CreateTextureFromSurface(renderer, loadedSurface)};
	if (finalTexture == NULL) {
		std::cout << "Could not create texture from loaded surface! Error: " << SDL_GetError();
		SDL_DestroySurface(loadedSurface);

		return NULL;
	}

	return finalTexture;
}