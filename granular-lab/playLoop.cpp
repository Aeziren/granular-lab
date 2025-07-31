#include "playLoop.h"
#include "World.h"
#include "SandParticle.h"
#include "WaterParticle.h"
#include "Constants.h"


void playLoop(SDL_Window* window, SDL_Renderer* renderer) {
	World world{};
	SDL_Event event{};
	bool quit{ false };
	float mouseX{};
	float mouseY{};
	bool leftMouseButtonDown{ false };
	bool rightMouseButtonDown{ false };

	while (quit == false) {
		if (leftMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			SandParticle* newParticle = new SandParticle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING));
			world.addParticle(*newParticle);
		}
		if (rightMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			WaterParticle* newParticle = new WaterParticle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING));
			world.addParticle(*newParticle);
		}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				quit = true;
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					leftMouseButtonDown = true;
					break;
				case SDL_BUTTON_RIGHT:
					rightMouseButtonDown = true;
					break;
				}
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					leftMouseButtonDown = false;
					break;
				case SDL_BUTTON_RIGHT:
					rightMouseButtonDown = false;
					break;
				}
				break;
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Render & update particles
		world.update();
		world.draw(renderer);

		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(16);
	}
}