#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SDL3/SDL.h>
#include "nlohmann/json.hpp"
#include "GameState.h"
#include "UIManager.h"
#include "Button.h"
#include "Constants.h"


const std::string JSON_BUTTONS_LOCATION{ "screen_buttons.json" };

UIManager::UIManager(SDL_Renderer* renderer, GameState& gameState)
	: _renderer(renderer),
	_gameState(gameState)
{
	_buttons = getJsonButtons(JSON_BUTTONS_LOCATION);
}

void UIManager::ManageButtons() {
	SDL_FRect mouseRect{ _gameState.mouseX / SCALING, _gameState.mouseY / SCALING, 1, 1 };
	int clickedButtonIndex = -1;

	for (size_t i = 0; i < _buttons.size(); ++i) {
		Button& button = _buttons[i];
		SDL_Color color = button.getColor("base");

		if (button.selected) {
			color = button.getColor("selected");
		}
		else if (SDL_HasRectIntersectionFloat(&button.getPosition(), &mouseRect)) {
			if (_gameState.leftMouseButtonDown) {
				clickedButtonIndex = static_cast<int>(i);
				color = button.getColor("selected");
			}
			else {
				color = button.getColor("highlight");
			}
		}		

		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(_renderer, &button.getPosition());
	}

	// Update selection if a button was clicked
	if (clickedButtonIndex != -1) {
		for (size_t i = 0; i < _buttons.size(); ++i) {
			_buttons[i].selected = (i == clickedButtonIndex);
		}
	}
}

std::vector<Button> UIManager::getJsonButtons(const std::string jsonLocation) {
	using json = nlohmann::json;

    std::ifstream file(jsonLocation);
	if (!file.is_open()) {
		std::cerr << "Error opening " << jsonLocation << std::endl;		
	}

	json config{};
	file >> config;

	if (!config.contains("buttons")) 
		return {};
	
	std::vector<Button> resultButtons{};
	for (const auto& button : config["buttons"]) {
		SDL_FRect buttonPosition{ button["x"], button["y"], button["width"], button["height"] };
		Button newButton{ button["name"], button["image"], buttonPosition };

		resultButtons.push_back(newButton);
	}

	return resultButtons;	
}
