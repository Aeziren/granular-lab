#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"

class UIManager {
private:
	SDL_Renderer* _renderer{};
	GameState& _gameState;

public:
	UIManager(SDL_Renderer* renderer, GameState& gameState);

	void ManageButtons();
};
