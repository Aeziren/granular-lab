#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL3/SDL.h>
#include "helpers.h"
#include "Constants.h"
#include "playLoop.h"


int main(int argc, char* argv[]) {
	// Global random seed
	std::srand(std::time(nullptr));

	// Prepare
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	init(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SCALING);

	try {
		playLoop(window, renderer);
	}
	catch (const std::exception& ex) {
		std::cout << "Error: " << ex.what() << '\n';
	}

	// Close
	close(&window, &renderer);
	return 0;
}
