#include <iostream>
#include "UIManager.h"
#include "Button.h"
#include "Constants.h"

UIManager::UIManager(SDL_Renderer* renderer, GameState& gameState)
	: _renderer(renderer),
	_gameState(gameState)
{
}

void UIManager::ManageButtons() {
	Button testButton{ SDL_FRect{ 200, 200, 40, 40 } };

	SDL_Color buttonColor{};
	SDL_FRect mouseRect{ _gameState.mouseX / SCALING, _gameState.mouseY / SCALING, 1, 1 };
	if (SDL_HasRectIntersectionFloat(&testButton.getPosition(), &mouseRect)) {
		std::cout << '1';
		buttonColor = testButton.getColor("highlight");
	}
	else {
		std::cout << '0';
		buttonColor = testButton.getColor("base");
	}
	SDL_SetRenderDrawColor(_renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
	SDL_RenderFillRect(_renderer, &testButton.getPosition());
}
