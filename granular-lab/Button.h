#pragma once
#include <string>

class Button {
private:
	SDL_FRect _position{};
	SDL_Color _baseColor{ 240, 240, 240, 255 };
	SDL_Color _highlightColor{ 240, 200, 200, 255 };
	SDL_Color _selectedColor{ 240, 100, 100, 255 };
public:
	Button(const SDL_FRect position);

	const SDL_Color getColor(std::string_view chosenMode);

	const SDL_FRect& getPosition();
};