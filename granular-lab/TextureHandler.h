#pragma once
#include <SDL3/SDL.h>
#include <string>


class TextureHandler {
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string texturePath);
};

