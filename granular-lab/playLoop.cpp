#include <iostream>
#include <string>
#include "playLoop.h"
#include "World.h"
#include "SandParticle.h"
#include "WaterParticle.h"
#include "Constants.h"
#include "GameState.h"
#include "handleEvent.h"
#include "Button.h"
#include "UIManager.h"

void playLoop(SDL_Window* window, SDL_Renderer* renderer) {
	World world{};
	SDL_Event event{};
	GameState gameState{};			
	UIManager uiManager{ UIManager(renderer, gameState) };
			
	while (gameState.quit == false) {
		SDL_GetMouseState(&gameState.mouseX, &gameState.mouseY);

		if (gameState.leftMouseButtonDown) {			
			SandParticle* newParticle = new SandParticle(static_cast<int>(gameState.mouseX / SCALING), static_cast<int>(gameState.mouseY / SCALING));
			world.addParticle(*newParticle);
		}
		if (gameState.rightMouseButtonDown) {			
			WaterParticle* newParticle = new WaterParticle(static_cast<int>(gameState.mouseX / SCALING), static_cast<int>(gameState.mouseY / SCALING));
			world.addParticle(*newParticle);
		}

		while (SDL_PollEvent(&event)) {
			handleEvent(event, gameState);
		}		
		
		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Interface
		uiManager.ManageButtons();			

		// Render & update particles
		world.update();
		world.draw(renderer);

		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(16);
	}
}
