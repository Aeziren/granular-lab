#include <string>
#include "playLoop.h"
#include "World.h"
#include "SandParticle.h"
#include "WaterParticle.h"
#include "Constants.h"
#include "TextureHandler.h"
#include "GameState.h"
#include "handleEvent.h"


void playLoop(SDL_Window* window, SDL_Renderer* renderer) {
	World world{};
	SDL_Event event{};
	GameState gameState{};
	float mouseX{};
	float mouseY{};
	TextureHandler textureHandler{  };
	SDL_Texture* sandTexture{  };

	while (gameState.quit == false) {
		if (gameState.leftMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			SandParticle* newParticle = new SandParticle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING));
			world.addParticle(*newParticle);
		}
		if (gameState.rightMouseButtonDown) {
			SDL_GetMouseState(&mouseX, &mouseY);
			WaterParticle* newParticle = new WaterParticle(static_cast<int>(mouseX / SCALING), static_cast<int>(mouseY / SCALING));
			world.addParticle(*newParticle);
		}

		while (SDL_PollEvent(&event)) {
			handleEvent(event, gameState);
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