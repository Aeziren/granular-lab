#pragma once
#include <SDL3/SDL.h>

/**
 * @brief Initializes SDL, creates a window and renderer, and sets the render scale.
 *
 * @param window Pointer to the SDL_Window pointer to be created.
 * @param renderer Pointer to the SDL_Renderer pointer to be created.
 * @param screenWidth The width of the window in pixels.
 * @param screenHeight The height of the window in pixels.
 * @param scaling The scaling factor for the window and renderer (default is 1).
 * @return true if initialization is successful, else false,
 */
bool init(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight, int scaling);

/**
 * @brief Destroys the SDL window and renderer, and quits SDL.
 *
 * @param window Pointer to the SDL_Window pointer to be destroyed.
 * @param renderer Pointer to the SDL_Renderer pointer to be destroyed.
 */
void close(SDL_Window** window, SDL_Renderer** renderer);
