#pragma once
#include <SDL3/SDL.h>

bool init(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight, int scaling);
void close(SDL_Window** window, SDL_Renderer** renderer);
