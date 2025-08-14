#include <iostream>
#include <string>
#include "playLoop.h"
#include "World.h"
#include "SandParticle.h"
#include "WaterParticle.h"
#include "Constants.h"
#include "TextureHandler.h"
#include "GameState.h"
#include "handleEvent.h"

class Button {
private:
	SDL_FRect _position{};
	SDL_Color _baseColor{240, 240, 240, 255};
	SDL_Color _highlightColor{ 240, 200, 200, 255 };
	SDL_Color _selectedColor{ 240, 100, 100, 255 };	
public:
	Button(const SDL_FRect& position)
		: _position(position)
	{
	}

	SDL_Color getColor(std::string chosenMode);
};

void playLoop(SDL_Window* window, SDL_Renderer* renderer) {
	World world{};
	SDL_Event event{};
	GameState gameState{};	
	TextureHandler textureHandler{  };
	SDL_Texture* sandTexture{  };
	Button testButton{ SDL_FRect{200, 200, 40, 40} };
			
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

		SDL_FRect mouseRect{ gameState.mouseX / SCALING, gameState.mouseY / SCALING, 1, 1 };		
		if (SDL_HasRectIntersectionFloat(, &mouseRect)) {
			buttonColor = { 200, 140, 0, 0 };
		}
		else {
			buttonColor = { 150, 150, 150, 150 };
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Button rendering
		SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
		SDL_RenderFillRect(renderer, &button);

		// Render & update particles
		world.update();
		world.draw(renderer);

		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(16);
	}
}